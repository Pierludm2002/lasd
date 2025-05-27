
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data> , virtual public ClearableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer
private:
  // ...
protected:
  using Container::size;

  struct Node {

    Data val; 
    Node *next = nullptr; 
    Node() = default; 

    /* ********************************************************************** */
    
    // Specific constructors
    Node(const Data &); 
    Node(Data &&) noexcept; 

    /* ********************************************************************** */
    // Copy constructor 
    Node(const Node &); 
    // Move constructor
    Node(Node &&) noexcept; 

    /* ********************************************************************** */
    // Destructor
    virtual ~Node(); 
    /* ********************************************************************** */

    // Comparison operators
    inline bool operator==(const Node &) const noexcept; 
    inline bool operator!=(const Node &) const noexcept; 

    /* ********************************************************************** */
    // Specific member functions
  };

  Node* head = nullptr; 
  Node* tail = nullptr; 

public:

  // Default constructor
   List() = default;

  /* ************************************************************************ */

  // Specific constructor: La map può modificare i dati, la traverse no
  List(const TraversableContainer<Data> &) ; // A list obtained from a TraversableContainer
  List( MappableContainer<Data> &&); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List &);

  // Move constructor
  List(List &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  inline List & operator=(const List &) ;

  // Move assignment
  inline List & operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const List &) const noexcept;
  inline bool operator!=(const List &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

   void InsertAtFront(const Data &); // Copy of the value
   void InsertAtFront(Data &&) ; // Move of the value
   void RemoveFromFront() ; // (must throw std::length_error when empty)
   Data FrontNRemove(); // (must throw std::length_error when empty)
   void InsertAtBack(const Data &) ; // Copy of the value
   void InsertAtBack(Data&&) ; // Move of the value
   void RemoveFromBack() ; // (must throw std::length_error when empty)
   Data BackNRemove() ; // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  inline Data & operator[](ulong) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
  inline Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline const Data & operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)
  inline const Data & Front() const override ; // Override LinearContainer member (must throw std::length_error when empty)
  inline const Data & Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  
  using typename MappableContainer<Data>::MapFun;
  inline void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  inline void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  inline void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  inline void Traverse(TraverseFun)const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
