#include "parent.h"
#include "bank.h"
#include "printer.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
                    printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {

    printer.print(Printer::Parent, 'S');

    for(;;){

        _Accept(~Parent){
            //print finish statement
            printer.print(Printer::Parent, 'f');
        } _Else {
            //yield before giving money
            yield(parentalDelay);
            //get random number from [1,3]
            unsigned int money = MP(1,3);

            unsigned int studentId = MP(0, numStudents - 1);

            //deposit money into student's account
            bank.deposit(studentId, money);

            //print deposit statement
            printer.print(Printer::Parent, 'd', studentId, money);
        }

    }

    printer.print(Printer::Parent, 'F');

}

