// sandbox_idea: cpp/basics
// sandbox_name: float_comparison
// sandbox_description: error dloat comparison
// sandbox_env: cpp

#include <iostream>
using namespace std;

int main() {
  // float conversion is inaccurate, never compare 2 floats or 2 doubles
  // directly
  //=============================================================================
  // Example showing float compare NOT working
  double num1_float{100.00f - 99.99f}; // num1_float should be equal to 0.01
  double num2_float{10.00f - 9.99f};   // num2_float should be equal to 0.01
  cout << "num1_float: " << num1_float << endl
       << "num2_float: " << num2_float << endl;
  if (num1_float == num2_float)
    cout << "COMPARE FLOATS: Both numbers are equal - PASS" << endl;
  else if (num1_float > num2_float)
    cout << "COMPARE FLOATS: First number is greater than the second - FAIL"
         << endl;
  else if (num1_float < num2_float)
    cout << "COMPARE FLOATS: First number is less than the second - FAIL"
         << endl;
  cout << "==============" << endl;
  cout << "==============" << endl;

  //==============================================================
  // Example showing how to compare floats for values that can fit into an
  // integer convert float to integer by multiplying by required precision
  // Multiply by 100 for precision to 2 decimal places
  int num3_integer = num1_float * 100;
  int num4_integer = num2_float * 100;
  cout << "num3_integer: " << num3_integer << endl
       << "num4_integer: " << num4_integer << endl;
  if (num3_integer == num4_integer)
    cout << "COMPARE INTEGERS: Both numbers are equal - PASS" << endl;
  else if (num3_integer > num4_integer)
    cout << "COMPARE INTEGERS: First number is greater than the second - FAIL"
         << endl;
  else if (num3_integer < num4_integer)
    cout << "COMPARE INTEGERS: First number is less than the second - FAIL"
         << endl;
  cout << "==============" << endl;

  return 0;
}
