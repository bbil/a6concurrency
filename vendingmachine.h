#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

_Cormonitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
  public:
    enum Flavours {
        BluesBlackCherry = 0,
        ClassicalCreamSoda = 1,
        RockRootBeer = 2,
        JazzLime = 3
    };  // flavours of soda (YOU DEFINE)
  private:

    enum InternalState {
        NORMAL,
        STOCK,
        FUNDS
    };

    Printer& printer;
    NameServer& nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;

    InternalState state;

    unsigned int sodaInventory[4];

    void main();
  public:
                   
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