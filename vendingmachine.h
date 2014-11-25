#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

_Cormonitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
    void main();
  public:
    enum Flavours {
        BluesBlackCherry = 0,
        ClassicalCreamSoda = 1,
        RockRootBeer = 2,
        JazzLime = 3
    };                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif