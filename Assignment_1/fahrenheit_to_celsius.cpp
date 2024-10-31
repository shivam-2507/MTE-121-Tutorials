/*
Shivam Walia
*/
#include <iostream>
using namespace std;

int main()
{
    cout << "Enter a temperature in Fahrenheit:" << endl;
    float temp_f;
    cin >> temp_f;
    float temp_c = ((temp_f - 32) * 5) / 9;
    cout << temp_c;
    return 0;
}

/*
Enter a temperature
212
100

Enter a temperature in Fahrenheit:
100
37.7778

Enter a temperature in Fahrenheit:
32
0

Enter a temperature in Fahrenheit:
-40
-40
*/