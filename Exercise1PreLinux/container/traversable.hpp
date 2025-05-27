
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer: virtual public TestableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~TraversableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer<Data>& operator=(const TestableContainer<Data>&) = delete; 
  // Move assignment
  TraversableContainer<Data>& operator=(TestableContainer<Data>&&) noexcept = delete; 
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer<Data>&) const noexcept = delete; 
  bool operator!=(const TraversableContainer<Data>&) const noexcept = delete;
  
  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) const =0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &,  Accumulator &)>;

  template <typename Accumulator>
  inline Accumulator Fold(typename TraversableContainer<Data>::template FoldFun<Accumulator>,Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer &) = delete ; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderTraversableContainer&  operator=(PreOrderTraversableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators (ha senso solo nelle classi concrete)
  virtual bool operator==(PreOrderTraversableContainer & ) const noexcept = delete; // Comparison of abstract types might be possible.
  virtual bool operator!=(PreOrderTraversableContainer & ) const noexcept = delete; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void PreOrderTraverse(TraverseFun) const = 0;

  ///  
  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  inline Accumulator PreOrderFold(typename TraversableContainer<Data>::template FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data>{
  // Must extend TraversableContainer<Data>

private:

protected:

public:

  // Destructor
  ~PostOrderTraversableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer& operator=(const PostOrderTraversableContainer &) = delete;  // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderTraversableContainer& operator=(PostOrderTraversableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(PostOrderTraversableContainer&) noexcept ; // Comparison of abstract types might be possible.
  bool operator!=(PostOrderTraversableContainer &) noexcept; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  inline Accumulator PostOrderFold(typename TraversableContainer<Data>::template FoldFun<Accumulator>, Accumulator) const;


  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
