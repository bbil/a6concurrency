#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    
    //initialize map that tells a student which vending machine to go to
    for(unsigned int i=0; i < numStudents; i++){
        unsigned int vendingMachineIdx = i % numVendingMachines;

        studentToVending.insert(std::pair<unsigned int, unsigned int>(i, vendingMachineIdx));
    }
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
    unsigned int id = vendingmachine->getId();

    vendingMachines.insert(std::pair<unsigned int, VendingMachine*>(id, vendingmachine));
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
    for(;;){
        _Accept(~VendingMachine);
        or _Accept(getMachine);
        or _Accept(getMachineList);
        or _Accept(VMregister);
    }
}

