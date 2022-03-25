
#include <iostream>
#include <string>
#include <memory>
#include "packet.hh"
#include "heap.hh"


int main()
{
    using namespace std;

    // Packet<string> elem1("A", 0);
    // Packet<string> elem1("grammatical", 1);
    // Packet<string> elem1("unit", 2);
    // Packet<string> elem1("that", 3);
    // Packet<string> elem1("is", 4);

    MinHeap<string> styrta(10);

    styrta.addElem(Packet<string>("is", 4));
    styrta.addElem(Packet<string>("unit", 2));
    styrta.addElem(Packet<string>("grammatical", 1));
    styrta.addElem(Packet<string>("A", 0));
    styrta.addElem(Packet<string>("that", 3));
    styrta.addElem(Packet<string>("syntaticly", 5));
    styrta.addElem(Packet<string>("independent", 6));

    // cout << "   " << styrta.getElem() << endl;
    // cout << styrta.getElem(styrta.getLeft(0)) << " " << styrta.getElem(styrta.getRight(0)) << endl;

    // string ordered[5];

    cout << styrta.pop()->getContent() << endl;
    cout << styrta.pop()->getContent() << endl;
    cout << styrta.pop()->getContent() << endl;
    cout << styrta.pop()->getContent() << endl;
    cout << styrta.pop()->getContent() << endl;
    cout << styrta.pop()->getContent() << endl;
    cout << styrta.pop()->getContent() << endl;




    return 0;
}

/*
TODO: 
    add ifndefs to prevent multiple includes.
    Rozwiązanie problemu z template classes: zdefiniuj wszystko w .hh
    References& https://www.geeksforgeeks.org/return-by-reference-in-c-with-examples/
    ogarnij importy zeby uniknąć konfliktów - nie importuj 2x tej samej biblioteki
*/