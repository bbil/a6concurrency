#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;					// direct access to std
#include <cstdlib>					// exit

#include "config.h"
#include "mprng.h"

#include "bank.h"
#include "bottlingplant.h"
#include "nameserver.h"
#include "parent.h"
#include "printer.h"
#include "student.h"
#include "truck.h"
#include "vendingmachine.h"
#include "watcard.h"
#include "watcardoffice.h"
#include <vector>

bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ config-file [ random-seed (> 0) ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage


MPRNG MP;


void uMain::main() {
    int seed = getpid();
    char* configFile = "soda.config";
    
    //IO
    switch ( argc ) {
      case 3:
        if ( ! convert( seed, argv[2] ) || seed <= 0 ) {	// invalid integer ?
	        usage( argv );
	    }
        // FALL THROUGH
      case 2:
        configFile = argv[1];
        // FALL THROUGH
      case 1:						// all defaults
        break;
      default:						// wrong number of options
	    usage( argv );
    }

    vector<VendingMachine*> vendingMachines;
    vector<Student*> students;

    // start
    ConfigParms parms;
    processConfigFile( configFile, parms );

    Printer printer(parms.numStudents, parms.numVendingMachines, parms.numCouriers);

    Bank bank(parms.numStudents);

    Parent parent(printer, bank, parms.numStudents, parms.parentalDelay);

    WATCardOffice watCardOffice(printer, bank, parms.numCouriers);

    NameServer nameServer(printer, parms.numVendingMachines, parms.numStudents);

    for(unsigned int i = 0; i < parms.numVendingMachines; i++){
        vendingMachines.push_back(new VendingMachine(printer, nameServer, i, parms.sodaCost, parms.maxStockPerFlavour));
    }

    BottlingPlant* bottlingPlant = new BottlingPlant(printer, nameServer, parms.numVendingMachines, parms.maxShippedPerFlavour, parms.maxStockPerFlavour, parms.timeBetweenShipments);

    for(unsigned int i = 0; i < parms.numStudents; i++){
        students.push_back(new Student(printer, nameServer, watCardOffice, i, parms.maxPurchases));
    }

    for(unsigned int i = 0; i < parms.numStudents; i++){
        delete students[i];
    }

    delete bottlingPlant;

    for (unsigned int i = 0; i < parms.numVendingMachines; i++){
        delete vendingMachines[i];
    }
}








