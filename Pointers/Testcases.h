// Testcases are mainly taken from https://www.cplusplus.com/
//

#pragma once
#ifndef TESTCASES
#define TESTCASES

#include <iostream>
#include "SharedPTR.h"
#include "UniquePTR.h"

/// <summary>
/// This namespace contains testing functions for UniquePTR and SharedPTR
/// </summary>
namespace testcases {

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

  void testUniquePTRoperatorAsterisk()
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
    std::cout << "\n >> testing UniquePTR operator -> and move semantics\n";
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

  struct S { int* data; };

  void testSharedPTRconstructors()
    {
    std::cout << "\n >> testing SharedPTR constructors\n";
    SharedPTR<int> p1;
    SharedPTR<int> p2(nullptr);
    SharedPTR<int> p3(new int);
    SharedPTR<int> p5(new int(10));
    SharedPTR<int> p6(p5);
    SharedPTR<int> p7(std::move(p6));
    SharedPTR<S> obj(new S);

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

    std::cout << (uptr1.use_count() == 1 ? "passed" : "failed") << "\n";

      {
      SharedPTR<ItemShared> uptr2(uptr1);
      std::cout << (uptr1.use_count() == 2 ? "passed" : "failed") << "\n";
      std::cout << (uptr2.use_count() == 2 ? "passed" : "failed") << "\n";
      }

    std::cout << (uptr1.use_count() == 1 ? "passed" : "failed") << "\n";

    std::cout << "  > ItemShared must be destroyed...\n";
    }

  void testSharedPTRreset()
    {
    std::cout << "\n >> testing SharedPTR .reset() \n";

    SharedPTR<int> sp;

    sp.reset(new int);
    *sp = 10;
    std::cout << (*sp == 10 ? "passed" : "failed") << '\n';

    sp.reset(new int);
    *sp = 20;
    std::cout << (*sp == 20 ? "passed" : "failed") << '\n';

    sp.reset();
    std::cout << (sp.get() == nullptr ? "passed" : "failed") << '\n';
    std::cout << (sp.use_count() == 0 ? "passed" : "failed") << '\n';

    sp.reset(new int);
    *sp = 30;

    sp.reset(nullptr);
    std::cout << (sp.get() == nullptr ? "passed" : "failed") << '\n';
    std::cout << (sp.use_count() == 0 ? "passed" : "failed") << '\n';

    }

  void testSharedPTRmoveSemanticsAndDereferencing()
    {
    std::cout << "\n >> testing SharedPTR operator -> and move semantics\n";
    SharedPTR<C> foo(new C);
    SharedPTR<C> bar;

    foo->a = 10;
    foo->b = 20;

    std::cout << (bar ? "failed" : "passed") << '\n';

    bar = std::move(foo);

    std::cout << (foo ? "failed" : "passed") << '\n';
    std::cout << (bar ? "passed" : "failed") << '\n';
    std::cout << (foo.get() == nullptr ? "passed" : "failed") << '\n';
    std::cout << (foo.use_count() == 0 ? "passed" : "failed") << '\n';
    std::cout << (bar.use_count() == 1 ? "passed" : "failed") << '\n';

    std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';
    }

  void testSharedPTRnullptrBehaviour()
    {
    std::cout << "\n >> testing SharedPTR nullptr behaviour\n";
    SharedPTR<int> p1(nullptr);
    SharedPTR<int> p2(p1);
    SharedPTR<int> p3(nullptr);
    SharedPTR<int> p5 = p3;
    SharedPTR<int> p6(nullptr);
    SharedPTR<int> p7(std::move(p6));
    
    std::cout << (p1.use_count() == 0 ? "passed" : "failed") << '\n';
    std::cout << (p1.get() == nullptr ? "passed" : "failed") << '\n';
    std::cout << (p2.use_count() == 0 ? "passed" : "failed") << '\n';
    std::cout << (p3.use_count() == 0 ? "passed" : "failed") << '\n';
    std::cout << (p5.use_count() == 0 ? "passed" : "failed") << '\n';
    std::cout << (p6.use_count() == 0 ? "passed" : "failed") << '\n';
    std::cout << (p7.use_count() == 0 ? "passed" : "failed") << '\n';
    }

  void testSharedPTRoperatorAsterisk()
    {
    std::cout << "\n >> testing SharedPTR operator *\n";

    SharedPTR<int> foo(new int);
    SharedPTR<int> bar(new int(100));

    *foo = *bar * 2;

    std::cout << "foo: " << (*foo == 200 ? "passed" : "failed") << '\n';
    std::cout << "bar: " << (*bar == 100 ? "passed" : "failed") << '\n';
    }

  }
#endif // !TESTCASES