


#include <iostream>
#include <string>
#include <memory>
#include "packet.hh"
#include "heap.hh"
#include "person.hh"


void Demonstration()
{
    using namespace std;
    string demo_message = "Koń jaki jest, każdy widzi";
    Person Jan("Jan");
    Person Anna("Anna");
    
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna);
    Anna.readMessage();

    demo_message = "Once upon a time in a kingdom far, far away, the king and queen were blessed with a beautiful baby girl.";
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna);
    Anna.readMessage();

    Jan.generateMessage(100);
    Jan.sendMessage(Anna);
    Anna.readMessage();
}

int main()
{
    Demonstration();

    return 0;
}

/*
TODO: 
    add ifndefs to prevent multiple includes.
    Rozwiązanie problemu z template classes: zdefiniuj wszystko w .hh
    References& https://www.geeksforgeeks.org/return-by-reference-in-c-with-examples/
    ogarnij importy zeby uniknąć konfliktów - nie importuj 2x tej samej biblioteki
*/