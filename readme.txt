* C++ crash course for C programmers

-  Author :: [[http://www.labri.fr/perso/nrougier][Nicolas P. Rougier]]

-  Sources :: [[crash-course.rst]]

** Foreword

This is an introduction to C++ for C programmers:

- If you can't understand the code below, you'd better start with a C
  tutorial.

  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
int main (int argc, char **argv)
{
  printf("Hello World!\n");
}
  #+end_src

  #+RESULTS:
  : Hello World!

- If you don't know what are the stack and the heap, you'd better have
  a look at some architecture & system introduction.
- If you know java, that might help a bit.
- If you think [[http://www.python.org][python]] is cool, you're right,
  but still, this is not the place.
- If you never heard about [[http://www2.research.att.com/~bs/][Bjarne
  Stroustrup]], you might be at the right place.
- Here is a list of C++ specific keywords:

  #+begin_quote
      asm         dynamic_cast  namespace  reinterpret_cast  try
      bool        explicit      new        static_cast       typeid
      catch       false         operator   template          typename
      class       friend        private    this              using
      const_cast  inline        public     throw             virtual
      delete      mutable       protected  true              wchar_t
  #+end_quote

** From C to C++

Even if C++ is slanted toward object-oriented programming (OOP), you can
nevertheless use any c++ compiler to compile c code and benefits from
some c++ goodies.

*** Input/Output

Prefer the use of =<iostream>= for input/output operations (see stream
section for explanation).

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    int main (int argc, char **argv)
    {
        int i;
        std::cout << "Please enter an integer value: ";
        std::cin >> i;
        std::cout << "The value you entered is " << i  << std::endl;
        return 0;
    }
#+end_src

#+RESULTS:
: Please enter an integer value: The value you entered is 0

*** New/Delete

The =new= and =delete= keywords are used to allocate and free memory.
They are "object-aware" so you'd better use them instead of =malloc= and
=free=. In any case, never cross the streams (new/free or
malloc/delete).

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    int *a = new int;
    delete a;

    int *b = new int[5];
    delete [] b;
#+end_src

#+RESULTS:

=delete= does two things: it calls the destructor and it deallocates the
memory.

*** References

A reference allows to declare an alias to another variable. As long as
the aliased variable lives, you can use indifferently the variable or
the alias.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
int x;
int& foo = x;

foo = 42;

std::cout << x << std::endl;
std::cout << foo << std::endl;
#+end_src

#+RESULTS:
| 42 |
| 42 |

References are extremely useful when used with function arguments since
it saves the cost of copying parameters into the stack when calling the
function.

*** Default parameters

You can specify default values for function parameters. When the
function is called with fewer parameters, default values are used.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
float foo( float a=0, float b=1, float c=2 )
{return a+b+c;}

using namespace std;

int main (int argc, char **argv){
  cout << foo(0) << std::endl << foo(0,2) << std::endl << foo(0,2,3) << std::endl << foo() << endl;
}
#+end_src

#+RESULTS:
| 3 |
| 4 |
| 5 |
| 3 |

You should obtain values 4, 5 and 6.

*** Namespaces

Namespace allows to group classes, functions and variable under a common
scope name that can be referenced elsewhere.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
namespace first  { int var = 5; }
namespace second { int var = 3; }
using namespace std;

int main (int argc, char **argv){
  cout << first::var << endl << second::var << endl;
}
#+end_src

#+RESULTS:
| 5 |
| 3 |

You should obtain values 3 and 5. There exists some standard namespace
in the standard template library such as std.

*** Overloading

Function overloading refers to the possibility of creating multiple
functions with the same name as long as they have different parameters
(type and/or number).

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
float add( float a, float b )
{return a+b;};

int add( int a, int b )
{return a+b;};

using namespace std;


int main(){
  int b = 0.4, c = 6.7;
  float a = add(b, c);
  cout << a << endl;
}
#+end_src

#+RESULTS:
: 6

It is not legal to overload a function based on the return type (but you
can do it
[[http://stackoverflow.com/questions/442026/function-overloading-by-return-type][anyway]])

*** Const & inline

Defines and macros are bad if not used properly as illustrated below

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #define SQUARE(x) x*x

    int result = SQUARE(3+3);
#+end_src

#+RESULTS:

For constants, prefer the const notation:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    const int two = 2;
#+end_src

#+RESULTS:

For macros, prefer the inline notation:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    int inline square(int x)
    {
        return x*x;
    }
#+end_src

#+RESULTS:

*** Mixing C and C++

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #ifdef __cplusplus
    extern "C" {
    #endif

    #include "some-c-code.h"

    #ifdef __cplusplus
    }
    #endif
#+end_src

#+RESULTS:

*** Exercises

1. Write a basic makefile for compiling sources

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/Makefile][Makefile]]

2. How would you declare:



  -  A pointer to a char
  -  A constant pointer to a char
  -  A pointer to a constant char
  -  A constant pointer to a constant char
  -  A reference to a char
  -  A reference to a constant char

  *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-2.1.cc][crash-course-2.1.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
  /*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
int main( int argc, char **argv )
{
    // Pointer to a char
    char * p1 = new char;

    // A constant pointer to a char
    char * const p2 = p1;

    // A pointer to a constant char
    const char * p3 = p1;

    // A constant pointer to a constant char
    const char * const p4 = p2;

    // A reference to a char
    char & r1 = *p2;

    // A reference to a constant char:
    const char & r2 = *p4;

    // To have no warning at compilation for unused variables
    if( *p3 == r1 ) { }
    if( *p3 == r2 ) { }

}

  #+end_src

  #+RESULTS:

3. Create a two-dimensional array of integers (size is n x n), fill it
   with corresponding indices (a[i][j] = i*n+j), test it and finally,
   delete it.


  *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-2.2.cc][crash-course-2.2.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
  /*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

int main( int argc, char **argv )
{
    const size_t n = 2;
    int **array = new int *[n];

    for( size_t i=0; i<n; ++i )
        array[i] = new int[n];

    for( size_t i=0; i<n; ++i )
        for( size_t j=0; j<n; ++j )
            array[i][j] = i*n+j;

    for( size_t i=0; i<n; ++i )
        for( size_t j=0; j<n; ++j )
            std::cout << "array[" << i << "," << j << "] = "
                      << array[i][j] << std::endl;

    for( size_t i=0; i<n; ++i )
        delete [] array[i];
    delete [] array;
}

  #+end_src

  #+RESULTS:
  | array[0 | 0] = 0 |
  | array[0 | 1] = 1 |
  | array[1 | 0] = 2 |
  | array[1 | 1] = 3 |


4. Write a function that swap two integers, then two pointers.


  *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-2.3.cc][crash-course-2.3.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
  /*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

void swap_ref( int & a, int & b )
{
    int c = a;
    a = b;
    b = c;
}

void swap_ptr( int * a, int * b )
{
    int c = *a;
    *a = *b;
    *b = c;
}

void swap_ref_ptr( int * & a, int * & b )
{
    int *c = a;
    a = b;
    b = c;
}

int main( int argc, char **argv )
{
    int i1 = 1;
    int i2 = 2;
    int * p1 = &i1;
    int * p2 = &i2;

    std::cout << "i1 = " << i1 << ", " << "i2 = " << i2 << std::endl;
    swap_ref(i1,i2);
    std::cout << "i1 = " << i1 << ", " << "i2 = " << i2 << std::endl;
    std::cout << std::endl;

    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;
    swap_ptr(p1,p2);
    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;
    std::cout << std::endl;

    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;
    swap_ref_ptr(p1,p2);
    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;

    return 0;
}

  #+end_src

  #+RESULTS:
  | i1 = 1  | i2 = 2  |
  | i1 = 2  | i2 = 1  |
  |         |         |
  | *p1 = 2 | *p2 = 1 |
  | *p1 = 1 | *p2 = 2 |
  |         |         |
  | *p1 = 1 | *p2 = 2 |
  | *p1 = 2 | *p2 = 1 |


5. Is this legal ?

   #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
       int add( int a, int b ) { return a+b; }

       int add( int a, int b, int c=0 ) { return a+b+c; }
   #+end_src

   #+RESULTS:


  *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-2.4.cc][crash-course-2.4.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
  /*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

int add( int a, int b )
{
    return a+b;
}

int add( int a, int b, int c=0 )
{
    return a+b+c;
}

int main( int argc, char **argv )
{
    // int value = add(1,2); // WRONG because this is ambiguous
    return 0;
}

  #+end_src

  #+RESULTS:


6. Write a =const correct= division function.


  *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-2.5.cc][crash-course-2.5.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
  /*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <cassert>

const double divide( const double a, const double b )
{
    assert(b != 0);
    return a/b;
}

int main( int argc, char **argv )
{
    return 0;
}

  #+end_src

  #+RESULTS:


7. What's the difference between =int const* p=, =int* const p= and
   =int const* const p= ?


  *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-2.6.cc][crash-course-2.6.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

int main( int argc, char **argv )
{
    int i1 = 1;
    int i2 = 2;

    int const *p1 = &i1;
    int *const p2 = &i1;
    int const * const p3 = &i1;

    p1 = &i2;    // OK
    // *p1 = 2;  // WRONG

    // p2 = &i2;  // WRONG
    *p2 = 2;      // OK

    // p3 = &i2;  // WRONG
    // *p3 = 2;   // WRONG

    // To have no warning at compilation for unused variables
    if( p3 == p2 ) { };

    return 0;
}

  #+end_src

  #+RESULTS:

** Classes

A class migh be considered as an extended concept of a data structure:
instead of holding only data, it can hold both data and functions. An
object is an instantiation of a class. By default, all attributes and
functions of a class are private (see below Access control). If you want
a public default behavior, you can use keyword =struct= instead of
keyword =class= in the declaration.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class Foo {
        int attribute;
        int function( void ) { };
    };

    struct Bar {
        int attribute;
        int function( void ) { };
    };

    Foo foo;
    foo.attribute = 1; // WRONG

    Bar bar;
    bar.attribute = 1;  // OK
#+end_src

#+RESULTS:

*** Constructors

It is possible to specify zero, one or more constructors for the class.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    class Foo {
    public:
        Foo( void )
        { std::cout << "First Foo constructor called" << std::endl; }
        Foo( int value )
        { std::cout << "Second Foo constructor called" << std::endl; }
    };

    int main( int argc, char **argv )
    {
        Foo foo_1, foo_2(2);
        return 0;
    }
#+end_src

#+RESULTS:
| First  | Foo | constructor | called |
| Second | Foo | constructor | called |

*** Destructor

There can be only one destructor per class. It takes no argument and
returns nothing.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    class Foo {
    public:
        ~Foo( void )
        { std::cout << "Foo destructor called" << std::endl;}

        Foo( void )
        { std::cout << "Foo constructor called" << std::endl; }
    };
    int main( int argc, char **argv )
    {
        Foo foo1;
        std::cout << "Random" << std::endl;
        return 0;
    }
#+end_src

#+RESULTS:
| Foo    | constructor | called |
| Random |             |        |
| Foo    | destructor  | called |

Note that you generally never need to explicitly call a destructor.

*** Access control

You can have fine control over who is granted access to a class function
or attribute by specifying an explicit access policy:

-  *public*: Anyone is granted access
-  *protected*: Only derived classes are granted access
-  *private*: No one but friends are granted access

*** Initialization list

Object's member should be initialized using initialization lists

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class Foo
    {
        int _value;
    public:
        Foo(int value=0) : _value(value) { };
    };
#+end_src

#+RESULTS:

It's cheaper, better and faster.

*** Operator overloading

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class Foo {
    private:
        int _value;

    public:
        Foo( int value ) : _value(value) { };

        Foo operator+ ( const Foo & other )
        {
            return Foo( _value+ other._value );
        }

        Foo operator* ( const Foo & other );
        {
            return Foo( _value * other._value );
        }
    }
#+end_src

#+RESULTS:

*** Friends

Friends are either functions or other classes that are granted
privileged access to a class.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    class Foo {
    public:
        friend std::ostream& operator<< ( std::ostream& output,
                                          Foo const & that )
        {
            return output << that._value;
        }
    private:
        double _value;
    };

    int main( int argc, char **argv )
    {
      Foo foo;
      std::cout << "Foo object: " << foo << std::endl;
      return 0;
    }
#+end_src

#+RESULTS:
: Foo object: 6.95304e-310

*** Exercices

1. Why the following code doesn't compile ?

   #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
       class Foo { Foo () { }; };

       int main( int argc, char **argv )
       {
           Foo foo;
       }
   #+end_src

   #+RESULTS:

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-3.1.cc][crash-course-3.1.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

class Foo { Foo ( void )  { }; };
struct Bar { Bar ( void ) { }; };

int main( int argc, char **argv )
{
    // Foo foo; // WRONG, constuctor is private
    Bar bar;    // OK, constructor is public

    return 0;
}

  #+end_src

  #+RESULTS:

2. Write a =Foo= class with default and copy constructors and add also
   an assignment operator. Write some code to highlight the use of each
   of them.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-3.2.cc][crash-course-3.2.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

class Foo {
private:
    int _value;


public:
    Foo( int value = 0 ) : _value(value)
    {
        std::cout << "Foo default constructor called" << std::endl;
    }

    Foo( const Foo & other )
    {
        std::cout << "Foo copy constructor called" << std::endl;
    }

    Foo & operator= ( const Foo &other )
    {
        std::cout << "Foo operator = called" << std::endl;

        // Gracefully handle self assignment
        if( this == &other ) return *this;

        _value = other._value;
        return *this;
    }

   ~Foo( void )
    {
        std::cout << "Foo destructor called" << std::endl;
    }
};

int main( int argc, char **argv )
{
    Foo foo_1(2);
    Foo foo_2(foo_1);
    Foo foo_3;
    foo_3 = foo_1;

    return 0;
}

  #+end_src

  #+RESULTS:
  | Foo | default    | constructor | called |
  | Foo | copy       | constructor | called |
  | Foo | default    | constructor | called |
  | Foo | operator   | =           | called |
  | Foo | destructor | called      |        |
  | Foo | destructor | called      |        |
  | Foo | destructor | called      |        |

3. Write a =Point= class that can be constructed using cartesian or
   polar coordinates.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-3.3.cc][crash-course-3.3.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <cmath>

class Point {
public:
    Point( void ) : _x(0.0), _y(0.0) { };

    static Point cartesian( const float x, const float y )
    { return Point( x, y ); }

    static Point polar( const float rho, const float theta )
    { return Point( rho*std::cos(theta), rho*std::sin(theta) ); }

private:
    Point( const float x, const float y ) : _x(x), _y(y)  { };
    float _x;
    float _y;
};


int main( int argc, char **argv )
{
    Point p1 = Point::cartesian(5.7, 1.2);
    Point p2 = Point::polar(5.7, 1.2);
    return 0;
}

  #+end_src

  #+RESULTS:

4. Write a =Foo= class and provide it with an input method.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-3.4.cc][crash-course-3.4.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <cmath>
#include <iostream>

class Point {
public:
    Point( void ) : _x(0.0), _y(0.0) { };

    static Point cartesian( const float x, const float y )
    { return Point( x, y ); }

    static Point polar( const float rho, const float theta )
    { return Point( rho*std::cos(theta), rho*std::sin(theta) ); }

    friend std::istream & operator >> (std::istream & input, Point & that)
    { return input >> that._x >> that._y; }

    friend std::ostream & operator << (std::ostream & output, Point & that)
    { return output << "(" << that._x << ", " << that._y << ")"; }

private:
    Point( const float x, const float y ) : _x(x), _y(y)  { };
    float _x;
    float _y;
};


int main( int argc, char **argv )
{
    Point p;
    std::cout << "Enter a new point x y: ";
    std::cin >> p;
    std::cout << "p  = " << p << std::endl;

    return 0;
}

  #+end_src

  #+RESULTS:
  | Enter a new point x y: p  = (0 | 0) |

5. Is is possible to write something like =foo.method1().method2()= ?

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-3.5.cc][crash-course-3.5.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

class Foo {
public:
    Foo ( void )
    { };

    Foo & method1( void )
    { return *this; }

    void method2( void )
    {  }
};


int main( int argc, char **argv )
{
    Foo foo;
    foo.method1().method2();

    return 0;
}

  #+end_src

  #+RESULTS:

** Inheritance

*** Basics

Inheritance is done at the class definition level by specifying the base
class and the type of inheritance.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class Foo                            { /* ... */ };
    class Bar_public : public Foo        { /* ... */ };
    class Bar_private : private Foo      { /* ... */ };
    class Bar_protected : protected Foo  { /* ... */ };
#+end_src

#+RESULTS:

=Bar_public=, =Bar_private= and =Bar_protected= are derived from =Foo=.
=Foo= is the base class of =Bar_public=, =Bar_private= and
=Bar_protected=.

-  In =Bar_public=, public parts of =Foo= are public, protected parts of
   =Foo= are protected
-  In =Bar_private=, public and protected parts of =Foo= are private
-  In =Bar_protected=, public and protected parts of =Foo= are protected

*** Virtual methods

A =virtual= function allows derived classes to replace the
implementation provided by the base class (yes, it is not automatic...).
Non virtual methods are resolved statically (at compile time) while
virtual methods are resolved dynamically (at run time).

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class Foo {
    public:
        Foo( void );
        void method1( void );
        virtual void method2( void );
    };

    class Bar : public Foo {
    public:
        Bar( void );
        void method1( void );
        void method2( void );
    };

    Foo *bar = new Bar();
    bar->method1();
    bar->method2();
#+end_src

#+RESULTS:

Make sure your destructor is virtual when you have derived class.

*** Abstract classes

You can define pure virtual method that prohibits the base object to be
instantiated. Derived classes need then to implement the virtual method.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class Foo {
    public:
        Foo( void );
        virtual void method( void ) = 0;
    };

    class Bar: public Foo {
    public:
        Foo( void );
        void method( void ) { };
    };
#+end_src

#+RESULTS:

*** Multiple inheritance

A class may inherit from multiple base classes but you have to be
careful:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class Foo               { protected: int data; };
    class Bar1 : public Foo { /* ... */ };
    class Bar2 : public Foo { /* ... */ };
    class Bar3 : public Bar1, public Bar2 {
        void method( void )
        {
           data = 1; // !!! BAD
        }
    };
#+end_src

#+RESULTS:

In class Bar3, the =data= reference is ambiguous since it could refer to
Bar1::data or Bar2::data. This problem is referred as the *diamond
problem*. You can eliminete the problem by explicitely specifying the
data origin (e.g. Bar1::data) or by using virtual inheritance in Bar1
and Bar2.

*** Exercices

1. Write a =Bar= class that inherits from a =Foo= class and makes
   constructor and destructor methods to print something when called.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-4.1.cc][crash-course-4.1.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

class Foo {
public:
    Foo( void )
    { std::cout << "Foo constructor called" << std::endl;};

    virtual ~Foo( void )
    { std::cout << "Foo destructor called" << std::endl;};
};

class Bar : public Foo {
public:
    Bar( void )
    { std::cout << "Bar constructor called" << std::endl;};

    ~Bar( void )
    { std::cout << "Bar destructor called" << std::endl;};
};

int main( int argc, char **argv )
{
    Foo * foo = new Bar();
    delete foo;

    return 0;
}

  #+end_src

  #+RESULTS:
  | Foo | constructor | called |
  | Bar | constructor | called |
  | Bar | destructor  | called |
  | Foo | destructor  | called |

2. Write a =foo= function and make it called from a class that has a
   =foo= method.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-4.2.cc][crash-course-4.2.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

void foo( void )
{ std::cout << "::foo() called" << std::endl;}

class Foo {
public:
    Foo( void )
        { ::foo(); foo(); }

    void foo( void )
    { std::cout << "Foo::foo() called" << std::endl;};

};

int main( int argc, char **argv )
{
    Foo foo;
    return 0;
}

  #+end_src

  #+RESULTS:
  | ::foo()    | called |
  | Foo::foo() | called |

3. Write a =Real= base class and a derived =Integer= class with all
   common operators (+,-,*,/)

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-4.3.cc][crash-course-4.3.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <cmath>


class Real {
public:
    Real( float value = 0 ) : _value(value) { };
    virtual Real operator+(Real &other) { return Real(_value + other._value); }
    virtual Real operator-(Real &other) { return Real(_value - other._value); }
    virtual Real operator*(Real &other) { return Real(_value * other._value); }
    virtual Real operator/(Real &other) { return Real(_value / other._value); }
    friend std::ostream& operator<< ( std::ostream& output, Real const & that )
    { return output << that._value; }
protected:
    float _value;
};

class Integer : public Real {
public:
    Integer( int value = 0 ) : Real(int(round(value))) { };
protected:
    int _value;
};



int main( int argc, char **argv )
{
    Real r1(1.23), r2(4.56);
    Integer i1(1), i2(2);

    std::cout << i1+i2 << " " << std::endl;
    std::cout << r1+r2 << " " << std::endl;
    std::cout << r1+i2 << " " << std::endl;
    std::cout << i1+r2 << " " << std::endl;

    return 0;
}

  #+end_src

  #+RESULTS:
  |    3 |
  | 5.79 |
  | 3.23 |
  | 5.56 |

4. Write a =Singleton= class such that only one object of this class can
   be created.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-4.4.cc][crash-course-4.4.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

class Singleton
{

public:
   static Singleton * instance( void )
   {
	   if( !_instance )
       {
           _instance = new Singleton;
       }
       return _instance;
   }

private:
   Singleton( void )
   { };

   Singleton( Singleton const & other )
   { };

   Singleton & operator=( Singleton const & other )
   {
       return *this;
   };

   static Singleton* _instance;
};

Singleton *Singleton::_instance = 0;

int main( int argc, char **argv )
{
    Singleton *singleton = Singleton::instance();

    delete singleton;
    return 0;
}

  #+end_src

  #+RESULTS:

5. Write a functor class

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-4.5.cc][crash-course-4.5.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

class Functor
{
    int _value;
public:
    Functor( const int value ) : _value( value ) { }
    int operator()( const int value ) { return _value+value; }
};

int main( int argc, char **argv )
{
    Functor functor(1);
    std::cout << "functor(3) = " << functor(3) << std::endl;

    return 0;
}

  #+end_src

  #+RESULTS:
  : functor(3) = 4

** Exceptions

*** The Zen of Python

(by Tim Peters)


  Beautiful is better than ugly.\\
  Explicit is better than implicit.\\
  Simple is better than complex.\\
  Complex is better than complicated.\\
  Flat is better than nested.\\
  Sparse is better than dense.\\
  Readability counts.\\
  Special cases aren't special enough to break the rules.\\
  Although practicality beats purity.\\
  *Errors should never pass silently.*\\
  *Unless explicitly silenced.*\\
  In the face of ambiguity, refuse the temptation to guess.\\
  There should be one-- and preferably only one --obvious way to do
  it.\\
  Although that way may not be obvious at first unless you're Dutch.\\
  Now is better than never.\\
  Although never is often better than /right/ now.\\
  If the implementation is hard to explain, it's a bad idea.\\
  If the implementation is easy to explain, it may be a good idea.\\
  Namespaces are one honking great idea -- let's do more of those!


*** Catch me if you can

You can catch any exception using the following structure:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    try
    {
        float *array = new float[-1];
    }
    catch( std::bad_alloc e )
    {
        std::cerr << e.what() << std::endl;
    }
#+end_src

#+RESULTS:

If the raised exception is different from the ones you're catching,
program will stop.

*** Creating your own exception

Creating a new exception is quite easy:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <stdexcept>

    class Exception : public std::runtime_error
    {
    public:
        Exception() : std::runtime_error("Exception") { };
    };
#+end_src

#+RESULTS:

*** Standard exceptions

There exist some standard exceptions that can be raised in some
circumstances:

=#include <stdexcept>=

-  bad\_alloc
-  bad\_cast
-  bad\_exception
-  bad\_typeid
-  logic\_error

   -  domain\_error
   -  invalid\_argument
   -  length\_error
   -  out\_of\_range

-  runtime\_error

   -  range\_error
   -  overflow\_error
   -  underflow\_error

*** Exercices

1. How to handle a constructor that fails ?

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-5.1.cc][crash-course-5.1.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <stdexcept>

class FooException : public std::runtime_error {
public:
    FooException( void ) : std::runtime_error("FooException")
    { }
};

class Foo {
public:
    Foo( void )
    { throw new FooException; }
};

int main( int argc, char **argv )
{
    Foo *foo = new Foo;
    return 0;
}

  #+end_src

  #+RESULTS:

2. Write a program that raise 3 of the standard exceptions.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-5.2.cc][crash-course-5.2.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <typeinfo>
#include <exception>

class Foo
{ virtual void method( void ) { } };

class Bar : public Foo
{ };

void unexpected( void )
{ throw; }

void function( void ) throw( int, std::bad_exception )
{ throw 'x'; }


int main( int argc, char **argv )
{

    // Bad alloc
    try
    {
        int * array = new int[-1];
        int i = 0;
        i = array[0];
    }
    catch( std::bad_alloc & e )
    {
        std::cerr << "bad_alloc caught: " << e.what() << std::endl;
    }

    // Bad cast
    try
    {
        Foo f;
        Bar & b = dynamic_cast<Bar &>( f );
    }
    catch( std::bad_cast & e )
    {
        std::cerr << "bad_cast caught: " << e.what() << std::endl;
    }

    // Bad exception
    std::set_unexpected( unexpected );
    try {
        function();
    }
    catch( int )
    {
        std::cerr << "caught int" << std::endl;
    }
    catch( std::bad_exception e )
    {
        std::cerr << "bad_exception caught " << e.what() << std::endl;
    }

    return 0;
}

  #+end_src

  #+RESULTS:

3. Write a correct division function.

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-5.3.cc][crash-course-5.3.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <stdexcept>

class DivideByZero : public std::runtime_error {
public:
    DivideByZero( void ) : std::runtime_error("DivideByZero")
    { }
};

const double divide( const double a, const double b )
{
    if( b == 0 )
    {
        throw DivideByZero();
    }
    return a/b;
}

int main( int argc, char **argv )
{
    divide(5,3);
    divide(5,0);
    return 0;
}

  #+end_src

  #+RESULTS:

4. Write a =Integer= (positive) class with proper exception handling
   (=Overflow=, =Underflow=, =DivideByZero=, etc.)

   *solution*: [[/home/rcl/CPP-Crash-Course/sources/crash-course-5.4.cc][crash-course-5.4.cc]]
  #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream> <cmath>) :flags -std=c++11
/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <stdexcept>
#include <cmath>

struct DivideByZero : public std::runtime_error
{ DivideByZero( void ) : std::runtime_error("DivideByZero") { } };

struct OverflowError : public std::runtime_error
{ OverflowError( void ) : std::runtime_error("OverflowError") { } };

struct UnderflowError : public std::runtime_error
{ UnderflowError( void ) : std::runtime_error("UnderflowError") { } };


class Integer {
public:
    Integer( int value = 0 ) : _value(value) { };

    virtual Integer operator+(Integer &other)
    {
        unsigned char result = _value+other._value;
        if( result < _value )
        { throw new OverflowError; }
        return Integer(result);
    }

    virtual Integer operator-(Integer &other)
    {
        unsigned char result = _value-other._value;
        if( result > _value )
        { throw new UnderflowError; }
        return Integer(result);
    }

    virtual Integer operator*(Integer &other)
    {
        unsigned char result = _value * other._value;
        if((_value > 1) and (other._value >1 ) and ( result < _value ))
        { throw new OverflowError; }
        return Integer(result);
    }

    virtual Integer operator/(Integer &other)
    {
        if( other._value == 0 )
        { throw new DivideByZero; }

        return Integer(_value / other._value);
    }

    friend std::ostream& operator<< ( std::ostream& output, Integer const & that )
    { return output << that._value; }
protected:
    unsigned char _value;
};

int main( int argc, char **argv )
{
    Integer a(129), b(128), zero(0);

    Integer c(a+b); // overflow
    Integer d(b-a); // underflow
    Integer e(a/zero); // divide by zero

    return 0;
}

  #+end_src

  #+RESULTS:

** Streams

C++ provides input/output capability throught the iostream classes that
provide the stream concept (iXXXstream for input and oXXXstream for
output).

*** iostream and ios

Screen outputs and keyboard inputs may be handled using the iostream
header file:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    using namespace std;

    int main( int argc, char **argv )
    {

        unsigned char age = 65;
        std::cout << static_cast<unsigned>(age)     << std::endl;
        std::cout << static_cast<void const*>(&age) << std::endl;

        double f = 3.14159;
        cout.unsetf(ios::floatfield);
        cout.precision(5);
        cout << f << endl;
        cout.precision(10);
        cout << f << endl;
        cout.setf(ios::fixed,ios::floatfield);
        cout << f << endl;

        std::cout << "Enter a number, or -1 to quit: ";
        int i = 0;
        while( std::cin >> i )
        {
            if (i == -1) break;
            std::cout << "You entered " << i << '\n';
        }
        return 0;
    }
#+end_src

#+RESULTS:
|             65 |   |         |    |    |    |       |
| 0x7ffc2b35a6db |   |         |    |    |    |       |
|         3.1416 |   |         |    |    |    |       |
|        3.14159 |   |         |    |    |    |       |
|        3.14159 |   |         |    |    |    |       |
|          Enter | a | number, | or | -1 | to | quit: |

*** Class input/output

You can implement a class input and output using friends functions:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    class Foo {
    public:
        friend std::ostream& operator<< ( std::ostream & output, Foo const & that )
        { return output << that._value; }
        friend std::istream& operator>> ( std::istream & input, Foo& foo )
        { return input >> fred._value; }

    private:
        double _value;
    };
#+end_src

#+RESULTS:

*** Working with files

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <fstream>

    int main( int argc, char **argv )
    {
        std::ifstream input( filename );
        // std::ifstream input( filename, std::ios::in | std::ios::binary);

        std::ofstream output( filename );
        // std::ofstream output( filename, std::ios::out | std::ios::binary);

        return 0;
    }
#+end_src

#+RESULTS:

*** Working with strings

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <sstream>

    int main( int argc, char **argv )
    {
        const char *svalue = "42.0";
        int ivalue;
        std::istringstream istream;
        std::ostringstream ostream;

        istream.str(svalue);
        istream >> ivalue;
        std::cout << svalue << " = " << ivalue << std::endl;

        ostream.clear();
        ostream << ivalue;
        std::cout << ivalue << " = " << ostream.str() << std::endl;

        return 0;
    }
#+end_src

#+RESULTS:
| 42.0 | = | 42 |
|   42 | = | 42 |

*** Exercices

1. Write an =itoa= and an =atoi= function
2. Write a foo class with some attributes and write functions for
   writing to file and reading from file.

** Templates

Templates are special operators that specify that a class or a function
is written for one or several generic types that are not yet known. The
format for declaring function templates is:

-  template <typename identifier> function\_declaration;
-  template <typename identifier> class\_declaration;

You can have several templates and to actually use a class or function
template, you have to specify all unknown types:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    template<typename T1>
    T1 foo1( void ) { /* ... */ };

    template<typename T1, typename T2>
    T1 foo2( void ) { /* ... */ };

    template<typename T1>
    class Foo3 { /* ... */ };


    int a = foo1<int>();
    float b = foo2<int,float>();
    Foo<int> c;
#+end_src

#+RESULTS:

*** Template parameters

There are three possible template types:

-  *Type*


     #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
         template<typename T>  T foo( void ) { /* ... */ };
     #+end_src

     #+RESULTS:


-  *Non-type*


     #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
         template<int N>  foo( void ) { /* ... */ };
     #+end_src

     #+RESULTS:


-  *Template*


     #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
         template< template <typename T> > foo( void ) { /* ... */ };
     #+end_src

     #+RESULTS:


*** Template function

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    template <class T>
    T max( T a, T b)
    {
        return( a > b ? a : b );
    }

    #include <sstream>

    int main( int argc, char **argv )
    {
        std::cout << max<int>( 2.2, 2.5 ) << std::endl;
        std::cout << max<float>( 2.2, 2.5 ) << std::endl;
    }
#+end_src

#+RESULTS:
|   2 |
| 2.5 |

*** Template class

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    template <class T>
    class Foo {
        T _value;

    public:
        Foo( T value ) : _value(value) { };
    }

    int main( int argc, char **argv )
    {
        Foo<int> foo_int;
        Foo<float> foo_float;
    }
#+end_src

#+RESULTS:

*** Template specialization

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    template <class T>
    class Foo {
        T _value;
    public:
        Foo( T value ) : _value(value)
        {
            std::cout << "Generic constructor called" << std::endl;
        };
    }

    template <>
    class Foo<float> {
        float _value;
    public:
        Foo( float value ) : _value(value)
        {
            std::cout << "Specialized constructor called" << std::endl;
        };
    }

    int main( int argc, char **argv )
    {
        Foo<int> foo_int;
        Foo<float> foo_float;
    }
#+end_src

#+RESULTS:

*** Exercices

1. Write a generic swap function
2. Write a generic point structure
3. Write templated factorial, power and exponential functions (exp(x) =
   sum\_n x\^n/n!, exp(-x) = 1/exp(x))
4. Write a smart pointer class

** Standard Template Library

*** Containers

STL containers are template classes that implement various ways of
storing elements and accessing them.

*Sequence containers*:

-  vector
-  deque
-  list

*Container adaptors*:

-  stack
-  queue
-  priority\_queue

*Associative containers*:

-  set
-  multiset
-  map
-  multimap
-  bitset

See [[http://www.cplusplus.com/reference/stl/]] for more information.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <vector>
    #include <map>
    #include <string>

    using namespace std;

    int main( int argc, char **argv )
    {
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);

        map<string,int> m;
        m["one"] = 1;
        m["two"] = 2;
        m["three"] = 3;
        cout<< "Say " << m["one"] << endl;
        return 0;
    }
#+end_src

#+RESULTS:
: Say 1

*** Iterators

Iterators are a convenient tool to iterate over a container:

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <map>
    #include <string>
    #include <iostream>

    int main( int argc, char **argv )
    {
        std::map<std::string,int> m;
        m["one"] = 1;
        m["two"] = 2;
        m["three"] = 3;

        std::map<std::string,int>::iterator iter;
        for( iter=m.begin(); iter != m.end(); ++iter )
        {
            std::cout << "map[" << iter->first << "] = "
                      << iter->second << std::endl;
        }
        return 0;
    }
#+end_src

#+RESULTS:
| map[one]   | = | 1 |
| map[three] | = | 3 |
| map[two]   | = | 2 |

*** Algorithms

Algorithms from the STL offer fast, robust, tested and maintained code
for a lot of standard operations on ranged elements. Don't reinvent the
wheel !

Have a look at [[http://r0d.developpez.com/articles/algos-stl-fr/]]
(French) and [[http://www.cplusplus.com/reference/algorithm/]] for an
overview.

#+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <vector>
    #include <algorithm>

    bool compare( const int & first, const int  & second )
    {
        return (first < second);
    }

    int main( int argc, char **argv )
    {
        std::vector<int> v(10);
        std::sort(v.begin(), v.end(), &compare);

        return 0;
    }
#+end_src

#+RESULTS:

*** Exercices



  1. Write a template stack class using the STL vector class
  2. Write a generic vector class with iterators and benchmark it againt
     the STL vector class

** C++ exam

 Name:

*** Extern

 The code below declares and defines variable x. *True* or *False* ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11

extern int x;

int main(int argc, char** argv)
{
    return 0;
}

 #+end_src

*** Namespace

 In namespace foo, the function bar can access the variable x also
 declared in namespace foo ? *True* or *False* ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    namespace foo
    {
        void bar()
        {
            x++;
        }
        int x;
    }

    int main(int argc, char** argv)
    {
        return 0;
    }
 #+end_src

*** References

 What is the output of the following program ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>
    using namespace std;

    void swap1( int  a, int  b ) { int c=a; a=b; b=c; }
    void swap2( int *a, int *b ) { int c=*a; *a=*b; *b=c; }
    void swap3( int &a, int &b ) { int &c=a; a=b; b=c; }

    int main( int argc, char **argv )
    {
        int a, b;

        a = 1; b = 2; swap1(a,b);
        cout << "a: " << a << ", " <<"b: " << b << endl;

        a = 1; b = 2; swap2(&a,&b);
        cout << "a: " << a << ", " <<"b: " << b << endl;

        a = 1; b = 2; swap3(a,b);
        cout << "a: " << a << ", " <<"b: " << b << endl;
    }
 #+end_src

*** Inheritance

 What is the output of the program ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    struct A { unsigned int color; };
    struct B : public A { };
    struct C : public A { };
    struct D : public B, public C { };

    int main(int argc, char** argv)
    {
       D d;
       d.color = 3;
       std::cout << d.color << std::endl;
       return 0;
    }
 #+end_src

*** Inheritance

 How many times is "Hello World" printed by this program ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    struct A { A() {  std::cout << "Hello World" << std::endl; } };
    struct A1 : public A { };
    struct A2 : public A { };
    struct A3 : public A { };
    struct A4 : public A { };
    struct B : public A1, public A2, public A3, public A4 { };

    int main(int argc, char** argv)
    {
        B b;
        return 0;
    }
 #+end_src

*** Initialization

 What is the value of x, y & z ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    struct A
    {
      A(int n) : x(n++), y(n++), z(n++) {}
      int x;
      int y;
      int z;
    };

    int main(int argc, char** argv)
    {
      Foo f(3);

      std::cout << "x: " << f.x << std::endl;
      std::cout << "y: " << f.y << std::endl;
      std::cout << "z: " << f.z << std::endl;

      return 0;
    }
 #+end_src

*** Logic

 What value gets printed by the program?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    int main(int argc, char** argv)
    {
      int x = 0;
      int y = 0;

      if (x++ && y++)
      {
        y += 2;
      }

      std::cout << x + y << std::endl;

      return 0;
    }
 #+end_src

*** Constructors

 Which lines below should not compile ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    struct A
    {
       A(int x) : n(x) {}
       int n;
    };

    int main(int argc, char** argv)
    {
      A a1;
      A a2(2);
      A a3(a2);
      return 0;
    }
 #+end_src

*** Memory

 Which of the following implementations of the reset function is best for
 initializing the array to all zero.

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    class foo{
    public:
        foo(){
            reset();
        }
    private:
        void reset(){

        // A // memset(x, 0, 50);
        // B // memset(x, 0, sizeof(x));
        // C // memset(x, 0, 50 * 4);
        // D // memset(x, 0, 50 * sizeof(x));
        }

        long x[50];
    };
 #+end_src

*** References

 What is the output of the program ?

 #+begin_src C++ :includes '(<stdio.h> <algorithm> <string> <map> <sstream> <fstream> <stdexcept> <vector> <numeric> <iostream>) :flags -std=c++11
    #include <iostream>

    int main(int argc, char** argv)
    {
      // assume address of x is 0x822222222
      int x = 3;

      int*& rpx = &x;

      std::cout << rpx << std::endl;

      return 0;
    }
 #+end_src

*** End

** External links

 -  C++ FAQ --- Frequently Asked Questions\\
    [[http://www.parashift.com/c++-faq-lite/]]
 -  Boost free peer-reviewed portable C++ source libraries\\
    [[http://www.boost.org/]]
 -  Bjarne Stroustrup homepage\\
    [[http://www2.research.att.com/~bs/]]
 -  Complete reference on C++ Standard Library\\
    [[http://en.cppreference.com/w/cpp]]
 -  C++11 main features\\
    [[http://en.wikipedia.org/wiki/C%2B%2B11]]
 -  The definitive C++ book guide\\
    [[http://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list]]
 -  comp.lang.c++\\
    [[http://groups.google.com/group/comp.lang.c++/topics]]
 -  GNU make\\
    [[http://www.gnu.org/s/make/manual/make.html]]
 -  Les meilleurs cours et tutoriaux (in *French* as you may have already
    guessed...)\\
    [[http://cpp.developpez.com/cours/]]
