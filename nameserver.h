#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <map>

_Task VendingMachine;
_Cormonitor Printer;

_Task NameServer {
  private:

    std::map<unsigned int, unsigned int> studentToVending;  //holds the vending machine id that a student is currently located at
    std::map<unsigned int, VendingMachine*> vendingMachines; //holds a relationship to a vending machine to its id
    

    Printer& printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;

    VendingMachine* _registerMachine;                   //used for transfering data for main

    unsigned int registeredMachines;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
