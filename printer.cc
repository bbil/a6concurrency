#include "printer.h"
#include <iostream>

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
		numStudents(numStudents), numVendingMachines(numVendingMachines) {
	totalSize = 5 + numStudents + numVendingMachines + numCouriers;
	buffer = new Info [totalSize];

	// Print top
	cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
	for (unsigned int i = 0; i < numStudents; i++) {
		cout << "Stud" << i << '\t';
	}
	for (unsigned int i = 0; i < numVendingMachines; i++) {
		cout << "Mach" << i << '\t';
	}
	for (unsigned int i = 0; i < numCouriers; i++) {
		cout << "Cour" << i << '\t';
	}
	cout << endl;
	for (unsigned int i = 0; i < totalSize; i++) {
		cout << "=======" << '\t';
	}
	cout << endl;

	//set to empty
	for (unsigned int i = 0; i < totalSize; i++) {
		buffer[i].exists = false;
	}
}


Printer::~Printer () {
	cout << "***********************" << endl;
	delete [] buffer;
}

_Mutex void Printer::print( unsigned int id, char state, int value1, int value2) {
	if (state == 'F') {
		// check for flush
		for (unsigned int i = 0; i < totalSize; i++) {
			if (buffer[id].exists) {
				flush();
				break;
			}
		}

		// special case finish
		for (unsigned int i = 0; i < totalSize; i++) {
			if (id != i) {
				cout << "...";
			} else {
				cout << state;
			}
			cout << "\t";
		}
		cout << endl;
	} else if (buffer[id].exists) {
      flush();
	}

	if (state != 'F') {
		buffer[id].state  = state;
		buffer[id].value1 = value1;
		buffer[id].value2 = value2;
		buffer[id].exists = true;
	}
}

void Printer::print( Kind kind, char state ) {
	print(kind, state, -1, -1);
}

void Printer::print( Kind kind, char state, int value1 ) {
	print(kind, state, value1, -1);
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	print(kind, 0, state, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
	print(kind, lid, state, -1, -1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	print(kind, lid, state, value1, -1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	int offset = 0;
	
	if ( kind == Student ) {
		offset = 5;
	} else if ( kind == Vending ) {
		offset = 5 + numStudents;
	} else if ( kind == Courier ) {
		offset = 5 + numStudents + numVendingMachines;
	} else {
		offset = (unsigned int) kind;
	}

	print(offset + lid, state, value1, value2);
}


void Printer::flush () {
	for (unsigned int i = 0; i < totalSize; i++) {
		if (buffer[i].exists) {
			cout << buffer[i].state;
			if (buffer[i].value1 != -1) {
				cout << buffer[i].value1;
				if (buffer[i].value2 != -1) {
					cout << ',' << buffer[i].value2;
				}
			}
			buffer[i].exists = false;
		}
		cout << "\t";
	}
	cout << endl;
}