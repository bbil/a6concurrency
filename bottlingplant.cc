#include "bottlingplant.h"
#include "printer.h"
#include "nameserver.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, 
                            unsigned int timeBetweenShipments ) : printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
                            maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
    truck = new Truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    //initialize plant to having 0 of each flavour on hand
    for( int i = 0; i < 4; i++ ){
        sodaProduced[i] = 0;
    }

    isClosing = false;
}

BottlingPlant::~BottlingPlant(){
    delete truck;
}

void BottlingPlant::produceSoda(){
    int totalProduced = 0;
    
    for( int i = 0; i < 4; i++ ) {
        int produced = MP(maxShippedPerFlavour);    //create random amount for each flavour of soda
        sodaProduced[i] += produced;
        totalProduced += produced;
    }

    printer.print(Printer::BottlingPlant, 'G', totalProduced);
}

void BottlingPlant::main() {

    printer.print(Printer::BottlingPlant, 'S');

    produceSoda();

    for(;;){

        _Accept(~BottlingPlant){
            isClosing = true;
            //call it once more to throw shutdown
            _Accept( getShipment );
            break;
        }
        or _Accept(getShipment){
            printer.print(Printer::BottlingPlant, 'P');
            yield(timeBetweenShipments);
            produceSoda();
        }
    }

    printer.print(Printer::BottlingPlant, 'F');
}

void BottlingPlant::getShipment( unsigned int cargo[] ) {

    if( isClosing ){
        //silence extra exception
        uRendezvousAcceptor();
        _Throw BottlingPlant::Shutdown();
    }

    for( int i = 0; i < 4; i++ ){
        //transfer to truck
        cargo[i] = sodaProduced[i];

        //remove stock of flavour in plant
        sodaProduced[i] = 0;
    }
}

