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

    //wait for server to perform the bulk of the operation
    wait.wait();

    //throw exception based on the state of the vending machine determined in main
    if(state == FUNDS){
        _Throw Funds();
    } else if(state == STOCK){
        _Throw Stock();
    }
}

unsigned int *VendingMachine::inventory() {
    return sodaInventory;
}

//restocked is a no-op, external scheduling is used to control the state of the vending
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

            //store information needed into local variables
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
            //wait for a call to restock, no calls to buy can happen once in this block
            printer.print(Printer::Vending, id, 'r');
            
            _Accept(restocked);

            printer.print(Printer::Vending, id, 'R');
        } 
    }

    printer.print(Printer::Vending, id, 'F');
    
}

