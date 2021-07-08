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
  testUniquePTRconstructors();
  testUniquePTRreset();
  testUniquePTRoperatorAsterisk();
  testUniquePTRmoveSemanticsAndDereferencing();
  testUniquePTRrelease();
  }

/// <summary>
/// In this function testcases for SharedPTR are invoked
/// </summary>
void testSharedPTR()
  {
  testSharedPTRconstructors();
  testSharedPTRscoped();
  }

