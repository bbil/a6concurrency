#include "watcardoffice.h"
#include "watcard.h"
#include "bank.h"

#include <iostream>

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
    : printer(prt), numCouriers(numCouriers){

        //initialize couriers
        couriers = new Courier*[numCouriers];
        for(unsigned int i = 0; i < numCouriers; i++){
            couriers[i] = new Courier(prt, bank, this, i);
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

    printer.print(Printer::WATCardOffice, 'S');

    for(;;){
        _Accept(~WATCardOffice){
            //flush all outstanding jobs
            while(!jobs.empty()){
                _Accept(requestWork);
            }

            fin = true;

            //allow all couriers to do one final requestWork call, so that the courier can terminate
            for(unsigned int i=0; i < numCouriers; i++){
                _Accept(requestWork);
            }

            break;
        } 
        or _When(jobs.size() > 0) _Accept(requestWork);
        or _Accept(create, transfer);
    }

    printer.print(Printer::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    //create a new job and put it on the queue
    Args args(sid, amount);
    Job* job = new Job(args);

    jobs.push(job);

    printer.print(Printer::WATCardOffice, 'C', sid, amount);

    return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    //create a new job and put it on the queue
    Args args(sid, amount, card);
    Job* job = new Job(args);

    jobs.push(job);

    printer.print(Printer::WATCardOffice, 'T', sid, amount);

    return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
    //give couriers null if watcard office is beginning to terminate
    if(fin) return NULL;

    //job available, pop it off
    Job* curJob = jobs.front();
    jobs.pop();

    printer.print(Printer::WATCardOffice, 'W');
    return curJob;
}


void WATCardOffice::Courier::main(){

    printer.print(Printer::Courier, id, 'S');

    for(;;){
        //request work from administrator, blocks if no work available
        Job* job = office->requestWork();

        //terminate if job recieved is null, means that watcard office is also terminating
        if(!job) break;

        //gather arguments
        WATCard* card = job->args.card;
        unsigned int sid = job->args.sid;
        unsigned int amount = job->args.amount;

        printer.print(Printer::Courier, id, 't', sid, amount);

        //withdraw from bank (can block)
        bank.withdraw(sid, amount);

        //deposit money to card
        card->deposit(amount);
        printer.print(Printer::Courier, id, 'T', sid, amount);

        
        if(MP(0,5) == 0){
            //1 in 6 chance to lose card
            job->result.exception(new WATCardOffice::Lost);
            delete card;
        } else {
            job->result.delivery(card);
        }

        //free job memory, already popped off of job queue
        delete job;
    }

    printer.print(Printer::Courier, id, 'F');
}

