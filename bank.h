#ifndef BANK_H
#define BANK_H

#include <map>

_Monitor Bank {
  private:
    unsigned int numStudents;

    uCondition* waitingOnDeposit;

    std::map<unsigned int, int> accounts;   //map between studentId and money in account   
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
