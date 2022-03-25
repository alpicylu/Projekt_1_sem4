
// #include <iostream>
#include <cmath>

#include <algorithm>
#include <random>
#include <chrono>

#include "person.hh"
#include "heap.hh"

void Person::generateMessage(int num_of_chars)
{
    using namespace std;
    string random_mess = "";
    unsigned seed;
    char rc;
    
    for (int i=0; i<num_of_chars; i++)
    {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        rc = 'a' + seed%26;
        random_mess = random_mess + rc;
    }
    message_to_send = random_mess;
}

void Person::recieveMessage(const Packet<std::string>* message, int mess_size)
{
 
    // for (int i=0; i<mess_size; i++)
    // {
    //     std::cout << message[i].getContent();
    // }
    // std::cout << std::endl;
  
    std::string out_str = "";

    MinHeap<std::string> sterta(mess_size);
    for (int i=0; i<mess_size; i++)
    {
        sterta.addElem(message[i]);
    }
    for (int i=0; i<mess_size; i++)
    {
        out_str = out_str + sterta.pop()->getContent();
    }

    recieved_mess = out_str;
}

void Person::sendMessage(Person& address, bool read_scramble)
{
    // TODO: dodaj error check na wysylanie pustej wiadomosci
    int mess_len = message_to_send.length();  //ilosc znakow w wiadomosci
    int packet_size = 5;
    int num_of_packets = ceil( float(mess_len)/float(packet_size) ); //ilosc pakietow
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    Packet<std::string> packet_arr[num_of_packets];

    int packet_index = 0; //indexy kolejnych pakietow, synonimiczne z pryjorytetem.
    for (int i=0; i<mess_len; i=i+packet_size)
    {
        std::string m = message_to_send.substr(i, packet_size);

        packet_arr[packet_index] = Packet<std::string>(m, packet_index);
        packet_index++;  //leaves at packet index one greater than the factual last index.
    }
    std::shuffle(packet_arr, packet_arr + num_of_packets, std::default_random_engine(seed));

    if (read_scramble)
    {
        std::cout << "'Zmieszana' wiadomość:   ";
        for (int i=0; i<num_of_packets; i++)
        {
            std::cout << packet_arr[i].getContent();
        }
        std::cout << std::endl;
    }


    address.recieveMessage(packet_arr, num_of_packets);

}