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

    state = NORMAL;
}

void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard &card ) {

    _flavour = flavour;
    _card = &card;

    wait.wait();

    if(state == FUNDS){
        _Throw Funds();
    } else if(state == STOCK){
        _Throw Stock();
    }
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

    nameServer.VMregister(this);

    for(;;){
        //stuff
        _Accept(~VendingMachine) break;
        or _Accept(buy){

            unsigned int flavourIdx = (unsigned int)_flavour;
            unsigned int stock = sodaInventory[flavourIdx];
            unsigned int bal = _card->getBalance();

            if(stock == 0){
                //STOCK
                state = STOCK;
            } else if(bal < sodaCost){
                //FUNDS
                state = FUNDS;
            } else {
                //NORMAL
                state = NORMAL;
                sodaInventory[flavourIdx]-=1;
                //successfull purchase
                
                _card->withdraw(sodaCost);

                printer.print(Printer::Vending, id, 'B', flavourIdx, sodaInventory[flavourIdx]);
            }

            wait.signalBlock();
        }
        or _Accept(inventory){
            printer.print(Printer::Vending, id, 'r');
            //wait for a call to restock
            _Accept(restocked);

            printer.print(Printer::Vending, id, 'R');
        } 
    }

    printer.print(Printer::Vending, id, 'F');
    
}

