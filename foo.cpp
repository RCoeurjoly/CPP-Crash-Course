#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;

float foo( float a=0, float b=1, float c=2 ){return a+b+c;}
int main() {
  cout << foo(1) << endl << foo(1,2) << endl << foo(1,2,3) << endl;
}
