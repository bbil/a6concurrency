#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

_Cormonitor Printer;
_Task NameServer;
#include "truck.h"
#include "mprng.h"

extern MPRNG MP;

_Task BottlingPlant {
  private:
    Printer& printer;
    NameServer& nameServer;
    Truck* truck;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    void main();
  public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] );
};

#endif
