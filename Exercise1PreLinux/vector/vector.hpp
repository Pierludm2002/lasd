
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */


template <typename Data>
class Vector : virtual public ResizableContainer, virtual public MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer
private:

  // ...

protected:
  using Container::size;
  Data * elements = nullptr; 
public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
   Vector(ulong size); // A vector with a given initial dimension
   Vector(TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
   Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector&);
  // Move constructor
   Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector &);

  // Move assignment
   Vector & operator=(Vector &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector&) const noexcept;
  bool operator!=(const Vector&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // type operator[](argument) specifiers; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](unsigned long) override; 
  // type Front() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  Data& Front() override; 
  // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  Data& Back() override; 
  

  void Print() const; 
  
  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
  const Data& operator[](unsigned long) const override; 
  const Data& Front() const override;
  const Data& Back() const override;
  // type operator[]() specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  void Resize(ulong u) override; 
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; 

  /* ************************************************************************ */

  using typename MutableLinearContainer<Data>::MapFun;

   void Map(MapFun) override;
   void PreOrderMap(MapFun) override;  
   void PostOrderMap(MapFun) override;

protected:
  // Auxiliary functions, if necessary!
};

/* ************************************************************************** */

template <typename Data>
class SortableVector : public Vector<Data>, public SortableLinearContainer<Data>{

private:

protected:
  using Container::size;

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(ulong size); // A vector with a given initial dimension
  SortableVector(TraversableContainer<Data> &) ; // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data> &&) ; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector &) ;
  // Move constructor
  SortableVector(SortableVector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector<Data> & operator=(const SortableVector<Data> & );
  // Move assignment
  SortableVector<Data> & operator=(SortableVector<Data> &&) noexcept;

  void Sort() override; 
  
protected:

  void InsertionSort();  // Auxiliary functions, if necessary!
 
};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
