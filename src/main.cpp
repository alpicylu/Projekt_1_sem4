
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>
#include <random>
// #include "packet.hh"
#include "person.hh"  //person includes packet and heap
// #include "heap.hh"

void Demonstration()
{
    using namespace std;
    using namespace dbgopt;
    cout << "=-=-= Demonstracja efektów działania całego programu =-=-=-=-=-=-=-=-=-=" << endl << endl;

    string demo_message = "Once upon a time in a kingdom far, far away, the king and queen were blessed with a beautiful baby girl.";
    int poczatkowa_pojemnosc_sterty = 2;  //niska wartość w celu zaprezentowania funkcjonalnośći poszerzania tablicy
    int rozmiar_jednego_pakietu = 5;  //ilość znaków, która będzie przechowywana w jednym pakiecie.
    Person Jan("Jan", poczatkowa_pojemnosc_sterty);
    Person Anna("Anna");
    
    cout << "-- Wysyłanie średniej długości wiadomości od Jana do Anny: --" << endl;
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna, rozmiar_jednego_pakietu);
    Anna.readMessage();

    cout << "-- Wysłanie krótkiej wiadomości i ukazanie, że poprzednia długa wiadomość zwiększyła Stertę na tyle, że jest zbędna alokacja dodatkowego miejsca: --" << endl;
    demo_message = "Koń jaki jest, każdy widzi.";
    Jan.setMessage(demo_message);
    Jan.sendMessage(Anna, rozmiar_jednego_pakietu);
    Anna.readMessage();

    cout << "-- Wygenerowanie i wysłanie wiadomości o losowej treści - przydatne przy badaniu złożoności:" << endl;
    Jan.generateMessage(100);
    Jan.sendMessage(Anna, rozmiar_jednego_pakietu);
    Anna.readMessage();
}

/*Funkcja mająca za celu zbadanie złożonośći obliczeniowej kluczowej większości programu obejmującej:
    Przekształcanie wiadomości tekstowej na Pakiety
    Wymieszanie pakietów
    Przesłanie tych pakietów do innej instancji tej samej klasy (Person)
    Włożenie każdego z Pakietów z osobna do Sterty odpowiedzialnej za sortowanie
    Wyciągnięcie Pakietów z tejże starty, zgodnie z zasadami działania kolejki pryjorytetowej za pomocą funkcji dequeue()
    Przekształcenie tej wiadomości na przyjazny oczom tekst.
Funkcja ta mierzy czas wykonania tychże operacji dla coraz większych ilości pakietów.
Pomiar dla każdej ilości pakietów jest wykonywany 5-krotnie, z czego jest wyciągania średnia artym. tworząca punkt na charakterystyce. */
void MeasuringWhole()
{
    
    using namespace std;
    using namespace dbgopt;

    int poczatkowa_pojemnosc_sterty = 2;  //niska wartość w celu zaprezentowania funkcjonalnośći poszerzania tablicy
    int rozmiar_jednego_pakietu = 1;  //ilość znaków, która będzie przechowywana w jednym pakiecie.

    Person Jan("Jan", poczatkowa_pojemnosc_sterty);
    Person Anna("Anna");
    ofstream dane;

    rozmiar_jednego_pakietu = 1; //Dla uproszczenia -  jeden pakiet odpowiada jednemu znakowi wiadomości.
    const int BIG_O_START = 100;
    const int BIG_O_INCREMENT = 100;
    const int BIG_O_POINTS = 1000;

    dane.open("dane/dane_whole.csv");
    dane << "liczba_pakietow, " << "czas_1, " << "czas_2, " << "czas_3, " << "czas_4, " << "czas_5, " << "\n";
    for (int index_probki = 0; index_probki<BIG_O_POINTS; index_probki++)
    {
        dane << index_probki*BIG_O_INCREMENT + BIG_O_START << ", ";
        for (int i=0; i<5; i++)
        {
            Jan.generateMessage(index_probki*BIG_O_INCREMENT + BIG_O_START); //pomijamy czas generowania pojedyńczej wiadomości.
            auto start = chrono::high_resolution_clock::now(); //typ zmiennej zwracanej przez tą funkcje jest dosyć długi, dlatego zastosowano "auto"
            Jan.sendMessage(Anna, rozmiar_jednego_pakietu);
            auto stop = chrono::high_resolution_clock::now();
            dane << (chrono::duration<float>(stop - start).count())*1000 << ", ";  //zapisuje czas w ms.
        }
        dane << "\n";
    }
    dane.close();
}

