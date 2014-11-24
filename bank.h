#ifndef BANK_H
#define BANK_H

#include <map>
#include <vector>

_Monitor Bank {
  private:
    unsigned int numStudents;

    std::vector<uCondition> waitingOnDeposit;

    std::map<unsigned int, int> accounts;   //map between studentId and money in account   
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
