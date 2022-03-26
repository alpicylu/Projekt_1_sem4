
// #include <iostream>
#include <cmath>

#include <algorithm>
#include <random>
#include <chrono>

#include "person.hh"
#include "heap.hh"
#include "debug.hh"

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
    if (dbgopt::PRESENTATION_MODE)
    {
        cout << "Wygenerowana wiadomość:  ";
        cout << random_mess;
        cout << endl;
    }
    message_to_send = random_mess;
}

void Person::recieveMessage(const Packet<std::string>* message, int mess_size)
{
    if (dbgopt::PRESENTATION_MODE)
    {
        std::cout << "Rozmiar otrzymanej wiadomości (pakiety): " << mess_size <<  ", Pojemność Sterty (pakiety): " << sterta.getCapacity() << std::endl;
        std::cout << "'Zmieszana' wiadomość:   ";
        for (int i=0; i<mess_size; i++)
        {
            std::cout << message[i].getContent();
        }
        std::cout << std::endl;
    }
  
    std::string out_str = "";
    // MinHeap<std::string> sterta(mess_size); // ----- W przypadku implementacji "Jedna wiadomość - Jedna sterta"
    /*W przypadku implementacji "Jedna sterta na każdą wiadomość" -- Nie chcemy, aby poprzednia wiadomość w żaden sposób wpływała na aktualną, 
    więc resetujemy liczbe pakietów na stosie do 0. Teoretycznie, te pakiety nadal tam są, ale ze względu na taki reset, funkcja ich nie dostanie.
    Elementami tablicy, na której jest zbudowana sterta to shared_ptr<Packet<generic>>, więc nie trzeba martwić się ich dealokacją.*/
    sterta.reset(); 
    //Dodanie elementów do kolejki pryjorytetowej
    for (int i=0; i<mess_size; i++)
    {
        sterta.addElem(message[i]);
    }
    //Wyjęcie tych elementów zgodnie z pryjorytetem.
    for (int i=0; i<mess_size; i++)
    {
        out_str = out_str + sterta.pop()->getContent();
    }
    recieved_mess = out_str;
}

void Person::sendMessage(Person& address)
{
    int mess_len = message_to_send.length();  //ilosc znakow w wiadomosci
    int packet_size = 5; //ilość znaków w jednym pakiecie
    /* powodem użycia float w środku funkcji ceil jest fakt, że najczęściej wiadomość nie zostanie podzielona na pakiety o założonej długośći
    t.j. - najczęśćiej pojawi się jeden, ostatni pakiet, który będzie miał długość krótszą niż zakładana długość pakietu.
    dla przykładu: jeżeli rozmiar pakietu wynosi 2, a otrzymana wiadomość ma 5 znaków, zostanie utworzone 3 pakiety, trzeci o długośći 1. */
    int num_of_packets = ceil( float(mess_len)/float(packet_size) ); 
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();  //ziarno dla generatora dla losowego mieszania pakietów

    Packet<std::string> packet_arr[num_of_packets];

    int packet_index = 0; //indexy kolejnych pakietow, synonimiczne z pryjorytetem.

    /*Pętla odpowiedzialna za tworzenie pakietów na podstawie rozmiaru pakietu i otrzymanej wiadomości*/
    for (int i=0; i<mess_len; i=i+packet_size)
    {
        //funkcja substr() automatycznie zajmuje się tym "krótrzym" pakietem.
        std::string m = message_to_send.substr(i, packet_size);

        packet_arr[packet_index] = Packet<std::string>(m, packet_index);
        packet_index++;  //leaves at packet index one greater than the factual last index. Fix?
    }

    //Wymieszanie pakietów
    std::shuffle(packet_arr, packet_arr + num_of_packets, std::default_random_engine(seed));

    //"Wysłanie" wiadomości do innej instancji tej samej klasy
    address.recieveMessage(packet_arr, num_of_packets);
}