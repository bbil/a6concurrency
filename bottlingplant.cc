#include "bottlingplant.h"
#include "printer.h"
#include "nameserver.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, 
                            unsigned int timeBetweenShipments ) : printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
                            maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
    truck = new Truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    //initialize plant to having 0 of each flavour on hand
    for(unsigned int i = 0; i < 4; i++){
        sodaProduced.insert(std::pair<VendingMachine::Flavours, unsigned int>((VendingMachine::Flavours)i, 0));
    }

    isClosing = false;
}

BottlingPlant::~BottlingPlant(){
    delete truck;
}

void BottlingPlant::produceSoda(){
    for(unsigned int i = 0; i < 4; i++){
        unsigned int produced = MP(0, maxShippedPerFlavour);    //create random amount for each flavour of soda
        sodaProduced[(VendingMachine::Flavours)i] += produced;
    }
}

void BottlingPlant::main() {

    produceSoda();

    for(;;){

        _Accept(~BottlingPlant){
            break;
        }
        or _Accept(getShipment){

            yield(timeBetweenShipments);
            produceSoda();
        }
    }
}

void BottlingPlant::getShipment( unsigned int cargo[] ) {

    if(isClosing){
        //silence extra exception
        uRendezvousAcceptor();
        _Throw BottlingPlant::Shutdown();
    }

    unsigned int flavourShipment = 0;

    for(unsigned int i = 0; i < 4; i++){

        //amount of soda of this flavour produced
        flavourShipment = sodaProduced[(VendingMachine::Flavours)i];

        //transfer to truck
        cargo[i] = flavourShipment;

        //remove stock of flavour in plant
        sodaProduced[(VendingMachine::Flavours)i] = 0;
    }
}

