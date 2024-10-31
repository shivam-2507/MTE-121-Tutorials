/*
 Shivam Walia

*/

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
  cout << "Enter a number to find the square of" << endl;
  int side_length;
  cin >> side_length;
  cout << "The square of " << side_length << " is " << side_length * side_length << endl;
  cout << "& the cube of " << side_length << " is " << side_length * side_length * side_length << endl;

  return EXIT_SUCCESS;
  /*note that in order to use return EXIT_SUCCESS; you need to include the header file #include <cstdlib>
    If you decide to instead use return 0; then you do not need to include the header file #include <cstdlib>
  */
}

/*
Enter a number to find the square of
8
The square of 8 is 64
& the cube of 8 is 512
*/
