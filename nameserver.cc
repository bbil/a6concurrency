#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    
    //initialize map that tells a student which vending machine to go to
    for(unsigned int i=0; i < numStudents; i++){
        unsigned int vendingMachineIdx = i % numVendingMachines;

        studentToVending.insert(std::pair<unsigned int, unsigned int>(i, vendingMachineIdx));
    }

    registeredMachines = 0;
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
    _registerMachine = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id ) {
    VendingMachine* vm = NULL;

    unsigned int vendingMachineIdx = studentToVending.at(id);

    if(vendingMachines.find(vendingMachineIdx) != vendingMachines.end()){
        vm = vendingMachines.at(vendingMachineIdx);

        //give the student the next vending machine id (modulo), for the next time getMachine is called by the student
        unsigned int newIdx = (vendingMachineIdx + 1) % numVendingMachines;
        studentToVending[id] = newIdx;
    }

    printer.print(Printer::NameServer, 'N', id, vendingMachineIdx);

    return vm;
}

VendingMachine **NameServer::getMachineList() {

    VendingMachine** machines = new VendingMachine*[numVendingMachines];

    for(unsigned int i=0; i < numVendingMachines; i++){
        machines[i] = vendingMachines.at(i);
    }

    return machines;
}

void NameServer::main() {

    printer.print(Printer::NameServer, 'S');

    for(;;){
        _Accept(~NameServer) break;
        or _When(registeredMachines < numVendingMachines) _Accept(VMregister){
            registeredMachines+=1;
            vendingMachines.insert(std::pair<unsigned int, VendingMachine*>( _registerMachine->getId(), _registerMachine));
            printer.print(Printer::NameServer, 'R', _registerMachine->getId());
        }
        or _When(registeredMachines == numVendingMachines) _Accept(getMachine, getMachineList);
    }

    printer.print(Printer::NameServer, 'F');
}

