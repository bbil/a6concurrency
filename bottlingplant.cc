#include "bottlingplant.h"
#include "printer.h"
#include "nameserver.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, 
                            unsigned int timeBetweenShipments ) : printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
                            maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {}

BottlingPlant::~BottlingPlant(){
    delete truck;
}

void BottlingPlant::main() {
    //create truck
    truck = new Truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);
}

void BottlingPlant::getShipment( unsigned int cargo[] ) {}

