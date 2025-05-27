#include <iostream>
#include "testSetLst.hpp"

using namespace lasd; 

void myTestSetLst() {
    std::cout << "\n--- STRESS TEST SetLst<int> ---\n";

    SetLst<int> s;

    const int N = 1000;

    std::cout << "Inserisco " << N << " valori crescenti...\n";
    for (int i = 0; i < N; ++i) {
        s.Insert(i);
        std::cout << i << "->"; 
        if(i % 20 == 0) std::cout << "\n"; 
    }

    std::cout << "\nTento di reinserire valori duplicati (dovrebbero fallire)...\n";
    for (int i = 0; i < N; i += 100) {
        bool inserted = s.Insert(i);
        std::cout << "Insert(" << i << ") duplicato: " << (inserted ? "OK" : "NO (duplicato)") << "\n";
    }

    std::cout << "\nDimensione attesa: " << N << " - ottenuta: ";
    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (s.Exists(i)) ++count;
    }
    std::cout << count << "\n";

    std::cout << "\nRimuovo ogni 10° elemento...\n";
    for (int i = 0; i < N; i += 10) {
        s.Remove(i);
    }

    std::cout << "\nProvo a stampare Min e Max...\n";
    try {
        std::cout << "Min: " << s.Min() << "\n";
        std::cout << "Min: " << s.Min() << "\n";
        std::cout << "Max: " << s.Max() << "\n";
        std::cout << "Min: " << s.Min() << "\n";

    } catch (const std::length_error& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }

    std::cout << "Min: " << s.Min() << ", Max: " << s.Max() << "\n";


    std::cout << "\nProvo a rimuovere MinNRemove e MaxNRemove...\n";
    std::cout << "Min: " << s.Min() << ", Max: " << s.Max() << "\n";
    std::cout << "Size prima: " << s.Size() << "\n";
   
    

    try {
        int min = s.MinNRemove();
        int max = s.MaxNRemove();
        std::cout << "Min rimosso: " << min << ", Max rimosso: " << max << "\n";
        std::cout << "Size dopo: " << s.Size() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
    }

   std::cout << "\nTesto Successor e Predecessor...\n";
        try {
            int testVal = 500;
            std::cout << "Successor(" << testVal << "): " << s.Successor(testVal) << "\n";
            std::cout << "Predecessor(" << testVal << "): " << s.Predecessor(testVal) << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Errore: " << e.what() << "\n";
     }

    std::cout << "\nProvo Clear()...\n";
    s.Clear();
    std::cout << "\nSize dopo Clear: " << (s.Empty() ? 0 : -1) << "\n";

    std::cout << "\n\n--- FINE STRESS TEST SetLst<int> ---\n\n";
}

void extendedTestSetLst() {
    std::cout << "\n--- TEST ESTESO SetLst<int> ---\n";

    SetLst<int> s;

    std::cout << "Inserimento di 20 valori sparsi...\n";

    int values[] = {10, 3, 5, 20, 7, 15, 2, 12, 18, 6, 9, 11, 13, 17, 1, 4, 8, 14, 16, 19};
    for (int val : values) {
        s.Insert(val);
        std::cout << val << " ";
    }
    std::cout << "\n";

    std::cout << "Stampa valori ordinati:\n";
    s.Print(); 
    

    std::cout << "\nVerifica duplicati (Insert dovrebbe fallire):\n";
    for (int val : values) {
        bool inserted = s.Insert(val);
        std::cout << "Insert(" << val << "): " << (inserted ? "OK (errore!)" : "NO (corretto)") << "\n";
    }

    std::cout << "\nTest Exists su valori esistenti e non:\n";
    std::cout << "Exists(5): " << (s.Exists(5) ? "SI" : "NO") << "\n";
    std::cout << "Exists(21): " << (s.Exists(21) ? "SI" : "NO") << "\n";

    std::cout << "\nRimuovo elementi specifici: 1, 10, 15\n";
    s.Remove(1);
    s.Remove(10);
    s.Remove(15);
    s.Print();

    std::cout << "\nRimuovo elementi non presenti: 100, 0\n";
    std::cout << "Remove(100): " << (s.Remove(100) ? "SI (errore!)" : "NO (corretto)") << "\n";
    std::cout << "Remove(0): " << (s.Remove(0) ? "SI (errore!)" : "NO (corretto)") << "\n";

    std::cout << "\nTest Min e Max:\n";
    try {
        std::cout << "Min: " << s.Min() << "\n";
        std::cout << "Max: " << s.Max() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore Min/Max: " << e.what() << "\n";
    }

    std::cout << "\nTest Successor e Predecessor su valore interno (12):\n";
    try {
        std::cout << "Successor(12): " << s.Successor(12) << "\n";
        std::cout << "Predecessor(12): " << s.Predecessor(12) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore Succ/Pred: " << e.what() << "\n";
    }

    std::cout << "\nTest Successor e Predecessor su valore mancante (10):\n";
    try {
        std::cout << "Successor(10): " << s.Successor(10) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore Successor(10): " << e.what() << "\n";
    }
    try {
        std::cout << "Predecessor(10): " << s.Predecessor(10) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore Predecessor(10): " << e.what() << "\n";
    }

    std::cout << "\nTest MinNRemove e MaxNRemove:\n";
    try {
        int min = s.MinNRemove();
        int max = s.MaxNRemove();
        std::cout << "Min rimosso: " << min << ", Max rimosso: " << max << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore MinN/MaxN: " << e.what() << "\n";
    }
    s.Print();

    std::cout << "\nClear e verifica svuotamento:\n";
    s.Clear();
    std::cout << "Set vuoto: " << (s.Empty() ? "SI" : "NO") << "\n";

    std::cout << "\n--- FINE TEST ESTESO SetLst<int> ---\n";
}


