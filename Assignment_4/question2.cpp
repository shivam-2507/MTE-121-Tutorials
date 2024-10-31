/*
Shivam Walia and Himansh Garg
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

double triangle_area(double base, double height)
{
    return 0.5 * base * height;
}

double polygon_area(int numSides, double side_length, double height)
{
    return (numSides * triangle_area(side_length, height));
}

double polygon_perimeter(int numSides, double side_length)
{
    return numSides * side_length;
}

double calculate_cost(int numSides, double side_length, double height)
{
    double paving_cost = polygon_area(numSides, side_length, height) * 12;
    double fencing_cost = polygon_perimeter(numSides, side_length) * 3;
    return paving_cost + fencing_cost;
}

void function_read_and_write()
{
    ifstream input_file;
    input_file.open("jobs.txt");
    ofstream output_file;
    output_file.open("output1.xt");

    int job_number = 0, numSides = 0;
    double side_length = 0, height = 0;

    double sum_of_jobs = 0;
    double average_cost = 0;
    double number_of_jobs = 0;
    double maximum_cost = 0;

    if (!input_file.fail() && !output_file.fail())
    {
        output_file << fixed << setprecision(2) << "Job Number" << setw(15) << "Cost Per Job" << endl;
        while (input_file >> job_number >> numSides >> side_length >> height)
        {
            number_of_jobs++;
            output_file << job_number << setw(10) << "$" << calculate_cost(numSides, side_length, height) << endl;
            sum_of_jobs += calculate_cost(numSides, side_length, height);
            if (calculate_cost(numSides, side_length, height) > maximum_cost)
            {
                maximum_cost = calculate_cost(numSides, side_length, height);
            }
        }

        average_cost = sum_of_jobs / number_of_jobs;
        output_file << "Maximum Cost of the Jobs is $" << maximum_cost << endl
                    << "Total Cost of all the Jobs $" << sum_of_jobs << endl
                    << "Average Cost Per Job is $" << average_cost << endl;
    }
    else
    {
        cout << "Error Opening the File" << endl;
    }
}
int main()
{
    function_read_and_write();
}

/*
Output

Job Number   Cost Per Job
6304         $464.64
6305         $351.12
6306         $544.70
6307         $591.15
6308         $1320.00
6309         $609.66
6310         $793.80
6311         $444.91
6312         $360.00
6313         $946.26
6314         $35.64
6315         $118262.70
6316         $61.96
Maximum Cost of the Jobs is $118262.70
Total Cost of all the Jobs $124786.53
Average Cost Per Job is $9598.96

*/