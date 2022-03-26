
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
    // demo_message = "";
    Person Jan("Jan");
    Person Anna("Anna");
    
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna);
    Anna.readMessage();

    demo_message = "Koń jaki jest, każdy widzi.";
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna);
    Anna.readMessage();

    Jan.generateMessage(100);
    Jan.sendMessage(Anna);
    Anna.readMessage();
}

int main()
{
    // Demonstration();

    MinHeap<std::string> sterta(3);
    sterta.addElem(Packet<std::string>("a", 1));

    // std::cout << sterta.getElem()->getContent();
    // std::cout << sterta.getElem()->getContent();
    // std::cout << sterta.getElem()->getContent();


    return 0;
}

/*
TODO: Add peak() to heap
*/