
#ifndef HEAP_HH
#define HEAP_HH

#include "packet.hh"
#include <memory>

template <class generic>
class MinHeap
{
private:
    std::shared_ptr<Packet<generic>>* ptr_to_array; //Wskaźnik na tablice wskaźników na pakiet
    int size_of_array; //rozmiar całej tablicy, niezależnie ile elementów w niej jest.
    int num_of_elements;  //ilość elementów (Pakietów) w tablicy. Ilość elementów może być mniejsza niż size_of_array

public:

    /* Konstruktor. Ustala rozmiar tablicy na której MinHeap jest zbudowany i tworzy tą tablice.
        IN:
        int size - rozmiar tablicy, na której Heap jest zbudowany.
    */
    MinHeap(int size)
    {
        size_of_array = size;
        num_of_elements = 0;
        ptr_to_array = new std::shared_ptr<Packet<generic>>[size]; //this new returns a pointer to an array of pointers to Packet objects.
    }

    /* Destruktor. Kasuje zaalokowaną tablice */
    ~MinHeap() {delete[] ptr_to_array;}
    
    /* Returns index of right child node. */
    int getRight(int i) { return (2*i + 2); }

    /* Returns index of left child node. */
    int getLeft(int i) { return (2*i + 1); }

    /* Returns index of parent node. */
    int getParent(int i) { return (i-1)/2; }

    /*Dodaje element pilnujac tym samym aby została zachowana własność sterty minimalnej - rodzic mniejszy od dziecka
        IN:
          const Packet<generic>& new_elem - referencja na obiekt typu Packet, który ma zostać dodany do sterty*/
    void addElem(const Packet<generic>& new_elem)
    {
        num_of_elements++;
        int elem_ind = num_of_elements-1;
        *(ptr_to_array + elem_ind) = std::make_shared<Packet<generic>>(new_elem); //czy to na pewno nie miesza mi jakoś z oryginalną tablica/zmienną
        //TODO: dodaj check na przekroczenie rozmiaru tablicy

        //1. gdy i==0, to w stercie jest tylko 1 element, wiec juz jest posortowana.
        //2. Jako ze to jest minheap, pryjorytet rodzica MUSI być MNIEJSZY niż pryjorytet dziecka
        //czy "this" jest tutaj potrzebne
        while (elem_ind != 0 && (*(ptr_to_array + getParent(elem_ind)))->getPriority() > (*(ptr_to_array + elem_ind))->getPriority())
        {
            //Zamien elementy miejscami a potem zajmij sie rodzicem
            //Jako że tablica na której heap jest zbudowany przetrzymuje wskaźniki a nie całe dane, jedyne co się zamienia miejscami to wskaźniki na pakiety.
            std::swap( *(ptr_to_array + getParent(elem_ind)), *(ptr_to_array + elem_ind) );
            elem_ind = getParent(elem_ind);
        }
    }

    std::shared_ptr<Packet<generic>> pop() //retrieves and deletes the first element
    {
        if (num_of_elements <= 0) {
            std::cerr << "Heap empty - cannot pop()\n";
            throw -1; } //does it need a return?
        else if (num_of_elements == 1) 
        {
            num_of_elements--;
            return *(ptr_to_array);
        }

        std::shared_ptr<Packet<generic>> top_copy = getElem();  //zachowuje pierwszy element ze stosu, który zostanie zwrócony.
        *(ptr_to_array) = *(ptr_to_array + (num_of_elements-1) );  //Nadpisuje pierwszy element elementem, który jest ostatni w tablicy
        num_of_elements--; //"usuwa" ostatni element. W rzeczysistości skurcza o 1 zmienną śledzącą liczbe elementów. W praktyce ten wskaźnik nadal tam tkwi
        sortHeap(0);
        return top_copy; 
    }

    void sortHeap(int parent_index)
    {
        /*--- TERMINATION CONDITION START ---*/
        //termination conditions:
        //  if both children are bigger than parent OR
        //  if parent has no children (index of left child would be greater than num_of_elems-1)
        if ( getRight(parent_index) <= num_of_elements-1 ) //if both children exist (right child will always have higher index than left)
        {
            //if the parent has the lowest value of priority compared to its children
            if ( (*(ptr_to_array+parent_index))->getPriority() < (*(ptr_to_array+getLeft(parent_index)))->getPriority() &&
                 (*(ptr_to_array+parent_index))->getPriority() < (*(ptr_to_array+getRight(parent_index)))->getPriority() )
                 {
                    //  std::cerr << "debug1 - sortHeap"; 
                     return; //subtree is sorted
                 }   
        }
        else if ( getLeft(parent_index) > num_of_elements-1 ) {return;} //if parent has no children - tree is also sorted
        /*--- TERMINATION CONDITION END ---*/

        // TODO: dodaj sprawdzenie, czy dzieci istnieją.

        /*Ustala indeks dziecka, z którym rodzic zostanie zamieniony,zakładając oczywiscie, ze z conajmniej jednym dzieckiem mozna dokonac zamiany.
        To, czy isteje dziecko, z którym można wykonać zamiany jest sprawdzane przez blok Termination Condition.
        Algorytm wyboru dziecka do zamiany z rodzicem jest prosty:
            Jeżeli pryjorytet lewego dziecka jest mniejszy niż rodzica, indeks elementu do zamiany z rodzicem jest równy indeksowi lewego dziecka.
            Jeżeli prawe dziecko ma pryjorytet mniejszy niż lewe dziecko, indeks elementu do zamiany z rodzicem jest równy indeksowi prawego dziecka  */
        int smallest_ind = parent_index;
        if ( (*(ptr_to_array+getLeft(parent_index)))->getPriority() < (*(ptr_to_array+parent_index))->getPriority())
        {
            smallest_ind = getLeft(parent_index);
        }
        if ( (*(ptr_to_array+getRight(parent_index)))->getPriority() < (*(ptr_to_array+getLeft(parent_index)))->getPriority() )
        {
            smallest_ind = getRight(parent_index);
        }

        //dokonanie zamiany elementów w tablicy. Elementami tablicy są wskaźniki na Pakiet, więc zamienieniu miejscami ulegną tylko te wskaźniki.
        std::swap( *(ptr_to_array+smallest_ind), *(ptr_to_array+parent_index) );
        //Rekurencyjne wywołanie tego samego algorytmu dla rodzica, którego zastąpiliśmy dzieckiem (rodzic przechodzi niżej, a dziecko wyżej)
        sortHeap(smallest_ind);
    }
 
    //                                            \/usun
    std::shared_ptr<Packet<generic>> getElem(int i=0) const
    {
        return *(ptr_to_array + i);
    }
};


#endif