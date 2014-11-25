#ifndef PARENT_H
#define PARENT_H

_Cormonitor Printer;
_Monitor Bank;
#include "mprng.h"

extern MPRNG MP;

_Task Parent {
  private:
    void main();
    Printer& printer;
    Bank& bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
