
#include <iostream>
#include <string>
#include <memory>
// #include "packet.hh"
#include "person.hh"  //person includes packet and heap
// #include "heap.hh"

void Demonstration()
{
    using namespace std;
    string demo_message = "Once upon a time in a kingdom far, far away, the king and queen were blessed with a beautiful baby girl.";
    int poczatkowa_pojemnosc_sterty = 2;  //niska wartość w celu zaprezentowania funkcjonalnośći poszerzania tablicy
    int rozmiar_jednego_pakietu = 5;  //ilość znaków, która będzie przechowywana w jednym pakiecie.

    Person Jan("Jan", poczatkowa_pojemnosc_sterty);
    Person Anna("Anna");
    
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna, rozmiar_jednego_pakietu);
    Anna.readMessage();

    demo_message = "Koń jaki jest, każdy widzi.";
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna, rozmiar_jednego_pakietu);
    Anna.readMessage();

    Jan.generateMessage(100);
    Jan.sendMessage(Anna, rozmiar_jednego_pakietu);
    Anna.readMessage();
}

int main()
{
    Demonstration();

    // MinHeap<std::string> sterta(3);
    // sterta.enqueue(Packet<std::string>("a", 1));

    // std::cout << sterta.front()->getPriority();
    // std::cout << sterta.front()->getPriority();
    // std::cout << sterta.front()->getPriority();

    // // sterta.front()->test(6);
    // std::cout << sterta.front()->getPriority();    


    return 0;
}

/*
TODO: 
Refactoring: - DONE
    front() - front()
    pop() - dequeue()
    addElem() - enqueue()
    (...) - size()    zwraca ilość przechowywanych elementów
    (...) - isEmpty()    czy w kolejce są jakieś elementy

Methods allowing for modification of packets - unused, but DONE
Linear scale O() into a CSV
Make heapsize be settable from Person constructor (currently hardset at defauld MinHeap constructor) - DONE
*/