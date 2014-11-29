#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    studentToVending = new int[numStudents];
    vendingMachines = new VendingMachine*[numVendingMachines];
    
    //initialize map that tells a student which vending machine to go to
    for( unsigned int i=0; i < numStudents; i++ ) {
        studentToVending[i] = i % numVendingMachines;
    }

    registeredMachines = 0;
}

NameServer::~NameServer() {
    delete [] studentToVending;
    delete [] vendingMachines;
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
    _registerMachine = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id ) {
    VendingMachine* vm = NULL;
	
	vm = vendingMachines[studentToVending[id]];
	studentToVending[id] = (studentToVending[id] + 1) % numVendingMachines; //possibly change

    printer.print(Printer::NameServer, 'N', id, vm->getId());

    return vm;
}

VendingMachine **NameServer::getMachineList() {
    return vendingMachines;
}

void NameServer::main() {

    printer.print(Printer::NameServer, 'S');

    for(;;){
        _Accept(~VendingMachine) break;
        or _When( registeredMachines < numVendingMachines ) _Accept(VMregister){
            vendingMachines[registeredMachines] = _registerMachine->getId();
            registeredMachines += 1;
            printer.print(Printer::NameServer, 'R', _registerMachine->getId());
        }
        or _When(registeredMachines == numVendingMachines) _Accept(getMachine, getMachineList)
    }

    printer.print(Printer::NameServer, 'F');
}

