// This file contains simple tests for UniquePTR and SharedPTR

#include <iostream>
#include "SharedPTR.h"
#include "UniquePTR.h"
#include "Testcases.h"

void testUniquePTR();
void testSharedPTR();

int main()
  {

  std::cout << "[ Some simplest testing and output for UniquePTR ]\n\n";
  testUniquePTR();

  std::cout << "\n\n[ Some simplest testing and output for SharedPTR ]\n\n";
  testSharedPTR();
  
  return 0;
  }


/// <summary>
/// In this function testcases for UniquePTR are invoked
/// </summary>
void testUniquePTR()
  {
  testcases::testUniquePTRconstructors();
  testcases::testUniquePTRreset();
  testcases::testUniquePTRoperatorAsterisk();
  testcases::testUniquePTRmoveSemanticsAndDereferencing();
  testcases::testUniquePTRrelease();
  }

/// <summary>
/// In this function testcases for SharedPTR are invoked
/// </summary>
void testSharedPTR()
  {
  testcases::testSharedPTRconstructors();
  testcases::testSharedPTRscoped();
  testcases::testSharedPTRreset();
  testcases::testSharedPTRmoveSemanticsAndDereferencing();
  testcases::testSharedPTRnullptrBehaviour();
  testcases::testSharedPTRoperatorAsterisk();
  }

