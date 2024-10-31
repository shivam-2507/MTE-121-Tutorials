/*
Shivam Walia
*/
#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a withdrawal amount" << endl;
    double amount;
    cin >> amount;
    int cents = amount * 100;
    int quarters = cents / 25;
    int amount_left = cents % 25;
    int dimes = amount_left / 10;
    amount_left = amount_left % 10;
    int nickel = amount_left / 5;
    amount_left = amount_left % 5;

    cout << quarters << " quarters" << endl
         << dimes << " dimes" << endl
         << nickel << " nickels" << endl
         << amount_left << " pennies";
}
/*
Enter a withdrawal amount
1.17
4 quarters
1 dimes
1 nickels
2 pennies

Enter a withdrawal amount
5.24
20 quarters
2 dimes
0 nickels
4 pennies

*/