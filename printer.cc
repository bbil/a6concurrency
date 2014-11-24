#include "printer.h"

#include <iostream>

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
 numStudents(numStudents), numVending(numVendingMachines), numCouriers(numCouriers) {
    resume();
}

void Printer::print( Kind kind, char state ) {}

void Printer::print( Kind kind, char state, int value1 ) {}

void Printer::print( Kind kind, char state, int value1, int value2 ) {}

void Printer::print( Kind kind, unsigned int lid, char state ) {}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {}

void Printer::clearBuffers(){
    nonIdBuffer.clear();
    studentBuffer.clear();
    vendingBuffer.clear();
    courierBuffer.clear();
}

void Printer::insertToBuffer(Printer::Info info){
    Printer::Kind kind = info.kind;
    switch(kind){
        case Parent:
            if(nonIdBuffer.find(0) == buffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            nonIdBuffer.insert(Pair<unsigned int, Info>(0, info));
            break;
        case WATCardOffice:
            if(nonIdBuffer.find(1) == buffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            nonIdBuffer.insert(Pair<unsigned int, Info>(1, info));
            break;
        case NameServer:
            if(nonIdBuffer.find(2) == buffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            nonIdBuffer.insert(Pair<unsigned int, Info>(2, info));
            break;
        case Truck:
            if(nonIdBuffer.find(3) == buffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            nonIdBuffer.insert(Pair<unsigned int, Info>(3, info));
            break;
        case BottlingPlant:
            if(nonIdBuffer.find(4) == buffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            nonIdBuffer.insert(Pair<unsigned int, Info>(4, info));
            break;
    }
}

void Printer::insertToBuffer(Printer::Info info, unsigned int lid){
    Printer::Kind kind = info.kind;
    switch(kind){
        case Student:
            if(studentBuffer.find(lid) == studentBuffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            studentBuffer.insert(Pair<unsigned int, Info>(lid, info));
            break;
        case Vending:
            if(vendingBuffer.find(lid) == vendingBuffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            vendingBuffer.insert(Pair<unsigned int, Info>(lid, info));
            break;
        case Courier:
            if(courierBuffer.find(lid) == courierBuffer.end()){

            } else {
                resume();
                clearBuffers();
            }
            courierBuffer.insert(Pair<unsigned int, Info>(lid, info));
            break;
    }
}

void Printer::printInfo(Printer::Info info){
    char state = info.state;
    Printer::Kind kind = info.kind;

    switch(state){
        case 'S':
            if(kind == Student){
                cout << state << info.value1 << "," << info.value2;
            } else if(kind == Vending){
                cout << state << info.value1;
            } else {
                cout << state;
            }
            break;
        case 'D':
            cout << state << info.value1 << "," << info.value2;
            break;
        case 'd': 
            cout << state << info.value1 << "," << info.value2;
            break;
        case 'R':
            if(kind == Vending){
                cout << state;
            } else {
                cout << state << info.value1;
            }
            break;
        case 'r':
            cout << state;
            break;
        case 'C':
            cout << state << info.value1 << "," << info.value2;
            break;
        case 'W':
            cout << state;
            break;
        case 'B':
            if(kind == Vending){
                cout << state << info.value1 "," << info.value2;
            } else {
                cout << state << info.value1;
            }
            break;
        case 'L':
            cout << state << info.value1;
            break;
        case 'U':
            cout << state << info.value1 << "," << info.value2;
            break;
        case 'T':
            cout << state << info.value1 << "," << info.value2;
            break;
        case 't':
            cout << state << info.value1 << "," << info.value2;
            break;
        case 'V':
            cout << state << info.value1;
            break;
        case 'N':
            cout << state << info.value1 << "," << info.value2;
            break;
        case 'P':
            if(kind == BottlingPlant){
                cout << state;
            } else {
                cout << state << info.value1;
            }
            break;
        case 'G':
            cout << state << info.value1;
            break;
    }
}

void Printer::main(){

    cout << "Parent" << "\t";
    cout << "WatOff" << "\t";
    cout << "Names" << "\t";
    cout << "Truck" << "\t";
    cout << "Plant" << "\t";

    for(unsigned int i = 0; i < numStudents; i++){
        cout << "Stud" << i << "\t";
    }

    for(unsigned int i = 0; i < numVending; i++){
        cout << "Mach" << i << "\t";
    }

    for(unsigned int i=0; i < numCouriers; i++){
        cout << "Cour" << i << "\t";
    }

    cout << endl;

    for(unsigned int i=0; i < (5 + numStudents + numVending + numCouriers); i++){
        cout << "*******" << "\t"
    }

    cout << endl;

    for(;;){
        suspend();

        //print that stuff

        for(unsigned int i = 0; i < 5; i++){
            if(nonIdBuffer.find(i) != nonIdBuffer.end()){
                //found

                Printer::Info info = nonIdBuffer.at(i);
                printInfo(info);
            }

            cout << "\t";
        }

        for(unsigned int i = 0; i < numStudents; i++){
            if(studentBuffer.find(i) != studentBuffer.end()){
                //found
                Printer::Info info = studentBuffer.at(i);
                printInfo(info);
            }

            cout << "\t";
        }

        for(unsigned int i = 0; i < numVending; i++){
            if(vendingBuffer.find(i) != vendingBuffer.end()){
                //found
                Printer::Info info = vendingBuffer.at(i);
                printInfo(info);
            }
            cout << "\t";
        }

        for(unsigned int i = 0; i < numCouriers; i++){
            if(courierBuffer.find(i) != courierBuffer.end()){
                //found
                Printer::Info info = courierBuffer.at(i);
                printInfo(info);
            }
            cout << "\t";
        }

        cout << endl;
    }
    cout << "***********************" << endl;

}

