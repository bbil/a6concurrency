#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;					// direct access to std
#include <cstdlib>					// exit

#include "config.h"
#include "mprng.h"

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
    
    // start
    ConfigParms parms;
    processConfigFile( configFile, parms );

}








