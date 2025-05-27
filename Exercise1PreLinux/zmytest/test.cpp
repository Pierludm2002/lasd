#include <iostream>
#include <chrono>
#include <stdexcept>
#include "../vector/vector.hpp"
#include "../list/list.hpp"

using namespace std;
using namespace lasd;
void mytest() {
    std::cout << "\n--- TEST COMPLETO List<int> ---\n";

    lasd::List<int> lst;

    std::cout << "Inserimento in coda: 10, 20, 40\n";
    lst.InsertAtBack(10);
    lst.InsertAtBack(20);
    lst.InsertAtBack(40);

    std::cout << "Inserimento in testa: 5\n";
    lst.InsertAtFront(5);


    std::cout << "Contenuto lista: ";
    for (ulong i = 0; i < lst.Size(); ++i) std::cout << lst[i] << " ";
    std::cout << "\n";

    std::cout << "Front: " << lst.Front() << ", Back: " << lst.Back() << "\n";

    std::cout << "FrontNRemove: " << lst.FrontNRemove() << "\n";
    std::cout << "BackNRemove: " << lst.BackNRemove() << "\n";

    std::cout << "Contenuto dopo rimozioni estreme: ";
    for (ulong i = 0; i < lst.Size(); ++i) std::cout << lst[i] << " ";
    std::cout << "\n";

    

    std::cout << "Contenuto dopo rimozione in mezzo: ";
    for (ulong i = 0; i < lst.Size(); ++i) std::cout << lst[i] << " ";
    std::cout << "\n";

    std::cout << "Size finale: " << lst.Size() << "\n";

    lasd::List<int> lstCopy(lst);
    std::cout << "Copy == originale? " << ((lstCopy == lst) ? "SI" : "NO") << "\n";
    std::cout << "Copy != originale? " << ((lstCopy != lst) ? "SI" : "NO") << "\n";

    std::cout << "Clear e verifica Empty...\n";
    lst.Clear();
    std::cout << "Empty? " << (lst.Empty() ? "SI" : "NO") << "\n";

    std::cout << "--- FINE TEST List<int> ---\n";

    std::cout << "\n--- TEST COMPLETO Vector<int> ---\n";

    lasd::Vector<int> vec(5);
    for (ulong i = 0; i < 5; ++i) vec[i] = i * 10;

    std::cout << "Contenuto iniziale: ";
    for (ulong i = 0; i < vec.Size(); ++i) std::cout << vec[i] << " ";
    std::cout << "\n";

    std::cout << "Front: " << vec.Front() << ", Back: " << vec.Back() << "\n";

    std::cout << "Resize a 10 e aggiunta nuovi valori...\n";
    vec.Resize(10);
    for (ulong i = 5; i < 10; ++i) vec[i] = i * 10;

    std::cout << "Contenuto dopo resize: ";
    for (ulong i = 0; i < vec.Size(); ++i) std::cout << vec[i] << " ";
    std::cout << "\n";

    std::cout << "Copy e verifica uguaglianza...\n";
    lasd::Vector<int> vecCopy(vec);
    std::cout << "Copy == originale? " << ((vecCopy == vec) ? "SI" : "NO") << "\n";

    std::cout << "Clear e verifica Empty...\n";
    vec.Clear();
    std::cout << "Empty? " << (vec.Empty() ? "SI" : "NO") << "\n";

    std::cout << "--- FINE TEST Vector<int> ---\n";
}

