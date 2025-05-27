
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */
typedef unsigned long ulong;

namespace lasd {
/* ************************************************************************** */

class Container {

private:

protected:
  /* ************************************************************************ */
  unsigned long size = 0; 
  // Default constructor
  Container() = default;

public:

  // Destructor
   virtual ~Container() = default; 

  /* ************************************************************************ */
 // uso =delete per evitare di usare esplicitamente la copia e la move di Container(astratta)
  // Copy assignment
  Container & operator=(const Container &) = delete; 
  // Move assignment
  Container & operator=(Container &&) noexcept = delete;
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container &) const noexcept = delete;
  bool operator!=(const Container &) const noexcept = delete;

  /* ************************************************************************ */
  // Specific member functions
  inline virtual bool Empty() const noexcept {return (size == 0);} 
  inline virtual ulong Size() const noexcept { return size;}
};

/* ************************************************************************** */

class ClearableContainer : virtual public Container {
  // Must extend Container
private:

protected:

public:
  // Destructor
  virtual ~ClearableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer & operator = (const ClearableContainer &) = delete; 
  // Move assignment
  ClearableContainer & operator = (const ClearableContainer &&) noexcept= delete; 
  // noexcept perchè la move cambia solo 2 puntatori.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer &) const noexcept = delete;
  bool operator!=(const ClearableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual void Clear() = 0; 
};

/* ************************************************************************** */
class ResizableContainer : virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~ResizableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer & operator = (const ResizableContainer &) = delete; 
  // Move assignment
  ResizableContainer & operator = (ResizableContainer &&) noexcept = delete;  
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer &) const noexcept = delete;
  bool operator!=(const ResizableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual void Resize(unsigned long) =0;

  /* ************************************************************************ */
  // Specific member function (inherited from ClearableContainer)
  inline void Clear() override{
    Resize(0); 
  }
};

/* ************************************************************************** */

}

#endif
