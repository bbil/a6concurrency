#ifndef TRUCK_H
#define TRUCK_H

#include <vector>
#include "mprng.h"

_Cormonitor Printer;
_Task NameServer;
_Task BottlingPlant;
_Task VendingMachine;

extern MPRNG MP;

_Task Truck {
  private:
    Printer& printer;
    NameServer& nameServer;
    BottlingPlant& plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    unsigned int machineToStockNext;


    std::vector<VendingMachine*> vendingMachines;

    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
