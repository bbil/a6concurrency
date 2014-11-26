#include "vendingmachine.h"
#include "printer.h"
#include "watcard.h"
#include "nameserver.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour )
: printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour) {
    //initialize stock with 0s
    for(unsigned int i =0; i < 4; i++){
        sodaInventory[i] = 0;
    }

    nameServer.VMregister(this);

    state = NORMAL;
}

void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard &card ) {
    unsigned int stock = sodaInventory[(unsigned int)flavour];
    if(stock == 0){
        //STOCK
        state = STOCK;
        return;
    }

    unsigned int bal = card.getBalance();
    if(bal < sodaCost){
        //FUNDS
        state = FUNDS;
        return;
    }

    //successfull purchase
    state = NORMAL;
    card.withdraw(sodaCost);
}

unsigned int *VendingMachine::inventory() {
    return sodaInventory;
}

void VendingMachine::restocked() {}

_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
    return id;
}

void VendingMachine::main(){

    for(;;){
        //stuff
        _Accept(inventory){
            //wait for a call to restock
            _Accept(restocked);

        } or _Accept(buy){

            if(state == FUNDS){
                //_Resume Funds() _At 
            } else if(state == STOCK){
                //_Resume Stock() _At 
            }

        }
    }
    
}