/*Funkcja mająca za celu demonstracje wszystkich aspektów kluczowego elementu implementacji: Sterty Minimalnej (zwanej dalej MinHeap):
    1. isEmpty()
    2. Rozszerzanie sterty po przekroczeniu limitu.
    3. enqueue()
    4. dequeue() 
    5. front()*/
void DemoHeap()
{
    using namespace std;
    //1. isEmpty 
    cout << "--- isEmpty() ---" << endl;
    MinHeap<int> sterta(2);
    cout << "Wywołanie isEmpty na pustej stercie: " << sterta.isEmpty() << endl;
    sterta.enqueue(Packet<int>(1,1));
    cout << "Wywołanie isEmpty na stercie po dodaniu jednego elementu: " << sterta.isEmpty() << endl;

    //2. Rozszerzenie
    cout << "--- Rozszerzanie ---" << endl;
    cout << "Dodanie drugiego elementu (2,2) nie powoduje przekroczenia limitu, gdyż początkowy rozmiar sterty ustawiono na 2:" << endl;
    sterta.enqueue(Packet<int>(2,2));
    cout << "Pojemność sterty: " << sterta.getCapacity() << ", Aktualna il. elementów w stercie: " << sterta.size() << endl;
    cout << "Dodanie trzeciego elementu (3,3) powoduje już przekroczenie limitu:" << endl;
    sterta.enqueue(Packet<int>(3,3));
    cout << "Pojemność sterty: " << sterta.getCapacity() << ", Aktualna il. elementów w stercie: " << sterta.size() << endl;

    //3. Enqueue oraz front
    cout << "--- Enqueue & front ---" << endl;
    // cout << "Poprawnie zaimplementowana metoda enqueue sama dopilnuje, aby po dodaniu elemetu do sterty zostały zachowane jej właściwośći. " << endl;
    // cout << "MinHeap najlepiej się reprezentuje jako pełne drzewo binarne, w którym każde dziecko węzła jest większe niż sam węzeł (rodzic)" << endl;
    // cout << "W przypadku MinHeap, wartość (tutaj: pryjorytet) każdego z dzieci musi być większa niż wartość ich rodzica. " << endl;
    cout << "Poniższy przykład zareprezentuje poprawne działanie enqueue na prostym, 3-elementowym zbiorze." << endl;
    cout << "Dodano elementy: (Gamma 3), (Alfa 1), (Beta 2) w tejże kolejnośći." << endl;

    MinHeap<string> nowa(3);
    nowa.enqueue(Packet<string>("Gamma", 3));
    nowa.enqueue(Packet<string>("Alfa", 1));
    nowa.enqueue(Packet<string>("Beta", 2));
    
    cout << "Szczytowy element: " << *(nowa.front()) << endl;
    cout << "Jak można zauważyć, szczytowym elementem okazuje się (Alfa, 1), pomimo że został od dodany jako drugi." << endl;
    cout << "Oznacza to, że funkcja poprawnie dodaje elementy do stosu z zachowaniem właściwości sterty minimalnej." << endl;

    //4. Dequeue
    cout << "--- Dequeue ---" << endl;
    cout << "Funkcja dequeue zadziała poprawnie jeżeli elementy zostaną wyciągnięte ze stosu w kolejności odpowiadającej ich pryjorytetowi." << endl;
    cout << "Funkcja ta zostanie zaprezentowana na podstawie utworzonej już sterty 'nowa' z dodanymi nowymi elementami: " << endl;

    nowa.enqueue(Packet<string>("Omega", 0));
    nowa.enqueue(Packet<string>("Epsilon", 7));
    cout << *(nowa.dequeue()) << *(nowa.dequeue()) << *(nowa.dequeue()) << *(nowa.dequeue()) << *(nowa.dequeue()) << endl;

    cout << "Ze względu na dodanie więcej elementów niż pozwalał na to uprzedni limit, tablica na której zbudowany jest MinHeap zostaje znowu poszerzona" << endl;
}

