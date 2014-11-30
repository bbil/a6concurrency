#include "truck.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "vendingmachine.h"

#include <iostream>

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, 
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {

    VendingMachine** machineList = nameServer.getMachineList();
    for(unsigned int i=0; i < numVendingMachines; i++){
        vendingMachines.push_back(machineList[i]);
    }

    delete machineList;
    
    machineToStockNext = 0;
}

void Truck::main() {

    printer.print(Printer::Truck, 'S');

    for(;;){

        unsigned int yields = MP(1, 10);
        yield(yields); //go to tom horton's

        unsigned int cargo[4];

        try{
            plant.getShipment(cargo);
        } catch(BottlingPlant::Shutdown){
            //the plant has stopped producing soda, no need to continue making deliveries
            return;
        }

        unsigned int totalCargo = 0;

        //loop over newly received soda to take total inventory
        for(unsigned int i=0; i < 4; i++){
            totalCargo+= cargo[i];
        }

        printer.print(Printer::Truck, 'P', totalCargo);


        unsigned int firstMachine = machineToStockNext;
        bool first = true;
        for(;;){

            //stop delivering if no soda is left or 
            if((!first && firstMachine == machineToStockNext) || totalCargo == 0) break;

            printer.print(Printer::Truck, 'd', machineToStockNext, totalCargo);

            unsigned int* inventory = vendingMachines[machineToStockNext]->inventory();

            bool filled = true;
            unsigned int notReplenished = 0;

            //loop through flavours
            for(unsigned int i=0; i < 4; i++){
                unsigned int availableCargo = cargo[i];
                unsigned int inVending = inventory[i];

                if(inVending < maxStockPerFlavour){

                    //can add more soda into machine
                    unsigned int canAdd = maxStockPerFlavour - inVending;

                    if(availableCargo == 0){
                        filled = false;
                        notReplenished+=canAdd;
                        continue;
                    }

                    if(availableCargo >= canAdd){
                        //fill up vending machine for specific flavour completely
                        availableCargo-=canAdd;
                        inVending+=canAdd;

                        totalCargo-=canAdd;
                    } else {
                        //add as much as possible, keep track of how much space is empty
                        inVending+=availableCargo;
                        totalCargo-=availableCargo;
                        notReplenished+=canAdd-availableCargo;

                        availableCargo = 0;

                        filled = false;
                        
                    }
                }

                cargo[i] = availableCargo;
                inventory[i] = inVending;
            }

            if(!filled){
                printer.print(Printer::Truck, 'U', machineToStockNext, notReplenished);
            }

            printer.print(Printer::Truck, 'D', machineToStockNext, totalCargo);

            vendingMachines[machineToStockNext]->restocked();

            first = false;
            machineToStockNext = (machineToStockNext + 1) % numVendingMachines;
        }
    }

    printer.print(Printer::Truck, 'F');

}


