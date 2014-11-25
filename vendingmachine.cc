#include "vendingmachine.h"
#include "printer.h"
#include "watcard.h"
#include "nameserver.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) {}

void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard &card ) {}

unsigned int *VendingMachine::inventory() {}

void VendingMachine::restocked() {}

_Nomutex unsigned int VendingMachine::cost() {}

_Nomutex unsigned int VendingMachine::getId() {}

void VendingMachine::main(){
    
}

