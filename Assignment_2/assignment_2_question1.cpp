/*
Shivam Walia and Om Upadhyay
*/

#include <iostream>
using namespace std;

int main()
{
    cout << "Enter the amount of money you have: ";
    double amount = 0;
    cin >> amount;

    string coffee = "No Coffee";
    string sweet = "None";
    double remaining_amount = amount;

    if (amount >= 1.75)
    {
        coffee = "Regular";
        remaining_amount -= 1.75;
    }
    else if (amount >= 1.00)
    {
        coffee = "Small";
        remaining_amount -= 1.00;
    }
    if (remaining_amount >= 1.25)
    {
        sweet = "Cake";
    }
    else if (remaining_amount >= 1.00)
    {
        sweet = "Donut";
    }
    else if (remaining_amount >= 0.60)
    {
        sweet = "Mini Tart";
        if (amount < 1.00)
        {
            sweet = "Chocolate";
        }
    }
    else if (remaining_amount >= 0.50)
    {
        sweet = "Chocolate";
    }

    cout << "Coffee Choice is: " << coffee << endl;
    cout << "Sweet Choice is: " << sweet << endl;

    return 0;
}
/*
OUTPUT

Enter the amount of money you have: 0.30
Coffee Choice is: No Coffee
Sweet Choice is: None

Enter the amount of money you have: 0.75
Coffee Choice is: No Coffee
Sweet Choice is: Chocolate

Enter the amount of money you have: 1.25
Coffee Choice is: Small
Sweet Choice is: None

Enter the amount of money you have: 1.55
Coffee Choice is: Small
Sweet Choice is: Chocolate

Enter the amount of money you have: 1.70
Coffee Choice is: Small
Sweet Choice is: Mini Tart

Enter the amount of money you have: 2.00
Coffee Choice is: Regular
Sweet Choice is: None

Enter the amount of money you have: 2.80
Coffee Choice is: Regular
Sweet Choice is: Donut

Enter the amount of money you have: 5.00
Coffee Choice is: Regular
Sweet Choice is: Cake
*/