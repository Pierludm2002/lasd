
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"
#include <utility> // mi serve per std::pair

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual public Set<Data>, virtual public List<Data>{
  // Must extend Set<Data>,
  //             List<Data>
private:
  // ...
protected:

  using Container::size;
  using List<Data>::head; 
  //using List<Data>::tail; 
  using typename List<Data>::Node;
  
public:

  // Default constructor
  SetLst();

  /* ************************************************************************ */

  // Specific constructors
  SetLst(TraversableContainer<Data>&) ; // A set obtained from a TraversableContainer
  SetLst(MappableContainer<Data>&); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetLst(const SetLst&);

  // Move constructor
  SetLst(SetLst&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetLst();

  /* ************************************************************************ */

  // Copy assignment
  SetLst& operator=(const SetLst&);

  // Move assignment
  SetLst& operator=(SetLst&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SetLst&) const noexcept;
  bool operator!=(const SetLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  Data& Successor(const Data& ) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  bool Exists(const Data& val) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Corrected to include override specifier
  void Print() const; 

protected:

  // Auxiliary functions, if necessary!
 
  typename List<Data>::Node* FindPrev(const Data&) const; 
  typename List<Data>::Node* FindPrevOfPrev(const Data&) const; 
  typename List<Data>::Node* FindSuccNode(const Data&) const;
  std::pair<typename List<Data>::Node*, typename List<Data>::Node*> FindMaxWithPrev() const; 
  typename List<Data>::Node* FindNode(const Data&) const;

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
