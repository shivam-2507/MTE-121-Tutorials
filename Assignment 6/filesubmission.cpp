/*
Shivam Walia and Om Upadhyay
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

void latLongToXY(double latitude, double longitude, double &xCoord, double &yCoord)
{
    xCoord = longitude * (111 * cos(latitude * (M_PI / 180)));
    yCoord = latitude * 111;
}

double calculateDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

bool spillsOverlap(double radius1, double lat1, double long1, double radius2, double lat2, double long2)
{
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    latLongToXY(lat1, long1, x1, y1);
    latLongToXY(lat2, long2, x2, y2);
    double distanceBetweenSpills = calculateDistance(x1, y1, x2, y2);
    double radiusSum = radius1 + radius2;
    return (distanceBetweenSpills <= radiusSum);
}

bool isLocationInSpill(double locationLat, double locationLong, double spillLat, double spillLong, double spillRadius)
{
    double locX = 0, locY = 0, spillX = 0, spillY = 0;
    latLongToXY(locationLat, locationLong, locX, locY);
    latLongToXY(spillLat, spillLong, spillX, spillY);
    return calculateDistance(locX, locY, spillX, spillY) <= spillRadius;
}

int main()
{
    ifstream spillFile("spill.txt");
    ifstream locationFile("location.txt");
    ofstream outputFile("soutput.txt");

    string locationName = " ";
    double locationLatitude = 0, locationLongitude = 0;
    const int maxSpills = 10;

    double spillLatitudes[maxSpills];
    double spillLongitudes[maxSpills];
    double spillRadii[maxSpills];
    int numSpills = 0;

    if (!spillFile.fail() && !locationFile.fail() && !outputFile.fail())
    {
        int spillsAffectingLocation = 0;
        int reactionCount = 0;

        spillFile >> numSpills;
        for (int i = 0; i < numSpills; i++)
        {
            spillFile >> spillLatitudes[i] >> spillLongitudes[i] >> spillRadii[i];
        }

        while (locationFile >> locationName)
        {
            spillsAffectingLocation = 0;
            locationFile >> locationLatitude >> locationLongitude;
            for (int i = 0; i < numSpills; i++)
            {
                if (isLocationInSpill(locationLatitude, locationLongitude, spillLatitudes[i], spillLongitudes[i], spillRadii[i]))
                {
                    spillsAffectingLocation++;
                }
            }
            if (spillsAffectingLocation > 0)
            {
                outputFile << setw(25) << locationName << ": " << setw(3) << spillsAffectingLocation << " spills" << endl;
            }
        }

        for (int i = 0; i < numSpills; i++)
        {
            for (int j = i + 1; j < numSpills; j++)
            {
                if (spillsOverlap(spillRadii[i], spillLatitudes[i], spillLongitudes[i], spillRadii[j], spillLatitudes[j], spillLongitudes[j]))
                {
                    reactionCount++;
                }
            }
        }

        outputFile << setw(27) << "Total amount of reaction: " << setw(3) << reactionCount << " reactions" << endl;

        spillFile.close();
        locationFile.close();
        outputFile.close();
    }
    else
    {
        cout << "Error Opening File" << endl;
    }
}

/*
                 WEEF_Lab:   3 spills
       Ryan_Favourite_Pub:   4 spills
               WCI_School:   2 spills
     Grand_River_Hospital:   2 spills
                      RCH:   3 spills
              SJAM_School:   1 spills
            Michael_House:   1 spills
      Perimeter_Institute:   1 spills
       Waterloo_City_Hall:   3 spills
    Pineview_Nursing_Home:   1 spills
              Fiona_House:   2 spills
        St_Marys_Hospital:   3 spills
 Total amount of reaction:   8 reactions
*/