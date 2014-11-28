#include "bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
    waitingOnDeposit = new uCondition[numStudents];
    accounts = new int[ numStudents ];
    for(unsigned int i = 0; i < numStudents; i++){
        accounts[i] = 0;
    }
}

Bank::~Bank(){
    delete[] waitingOnDeposit;
    delete[] accounts;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    accounts[id] += amount;
    waitingOnDeposit[id].signal();
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while( amount > accounts[id] ){
        waitingOnDeposit[id].wait();
    }
    accounts[id] -= amount;
}

