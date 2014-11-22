#include "student.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ) : printer(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases){}


void Student::main(){
    bottlesToPurchase = MP(0,maxPurchases);
    favouriteFlavour = MP(0,3);

    watCard = watCardOffice.create(id, 5);

    vendingMachine = nameServer.getMachine(id);

    while(bottlesToPurchase > 0){

        unsigned int yields = MP(1,10);

        try{
            vendingMachine->buy(favouriteFlavour, watCard());
            //call is successful, drink the soda
        } catch(VendingMachine::Funds){
            vendingMachine = nameServer.getMachine(id);
        } catch(VendingMachine::Stock){
            unsigned int cost = vendingMachine->cost();
            watCardOffice.transfer(id, cost+5, watCard());
        }
    }
}