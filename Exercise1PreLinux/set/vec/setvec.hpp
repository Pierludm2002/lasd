
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Vector<Data>, virtual public Set<Data>, virtual public ResizableContainer{
  // Must extend Set<Data>, ResizableContainer

private:

  // ...

protected:
  ulong head = 0; 
  ulong capacity = 0; 
  using Vector<Data>::elements; 
  using Container::size;

public:

  // Default constructor
  SetVec(); 

  /* ************************************************************************ */

  // Specific constructors
  SetVec(TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetVec(MappableContainer<Data>&); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec&);

  // Move constructor
  SetVec(SetVec &&);

  /* ************************************************************************ */

  // Destructor
   ~SetVec() ;

  /* ************************************************************************ */

  // Copy assignment
  SetVec& operator=(const SetVec&);

  // Move assignment
  SetVec& operator=(SetVec&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetVec&) const noexcept;
  bool operator!=(const SetVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  Data&  Predecessor(const Data &) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(Data &) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data &&) noexcept override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override ; // Override ClearableContainer member

  //ResizableContainer 

  bool isOrdered() const noexcept; 


protected:

  long binSearch(const Data&) const; //faccio tornare l'indice (logico), -1 altrimenti
  void ResizeSet(const ulong ); 
  //long findIndexSucc(const Data&) const; 
  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
