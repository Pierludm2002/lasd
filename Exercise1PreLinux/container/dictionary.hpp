
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> {

private:

protected:

public:

  // Destructor
  ~DictionaryContainer() noexcept = default; 

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&) = delete; 
  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete; 

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer &) const noexcept = delete;
  bool operator!=(const DictionaryContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data&) = 0; //non voglio che venga modificato il valore (const) 
  virtual bool Insert(Data&&) = 0;   //rvalue
  virtual bool Remove(const Data&)  = 0;  

  virtual inline bool InsertAll(const TraversableContainer<Data>&); //stesso di sopra
  virtual inline bool InsertAll(MappableContainer<Data>&&); //rvalue
  virtual inline bool RemoveAll(const TraversableContainer<Data>&);

  virtual inline bool InsertSome(const TraversableContainer<Data>&); 
  virtual inline bool InsertSome(MappableContainer<Data>&&);
  virtual inline bool RemoveSome(const TraversableContainer<Data>&);

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~OrderedDictionaryContainer() noexcept = default; 

  /* ************************************************************************ */

  // Copy assignment
  OrderedDictionaryContainer& operator=(const OrderedDictionaryContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
   OrderedDictionaryContainer& operator=(OrderedDictionaryContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const OrderedDictionaryContainer&) noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const OrderedDictionaryContainer &) noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

    // Specific member functions tutti dovranno alzare std::lenght_error se vuote o non trovano.
    // AVRà SENSO IMPLEMENTARLE SOLO NELLA S.D.CONCRETA
  // virtual Data& Min(const OrderedDictionaryContainer&) const; // const perchè è solo in lettura
  // virtual Data& MinNRemove(OrderedDictionaryContainer& ); // non const perchè lo legge e lo rimuove (Data non è un riferimento proprio perchè sarà rimosso)
  // virtual void RemoveMin(OrderedDictionaryContainer &); 

  // virtual Data& Max(const OrderedDictionaryContainer&) const; 
  // virtual Data MaxNRemove(OrderedDictionaryContainer&);
  // virtual void RemoveMax(OrderedDictionaryContainer) ; 

  virtual Data& Min() const = 0; // const perchè è solo in lettura
  virtual Data MinNRemove() = 0; // non const perchè lo legge e lo rimuove (Data non è un riferimento proprio perchè sarà rimosso)
  virtual void RemoveMin() = 0; 

  virtual Data& Max() const = 0; 
  virtual Data MaxNRemove() = 0;
  virtual void RemoveMax() = 0 ; 

  virtual Data& Predecessor(const Data&) const = 0; // (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data&) = 0; 
  virtual void RemovePredecessor(const Data&)= 0; 

  virtual Data& Successor(const Data&) const =0; // (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data&) = 0; // (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data&) = 0; // (concrete function must throw std::length_error when not found)

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
