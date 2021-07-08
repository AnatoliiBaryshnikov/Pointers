// Testcases are mainly taken from https://www.cplusplus.com/
// 
// Yeah, this header contains both declarations and definitions. 
// It is for simplification in this particular case.

#pragma once
#ifndef TESTCASES
#define TESTCASES

#include <iostream>
#include "SharedPTR.h"
#include "UniquePTR.h"

/// <summary>
/// Class for testing UniquePTR
/// </summary>
class ItemUnique
  {
    public:
    ItemUnique() { std::cout << "ItemUnique created\n"; }
    ~ItemUnique() { std::cout << "ItemUnique destroyed\n"; }
  };

/// <summary>
/// Class for testing SharedPTR
/// </summary>
class ItemShared
  {
    public:
    ItemShared() { std::cout << "ItemShared created\n"; }
    ~ItemShared() { std::cout << "ItemShared destroyed\n"; }
  };

struct S { int* data; };

void testUniquePTRconstructors()
  {
  std::cout << "\n >> testing UniquePTR constructors\n";
  UniquePTR<int> u1;
  UniquePTR<int> u2(nullptr);
  UniquePTR<int> u3(new int);
  UniquePTR<int> u5(new int(0));
  UniquePTR<int> u6(std::move(u5));
  UniquePTR<int> u7(std::move(u6));

  std::cout << "u1: " << (u1 ? "failed - not null" : "passed") << '\n';
  std::cout << "u2: " << (u2 ? "failed - not null" : "passed") << '\n';
  std::cout << "u3: " << (u3 ? "passed" : "failed - null") << '\n';
  std::cout << "u5: " << (u5 ? "failed - not null" : "passed") << '\n';
  std::cout << "u6: " << (u6 ? "failed - not null" : "passed") << '\n';
  std::cout << "u7: " << (u7 ? "passed" : "failed - null") << '\n';
  }

void testUniquePTRreset()
  {
  std::cout << "\n >> testing UniquePTR .reset()\n";
  std::cout << "  > ItemUnique must be created...\n";
  UniquePTR<ItemUnique> up(new ItemUnique());

  std::cout << "  > ItemUnique must be created...\n";
  up.reset(new ItemUnique());

  std::cout << "  > ... ItemUnique has been destroyed\n";
  std::cout << "  > ItemUnique must be destroyed...\n";

  }

void testUniquePTRoperatorStar()
  {
  std::cout << "\n >> testing UniquePTR operator *\n";
  UniquePTR<int> foo(new int);
  UniquePTR<int> bar(new int(100));

  *foo = *bar * 2;

  std::cout << "foo: " << (*foo == 200 ? "passed" : "failed") << '\n';
  std::cout << "bar: " << (*bar == 100 ? "passed" : "failed") << '\n';
  }


struct C { int a; int b; };

void testUniquePTRmoveSemanticsAndDereferencing()
  {
  std::cout << "\n >> testing UniquePTR operator ->\n";
  UniquePTR<C> foo(new C);
  UniquePTR<C> bar;

  foo->a = 10;
  foo->b = 20;

  std::cout << (bar ? "failed" : "passed") << '\n';

  bar = std::move(foo);

  std::cout << (foo ? "failed" : "passed") << '\n';
  std::cout << (bar ? "passed" : "failed") << '\n';

  std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';
  }

void testUniquePTRrelease()
  {
  std::cout << "\n >> testing UniquePTR .release()\n";
  UniquePTR<int> auto_pointer(new int);
  int* manual_pointer;

  *auto_pointer = 10;

  manual_pointer = auto_pointer.release();

  std::cout << "manual_pointer points to " << *manual_pointer << '\n';

  std::cout << (auto_pointer ? "failed" : "passed") << '\n';

  }


void testSharedPTRconstructors()
  {
  std::cout << "\n >> testing SharedPTR constructors\n";
  std::shared_ptr<int> p1;
  std::shared_ptr<int> p2(nullptr);
  std::shared_ptr<int> p3(new int);
  std::shared_ptr<int> p5(new int(10));
  std::shared_ptr<int> p6(p5);
  std::shared_ptr<int> p7(std::move(p6));
  std::shared_ptr<S> obj(new S);

  std::cout << (p1.use_count() == 0 ? "passed" : "failed") << '\n';
  std::cout << (p2.use_count() == 0 ? "passed" : "failed") << '\n';
  std::cout << (p3.use_count() == 1 ? "passed" : "failed") << '\n';
  std::cout << (p5.use_count() == 2 ? "passed" : "failed") << '\n';
  std::cout << (p6.use_count() == 0 ? "passed" : "failed") << '\n';
  std::cout << (p7.use_count() == 2 ? "passed" : "failed") << '\n';
  std::cout << (obj.use_count() == 1 ? "passed" : "failed") << '\n';
  }

void testSharedPTRscoped()
  {
  std::cout << "\n >> testing SharedPTR scoped\n";
  std::cout << "  > ItemShared must be created...\n";

  SharedPTR<ItemShared> uptr1(new ItemShared());

  std::cout << (uptr1.useCount() == 1 ? "passed" : "failed") << "\n";

    {
    SharedPTR<ItemShared> uptr2(uptr1);
    std::cout << (uptr1.useCount() == 2 ? "passed" : "failed") << "\n";
    std::cout << (uptr2.useCount() == 2 ? "passed" : "failed") << "\n";
    }

  std::cout << (uptr1.useCount() == 1 ? "passed" : "failed") << "\n";

  std::cout << "  > ItemShared must be destroyed...\n";
  }

#endif // !TESTCASES