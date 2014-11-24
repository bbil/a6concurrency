#ifndef PRINTER_H
#define PRINTER_H

#include <map>

_Cormonitor Printer {
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
    virtual void main();

    struct Info
    {
        Kind kind;
        char state;
        int value1;
        int value2;
    };

    std::map<unsigned int, Info> nonIdBuffer;   //ids -> parent = 0, watcardoffice = 1, NameServer = 2, Truck = 3, BottlingPlant = 4
    std::map<unsigned int, Info> studentBuffer;
    std::map<unsigned int, Info> vendingBuffer;
    std::map<unsigned int, Info> courierBuffer;

    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;

};

#endif
