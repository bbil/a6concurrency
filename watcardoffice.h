#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <queue>

#include "mprng.h"
#include "watcard.h"
#include "printer.h"
_Monitor Bank;

extern MPRNG MP;

_Task WATCardOffice {
    struct Args
    {
        unsigned int sid;
        unsigned int amount;
        WATCard* card;

        Args(unsigned int sid, unsigned int a) : sid(sid), amount(a) {
            card = new WATCard();
        }

        Args(unsigned int sid, unsigned int a, WATCard* w) : sid(sid), amount(a), card(w) {}
    };

    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier {
      private:
        Printer& printer;
        Bank& bank;
        WATCardOffice* office;
        unsigned int id;
      public:
        Courier(Printer& printer, Bank& b, WATCardOffice* office, unsigned int id) : printer(printer), bank(b), office(office), id(id) {}
        virtual void main();
    };                 // communicates with bank

    Printer& printer;
    unsigned int numCouriers;
    bool fin;

    Courier** couriers;                 //array of courier pointers

    std::queue<Job*> jobs;

    void main();
  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
