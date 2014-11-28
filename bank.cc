#include "bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
    waitingOnDeposit = new uCondition[numStudents];
    for(unsigned int i = 0; i < numStudents; i++){
        accounts.insert(std::pair<unsigned int, int>(i, 0));
    }
}

Bank::~Bank(){
    delete[] waitingOnDeposit;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    std::map<unsigned int, int>::iterator it = accounts.find(id);
    if(it != accounts.end()){
        //account is found
        it->second+= amount;

        waitingOnDeposit[id].signal();
    }
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    std::map<unsigned int, int>::iterator it = accounts.find(id);
    if(it != accounts.end()){
        //account is found


        while(amount > it->second){
            waitingOnDeposit[id].wait();
        }

        it->second-= amount;
    }
}

