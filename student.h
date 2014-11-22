#ifndef STUDENT_H
#define STUDENT_H

#include "mprng.h"
#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "vendingmachine.h"


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
};

#endif
