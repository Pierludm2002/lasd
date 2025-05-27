#include <iostream>
#include "testSetVec.hpp"
using namespace std;
using namespace lasd;

void mytestvec() {
  SetVec<int> svec;

  cout << "Inserimento valori...\n";
//   svec.Insert(10);
//   svec.Insert(5);
//   svec.Insert(15);
//   svec.Insert(10); // duplicato
//   svec.Insert(1);
//   svec.Insert(20);
    svec.Insert(3);
    svec.Insert(7);
    svec.Insert(10);
    svec.Insert(15);
    svec.Insert(50);

  cout << "Contenuto dopo inserimenti: ";
  for (ulong i = 0; i < svec.Size(); ++i) {
    cout << svec[i] << " ";
  }
  cout << "\n";

  cout << "Elemento minimo: " << svec.Min() << endl;
  cout << "Elemento massimo: " << svec.Max() << endl;

  cout << "Successore di 10: " << svec.Successor(10) << endl;
  cout << "Predecessore di 10: " << svec.Predecessor(10) << endl;

  cout << "Rimuovo Min: " << svec.MinNRemove() << endl;
  cout << "Rimuovo Max: " << svec.MaxNRemove() << endl;

  cout << "Contenuto dopo rimozione Min e Max: ";
  for (ulong i = 0; i < svec.Size(); ++i) {
    cout << svec[i] << " ";
  }
  cout << "\n";

  cout << "Rimuovo il valore 5...\n";
  int val = 5;
  svec.Remove(val);

  cout << "Contenuto dopo Remove(5): ";
  for (ulong i = 0; i < svec.Size(); ++i) {
    cout << svec[i] << " ";
  }
  cout << "\n";

  cout << "Chiamo Clear...\n";
  svec.Clear();
  cout << "Size dopo Clear: " << svec.Size() << "\n";

  cout << "Reinserimento dopo clear...\n";
  svec.Insert(7);
  svec.Insert(3);
  svec.Insert(9);
  for (ulong i = 0; i < svec.Size(); ++i) {
    cout << svec[i] << " ";
  }
  cout << "\n";

  cout << "Test completato.\n";
}


void stresstestvec() {
    std::cout << "\n\n\n=== STRESS TEST SetVec<int> ===\n";
  
    SetVec<int> svec;
  
    const int N = 10000;
  
    std::cout << "Inserimento di " << N << " elementi...\n";
    for (int i = N; i > 0; --i) {
      svec.Insert(i); // Inserimento in ordine decrescente → stressa l'inserimento in testa
    }
  
    std::cout << "Size dopo inserimenti: " << svec.Size() << "\n";
    printSetVec100(svec); 
  
    // Verifica che sia ordinato
    bool ordered = svec.isOrdered();

    std::cout << "Ordine mantenuto? " << (ordered ? "✅ Sì" : "❌ No") << "\n";
    
  
    // Verifica Exists
    std::cout << "Exists(5000)? " << (svec.Exists(5000) ? "✅ Sì" : "❌ No") << "\n";
    std::cout << "Exists(" << N+1 << ")? " << (svec.Exists(N+1) ? "❌ Sì (bug)" : "✅ No") << "\n";
    
    // Verifica Min / Max
    try {
      std::cout << "Min: " << svec.Min() << "\n";
      std::cout << "Max: " << svec.Max() << "\n";
    } catch (const std::exception& e) {
      std::cerr << "❌ Errore Min/Max: " << e.what() << "\n";
    }
  
    // Verifica Successor / Predecessor
    try {
      std::cout << "Successor di 4999: " << svec.Successor(4999) << "\n";
      std::cout << "Predecessor di 5001: " << svec.Predecessor(5001) << "\n";
    } catch (const std::exception& e) {
      std::cerr << "❌ Errore Successor/Predecessor: " << e.what() << "\n";
    }
    
    // Rimuovi 1000 elementi via MinNRemove
    std::cout << "Rimozione di 1000 elementi dal minimo...\n";
    for (int i = 0; i < 1000; ++i) {
      svec.MinNRemove();
    }
    printSetVec100(svec); 
    std::cout << "Size dopo rimozioni: " << svec.Size() << "\n";
    std::cout << "Min ora: " << svec.Min() << "\n";
  
    // Clear e reinserimento
    std::cout << "Clear() e reinserimento...\n";
    svec.Clear();
    for (int i = 0; i < 1000; ++i) {
      svec.Insert(i * 3);
    }
    std::cout << "Size dopo reinserimento: " << svec.Size() << "\n";
    std::cout << "Min finale: " << svec.Min() << ", Max finale: " << svec.Max() << "\n";

    printSetVec100(svec); 
  
    std::cout << "=== STRESS TEST COMPLETATO ===\n";
  }
  
  void printSetVec100(SetVec<int> & svec) {
      //stampa contenuto (ogni 100 elementi)
    for (ulong i = 0; i < svec.Size(); ++i) {
        if (i % 100 == 0) {
          std::cout << svec[i] << " ";
        }
        if( i % 1000 == 999) {
          std::cout << "\n"; // Nuova riga ogni 1000 elementi
        }
      }
      std::cout << "\n";
  }

