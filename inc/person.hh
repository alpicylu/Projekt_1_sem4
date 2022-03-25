#ifndef PERSON_HH
#define PERSON_HH

#include <string>
#include <iostream>
#include "packet.hh"


class Person
{
private:
    std::string name;
    std::string message_to_send; //original, unaltered and ordered message 
    std::string recieved_mess;

public:

    /*Konstruktor i konstruktor kopiujący*/
    Person(std::string n, std::string m="") {name = n; message_to_send = m;}
    Person(const Person& P) {name = P.name; message_to_send = P.message_to_send;}

    void setMessage(std::string new_message) {message_to_send = new_message;}

    void generateMessage(int num_of_chars);

    void sendMessage(Person& address, bool read_scramble=false);

    void recieveMessage(const Packet<std::string>* message, int mess_size);

    void readMessage()
    {
        std::cout << "Uporządkowana wiadomość: ";
        std::cout << recieved_mess << std::endl;}
};


#endif