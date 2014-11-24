#include "bank.h"

Bank( unsigned int numStudents ) : numStudents(numStudents) {

    for(int i = 0; i < numStudents; i++){
        accounts.insert(std::pair<unsigned int, int>(i, 0));
        waitingOnDeposit.push_back(uCondition());
    }
}

void deposit( unsigned int id, unsigned int amount ) {
    map<unsigned int, int>::iterator it = accounts.find(id);
    if(it != accounts.end()){
        //account is found
        it->second+= amount;

        waitingOnDeposit[id].signal();
    }
}

void withdraw( unsigned int id, unsigned int amount ) {
    map<unsigned int, int>::iterator it = accounts.find(id);
    if(it != accounts.end()){
        //account is found

        int accountBal = it->second;

        while(amount > accountBal){
            waitingOnDeposit[id].wait();
        }

        it->second-= amount;
    }
}

