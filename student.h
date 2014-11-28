#ifndef STUDENT_H
#define STUDENT_H

#include "mprng.h"

#include "watcard.h"

_Cormonitor Printer;
_Task NameServer;
_Task WATCardOffice;
_Task VendingMachine;


extern MPRNG MP;

_Task Student {
  private:
    Printer& printer;
    NameServer& nameServer;
    WATCardOffice& cardOffice;
    WATCard::FWATCard watCard;
    VendingMachine* vendingMachine;
    unsigned int id;
    unsigned int maxPurchases;
    unsigned int bottlesToPurchase;
    unsigned int favouriteFlavour;


    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
    ~Student();
};

#endif