void NQ_O()
{
    /*Ja może pierw napisze co che zrobc:
        Tworze nową sterte
        dodaje do niej 2000 elementów w seriach po 100 (20 punktów pomiarowych)
            Każdy element ma mieć losowy pryjorytet z jakiegośtam dużego zakresu
        mierze czas dodania każdych 100 elementów
        robie nową sterte i powtażam całą operacje zeby mieć 5 kolumn */
    /*UWAGA: złożoność chyba określa ile czasu zajmuje dana operacja w zależności od ilości elementów w strukturze. Ty tak nie zrobiłeś.*/
    /*Ty zrobiłeś ile czasu zajmuje wkładanie coraz większej ilości elementów*/
    /* najgorszy przypadek - wszystkie elementy na początku mają pryjorytet wyższy od wkładanego - nowy element musi się zbombelokować
    za każdym razem na szczyt drzewa. */
    using namespace std;

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1, 20000);
    ofstream dane;

    const int NQ_POINTS = 2000;
    const int NQ_INCREMENT = 100;
    const int NQ_START = 100;
    dane.open("dane/dane_NQ.csv");

    dane << "l. elem. w stosie, " << "czas_1, " << "czas_2, " << "czas_3, " << "czas_4, " << "czas_5, " << "\n";
    for (int i=0; i<NQ_POINTS; i++)
    {
        dane << i*NQ_INCREMENT + NQ_START << ", ";
        for (int kolumna=0; kolumna<5; kolumna++)
        {
            MinHeap<int> sterta;
            
            for (int e=0; e<(i*NQ_INCREMENT+NQ_START); e++)
            {
                sterta.enqueue(Packet<int>(1, uni(rng))); // wszystkie elementy w stosie mają większy pryj. niż ten, który włożymy ostatni.
            }
            // cout << sterta.size() << endl;
            auto start = chrono::high_resolution_clock::now();
            sterta.enqueue(Packet<int>(1, 0)); //element staje sie rootem
            auto stop = chrono::high_resolution_clock::now();
            dane << (chrono::duration<float>(stop - start).count())*1000 << ", ";
            // cout << *(sterta.front()) << endl;
        }
        dane << "\n";
    }


}

void DQ_O()
{
    /*Najgorszy przypadek DQ - ostatni element w tablicy przepisujemy na pierwsze miesce, ale ten element ma taka wartosc ze po SortHeap()
    i tak trafi na ostatnia warstwe drzewa*/
    using namespace std;

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, 19999);
    ofstream dane;

    const int DQ_POINTS = 2000;
    const int DQ_INCREMENT = 100;
    const int DQ_START = 100;
    dane.open("dane/dane_DQ.csv");

    dane << "l. elem., " << "czas_1, " << "czas_2, " << "czas_3, " << "czas_4, " << "czas_5, " << "\n";
    for (int i=0; i<DQ_POINTS; i++)
    {
        dane << i*DQ_INCREMENT+DQ_START << ", ";
        for (int kolumna=0; kolumna<5; kolumna++)
        {
            MinHeap<int> sterta;
            
            for (int e=0; e<(i*DQ_INCREMENT+DQ_START-1); e++)  //do każdego testu świerza sterta 5000 elementów
            {
                sterta.enqueue(Packet<int>(1, uni(rng)));
            }
            sterta.enqueue(Packet<int>(1, 20000));
            auto start = chrono::high_resolution_clock::now();
            sterta.dequeue();
            auto stop = chrono::high_resolution_clock::now();
            dane << (chrono::duration<float>(stop - start).count())*1000 << ", ";
        }
        dane << "\n";
    }
}

int main()
{
    // Demonstration();

    // DemoHeap();

    if (dbgopt::BIG_O)
    {
        MeasuringWhole();
        // NQ_O();
        // DQ_O();
    }

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

/* Uwagi:
    w MeasuringO mierzymy również czas wymieszania wygenerowanej odpowiedzi
    Przy rozmiarze pakietu równym 1 program nie radzi sobie z polskimi znakami.
    może dequeue powinno zwracać inny typ, np sam Packet? 
    MAKE METHODS PRIVATE
    Jak określić złożoność, jak odróżnić sqrt(n) od logn*/