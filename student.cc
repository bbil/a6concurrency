#include "student.h"
#include "printer.h"
#include "watcardoffice.h"
#include "nameserver.h"
#include "vendingmachine.h"

#include <iostream>

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ) : printer(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases){}

Student::~Student(){
    delete watCard();
}

void Student::main(){

    bottlesToPurchase = MP(0,maxPurchases);
    favouriteFlavour = MP(0,3);

    printer.print(Printer::Student, id, 'S', favouriteFlavour, bottlesToPurchase);

    watCard = cardOffice.create(id, 5);

    vendingMachine = nameServer.getMachine(id);
    printer.print(Printer::Student, id, 'V', vendingMachine->getId());

    unsigned int yields = MP(1,10);
    yield(yields);

    bool lostError = false;

    while(bottlesToPurchase > 0){
        try{
            vendingMachine->buy((VendingMachine::Flavours)favouriteFlavour, *watCard());
            printer.print(Printer::Student, id, 'B', watCard()->getBalance());
            bottlesToPurchase--;
            //call is successful, drink the soda
        } catch(WATCardOffice::Lost){
            printer.print(Printer::Student, id, 'L');
            cardOffice.create(id, 5);
            lostError = true;
        } catch(VendingMachine::Funds){
            vendingMachine = nameServer.getMachine(id);
            printer.print(Printer::Student, id, 'V', vendingMachine->getId());
        } catch(VendingMachine::Stock){
            unsigned int cost = vendingMachine->cost();
            cardOffice.transfer(id, cost+5, watCard());
        }

        if(lostError) continue;

        yields = MP(1,10);
        yield(yields);
    }

    printer.print(Printer::Student, id, 'F');
}