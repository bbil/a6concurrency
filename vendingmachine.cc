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

    unsigned int flavourIdx = (unsigned int)flavour;
    unsigned int stock = sodaInventory[flavourIdx];
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

    sodaInventory[flavourIdx] -= 1;

    //successfull purchase
    state = NORMAL;
    card.withdraw(sodaCost);

    printer.print(Printer::Vending, 'B', flavourIdx, sodaInventory[flavourIdx]);
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

    printer.print(Printer::Vending, id, 'S', sodaCost);

    for(;;){
        //stuff
        _Accept(inventory){
            printer.print(Printer::Vending, 'r');
            //wait for a call to restock
            _Accept(restocked);

            printer.print(Printer::Vending, 'R');

        } or _Accept(buy){

            if(state == FUNDS){
                //_Resume Funds() _At 
            } else if(state == STOCK){
                //_Resume Stock() _At 
            }

        }
    }

    printer.print(Printer::Vending, id, 'F');
    
}

