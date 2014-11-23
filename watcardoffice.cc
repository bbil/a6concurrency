#include "watcardoffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) {}

void WATCardOffice::main() {}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {}

Job *WATCardOffice::requestWork() {}

