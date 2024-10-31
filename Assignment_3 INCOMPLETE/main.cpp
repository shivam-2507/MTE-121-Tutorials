#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    ifstream inputfile;
    inputfile.open(("taxi.txt"));
    ofstream outputfile;
    outputfile.open(("report.txt"));

    bool vip = 0;
    int stops = 0;
    int tripNum = 0;
    float trip_cost = 0, trip_distance = 0;

    if (!inputfile.fail() && !outputfile.fail())
    {
        outputfile << setw(10) << "Trip #" << setw(10) << "VIP" << setw(10) << "Stops" << setw(10) << "tripDist" << setw(10) << "tripCost" << setw(10) << "totalDist" << setw(10) << "totalCost" << endl;
        while (inputfile >> vip >> stops)
        {
            tripNum++;
            float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
            float x_distance = 0, y_distance = 0;
            float leg_distance = 0, leg_cost = 0, return_leg = 0, return_cost = 0;
            trip_cost = 15 * stops;
            trip_distance = 0;
            for (int i = 0; i < stops; i++)
            {
                inputfile >> x1 >> y1;
                x_distance = x1 - x2;
                y_distance = y1 - y2;

                leg_distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
                leg_cost = leg_distance * 2.6;

                trip_distance += leg_distance;
                trip_cost += leg_cost;

                if (i == (stops - 1))
                {
                    return_leg = sqrt(pow(x1, 2) + pow(y1, 2));
                    trip_distance += return_leg;
                    return_cost = return_leg * 2.6;

                    trip_cost += return_cost;
                    // cout << trip_cost << endl;
                }

                x2 = x1;
                y2 = y1;
            }
            outputfile << setw(10) << tripNum << setw(10) << vip << setw(10) << stops << setw(10) << trip_distance << setw(10) << trip_cost << endl;
        }
    }
    else
    {
        cout << "error opening file";
    }
}