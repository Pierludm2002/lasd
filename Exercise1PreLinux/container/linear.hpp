#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */
#include "mappable.hpp"
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer :  virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data> {
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>
  //implementa 2 volte traverse() e sono anche diverse. 

private:

protected:
  using Container::size; 
public:

  // Destructor
   virtual ~LinearContainer() = default; 

  /* ************************************************************************ */
  // Copy assignment
  LinearContainer & operator=(const LinearContainer &) = delete; //la classe è astratta

  // Move assignment
  LinearContainer & operator=(LinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const LinearContainer &) const noexcept;
  inline bool operator!=(const LinearContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type operator[](argument) specifiers; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data& operator[](unsigned long)  = 0; 
  virtual const Data& operator[](unsigned long) const =0; //deve essere dichiarata anche per valori const.
  
 // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual inline Data& Front() = 0; 
  virtual inline const Data & Front() const = 0 ; 
 // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual inline const Data& Back() const = 0; 
  virtual inline Data& Back() = 0; //no const (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public LinearContainer<Data> , virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data> {
  // Must extend LinearContainer<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

protected:
  using Container::size; 
public:

  // Destructor
  ~MutableLinearContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer & operator=(const MutableLinearContainer & ) = delete ; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableLinearContainer & operator=(MutableLinearContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
   virtual Data& operator[](unsigned long) override = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)
   virtual inline Data& Front() override = 0 ; // no const(mutable version; concrete function must throw std::length_error when empty)
   virtual inline Data& Back() override = 0; // no const (mutable version; concrete function must throw std::length_error when empty)
  //  virtual const Data& operator[](unsigned long) const override = 0;
  //  virtual const Data& Front() const override = 0;
  //  virtual const Data& Back() const override = 0;
  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;
  inline void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
   inline void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  // Specific member function (inherited from PostOrderMappableContainer)
  inline void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  //espongo anche le versioni const 
   using LinearContainer<Data>::operator[]; 
   using LinearContainer<Data>::Front;
   using LinearContainer<Data>::Back;

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>

private:

protected:

public:
  // Destructor
  virtual ~SortableLinearContainer() noexcept = default; // Default destructor

  /* ************************************************************************ */

  // Copy assignment
  virtual SortableLinearContainer & operator=(const SortableLinearContainer &) = delete; // Copy assignment of abstract types is not possible.
  // Move assignment
  virtual SortableLinearContainer & operator=(SortableLinearContainer &&) noexcept = delete; // Move assignment of abstract types is not be possible.

  /* ************************************************************************ */

  // Specific member function
  virtual void Sort() = 0 ; // Sort function must be implemented by derived classes

protected:

  // Auxiliary member functions (basta solo insertion)

  void InsertionSort() ; // Insertion sort implementation
 

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
