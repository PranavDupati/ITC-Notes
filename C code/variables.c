// the syntax to creating variables is: type variableName = value; 
//for outputting the value of a variable, we need to use the format specifier
// for the type of variable we are outputting. In the case of integers, we use %d. Here is an example:

#include <stdio.h>
int main() {
  int myOtherNumber = 15; // this is an old integer variable value
  int newOtherNumber = 20; // this is a new integer variable value
  myOtherNumber = newOtherNumber; // this will assign the value of newOtherNumber to myOtherNumber
  printf("The value of myOtherNumber is: %d\n", myOtherNumber); 
  int x = 5;
  int y = 6;
  int sum = x + y;
  printf("The sum is: %d", sum); 
  return 0;
}
