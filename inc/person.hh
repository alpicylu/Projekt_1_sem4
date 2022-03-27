#ifndef PERSON_HH
#define PERSON_HH

#include <string>
#include <iostream>
#include "packet.hh"
#include "heap.hh"
#include "debug.hh"


class Person
{
private:
    std::string name;
    std::string message_to_send; //original, unaltered and ordered message 
    std::string recieved_mess;
    MinHeap<std::string> sterta {};

public:

    /*Konstruktor i konstruktor kopiujący*/
    Person(std::string n, int heap_size=2, std::string m=""): sterta{heap_size} {name = n; message_to_send = m; recieved_mess="";}
    Person(const Person& P) {name = P.name; message_to_send = P.message_to_send; recieved_mess = P.recieved_mess; sterta = P.sterta;}

    void setMessage(std::string new_message) {message_to_send = new_message;}

    void generateMessage(int num_of_chars);

    void sendMessage(Person& address, int size_of_packet);

    void recieveMessage(const Packet<std::string>* message, int mess_size);

    std::string readMessage()
    {
        if (dbgopt::PRESENTATION_MODE)
        {
            std::cout << "Uporządkowana wiadomość: ";
            std::cout << recieved_mess << std::endl << std::endl;
        }
        return recieved_mess;
    }
};


/* Nie podoba mi się do końca, że aby zmienić początkowy rozmiar tablicy na której stoi sterta trzeba zmienić wartość zmiennej w default constructor
w headerze heap.hh. Spróbuj zamiast starty jako atrybutu klasy dać niezainicjalizowany wskaźnik na stertę. W kostruktorze klasy Person zaś
zdereferujesz ten wskaźnik i przypiszesz mu sterte o chcianej pojemnośći */

#endif