#include "watcardoffice.h"
#include "printer.h"
#include "watcard.h"
#include "bank.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
    : printer(printer), numCouriers(numCouriers){

        couriers = new Courier*[numCouriers];

        for(unsigned int i = 0; i < numCouriers; i++){
            couriers[i] = new Courier(prt, bank, this);
        }

        fin = false;
}

WATCardOffice::~WATCardOffice(){
    for(unsigned int i = 0; i < numCouriers; i++){
        delete couriers[i];
    }

    delete[] couriers;
}

void WATCardOffice::main() {

    for(;;){
        _Accept(~WATCardOffice){
            fin = true;
            for(unsigned int i=0; i < numCouriers; i++){
                _Accept(requestWork);
            }

            break;
        } 
        or _When(jobs.size() > 0) _Accept(requestWork);
        or _Accept(create, transfer);
    }
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Args args(sid, amount);
    Job* job = new Job(args);

    jobs.push(job);

    return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Args args(sid, amount, card);
    Job* job = new Job(args);

    jobs.push(job);

    return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
    if(fin) return NULL;

    //job available, pop it off
    Job* curJob = jobs.front();
    jobs.pop();

    return curJob;
}


void WATCardOffice::Courier::main(){
    for(;;){
        //request work from administrator, blocks if no work available
        Job* job = office->requestWork();

        if(!job) break;

        //gather arguments
        WATCard* card = job->args.card;
        unsigned int sid = job->args.sid;
        unsigned int amount = job->args.amount;

        
        if(MP(0,5) == 0){
            //1 in 6 chance to lose card
            job->result.exception(new WATCardOffice::Lost);
            delete card;
        } else {
            //withdraw from bank (can block)
            bank.withdraw(sid, amount);

            //deposit money to card
            card->deposit(amount);

            job->result.delivery(card);
        }

        //free job memory, already popped off of job queue
        delete job;
    }
}

