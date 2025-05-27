
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"
#include "zmytest/testSetVec.hpp"
#include "zmytest/testSetLst.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "LASD Libraries 2025" << std::endl;
  lasdtest();

  //mytestvec(); 
  mytest(); 

  // stresstestvec();

  // myTestSetLst();
  // extendedTestSetLst();
  
  return 0;
}
