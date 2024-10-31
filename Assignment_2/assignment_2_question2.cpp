/*
Shivam Walia and Om Upadhyay
*/

#include <iostream>
using namespace std;

int main()
{
    cout << "enter the first digit of your guess, the number must be either 0,1,2 or 3: " << endl;
    int guess_digit_tens = 0;
    int guess_digit_ones = 0;
    cin >> guess_digit_tens;
    cout << "enter the second digit of your guess, the number must be either 0,1,2 or 3: " << endl;
    cin >> guess_digit_ones;
    //
    int secert_code_tens = 0;
    int secert_code_ones = 2;
    int correct_place = 0;
    int wrong_place = 0;
    //
    if (guess_digit_ones == secert_code_ones && guess_digit_tens == secert_code_tens)
    {
        cout << "correct guess" << endl;
    }
    else if (guess_digit_ones == secert_code_tens && guess_digit_tens == secert_code_ones)
    {
        wrong_place++;
        wrong_place++;
    }
    else if (guess_digit_ones == secert_code_ones)
    {
        correct_place++;
    }
    else if (guess_digit_ones == secert_code_tens)
    {
        wrong_place++;
    }
    else if (guess_digit_tens == secert_code_ones)
    {
        wrong_place++;
    }
    else if (guess_digit_tens == secert_code_tens)
    {
        correct_place++;
    }
    else
        cout << "none correct try again" << endl;
    if (correct_place > 0 || wrong_place > 0)
    {
        cout << correct_place << " digits correct in the correct place" << endl;
        cout << wrong_place << " digits correct in the wrong place" << endl;
    }
}

/*
OUTPUT
enter the first digit of your guess, the number must be either 0,1,2 or 3:
1
enter the second digit of your guess, the number must be either 0,1,2 or 3:
3
none correct try again


enter the first digit of your guess, the number must be either 0,1,2 or 3:
2
enter the second digit of your guess, the number must be either 0,1,2 or 3:
1
0 digits correct in the correct place
1 digits correct in the wrong place


enter the first digit of your guess, the number must be either 0,1,2 or 3:
1
enter the second digit of your guess, the number must be either 0,1,2 or 3:
2
1 digits correct in the correct place
0 digits correct in the wrong place


enter the first digit of your guess, the number must be either 0,1,2 or 3:
2
enter the second digit of your guess, the number must be either 0,1,2 or 3:
0
0 digits correct in the correct place
2 digits correct in the wrong place


enter the first digit of your guess, the number must be either 0,1,2 or 3:
0
enter the second digit of your guess, the number must be either 0,1,2 or 3:
2
correct guess
*/