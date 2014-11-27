#include "truck.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "vendingmachine.h"

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
            return;
        }

        unsigned int totalCargo = 0;

        for(unsigned int i=0; i < 4; i++){
            totalCargo+= cargo[i];
        }

        printer.print(Printer::Truck, 'P', totalCargo);


        unsigned int firstMachine = machineToStockNext;
        bool first = true;
        for(;;){

            if(!first && firstMachine == machineToStockNext) break;

            printer.print(Printer::Truck, 'd', machineToStockNext, totalCargo);

            unsigned int* inventory = vendingMachines[machineToStockNext]->inventory();

            for(unsigned int i=0; i <= 4; i++){
                unsigned int availableCargo = cargo[i];
                unsigned int inVending = inventory[i];

                if(inVending < maxStockPerFlavour){
                    //can add more soda into machine
                    
                    unsigned int canAdd = maxStockPerFlavour - inVending;

                    if(availableCargo >= canAdd){
                        //fill up
                        availableCargo-=canAdd;
                        inVending+=canAdd;

                        totalCargo-=canAdd;
                    } else {
                        //add as much as possible
                        unsigned int toAdd = canAdd - availableCargo;
                        availableCargo = 0;
                        inVending+=toAdd;

                        totalCargo-=toAdd;

                        printer.print(Printer::Truck, 'U', machineToStockNext, canAdd-toAdd);
                    }
                }

                cargo[i] = availableCargo;
                inventory[i] = inVending;
            }

            printer.print(Printer::Truck, 'D', machineToStockNext, totalCargo);

            first = false;
            machineToStockNext = (machineToStockNext + 1) % numVendingMachines;
        }

        machineToStockNext = (machineToStockNext + 1) % numVendingMachines;
    }

    printer.print(Printer::Truck, 'F');

}


