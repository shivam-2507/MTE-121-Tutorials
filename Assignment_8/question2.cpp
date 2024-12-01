#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class measurement
{
private:
    float CO2;
    float NOx;
    float SOx;
    float location;
    float time;
    int index;

public:
    measurement(float newlocation, float newtime, float newCO2, float newNOx, float newSOx);
    float getCO2();
    float getNOx();
    float getSOx();
    float getLocation();
    float getTime();
    int getIndex();
    void print();
};

measurement::measurement(float newlocation, float newtime, float newCO2, float newNOx, float newSOx)
{
    CO2 = newCO2;
    NOx = newNOx;
    SOx = newSOx;
    location = newlocation;
    time = newtime;
    // index = newindex;
}

float measurement::getLocation()
{
    return location;
}

float measurement::getTime()
{
    return time;
}

float measurement::getCO2()
{
    return CO2;
}

float measurement::getNOx()
{
    return NOx;
}

float measurement::getSOx()
{
    return SOx;
}

int measurement::getIndex()
{
    return index;
}

void measurement::print()
{
    cout << setw(10) << getLocation() << setw(10) << getTime() << setw(10) << getCO2() << setw(10) << getNOx() << setw(10) << getSOx();
}

class Node
{
private:
    measurement *data; // points to measurement object
    Node *next;        // next node object pointer

public:
    Node();
    Node(measurement *data);

    Node *getNext();
    measurement *getData();

    void setNext(Node *node);
};

Node::Node(measurement *m)
{
    data = m;
    next = NULL;
}

Node *Node::getNext()
{
    return next;
}

measurement *Node::getData()
{
    return data;
}

void Node::setNext(Node *node)
{
    next = node;
}

class LinkedList
{
private:
    Node *head;

public:
    LinkedList();
    void insert(float location, float time, float CO2, float NOx, float SOx, int index);
    void remove(int index);
    void print();
    void swap(int index);
    void sort(string value);
    void addData(ifstream &input);
    int cutoffIndex(float time);
    void removeData(float time);
    void printHead(int index);
};

LinkedList::LinkedList()
{
    head = NULL;
}

void LinkedList::insert(float location, float time, float CO2, float NOx, float SOx, int index)
{
    measurement *data = new measurement(location, time, CO2, NOx, SOx);

    if (head == NULL)
    {
        head = new Node(data); // create a node
    }
    else if (index == 0)
    {
        Node *temp = head;     // push whats in head to temp (data of the head)
        head = new Node(data); // creates new node object
        head->setNext(temp);   // take the old data pointer
    }
    else
    {
        Node *currentNode;
        Node *nextNode = head; // start at head
        int counter = 0;
        while (counter < index && nextNode != NULL) // move through to where you want to add
        {
            currentNode = nextNode;
            nextNode = nextNode->getNext();
            counter++;
        }
        Node *temp = new Node(data);
        currentNode->setNext(temp);
        temp->setNext(nextNode);
    }
}

void LinkedList::remove(int index)
{
    if (head == NULL)
    {
        cout << "Nothing to remove" << endl;
    }
    else if (index == 0)
    {
        Node *temp = head->getNext();
        delete head->getData();
        delete head;
        head = temp;
    }
    else
    {
        Node *currentNode;
        Node *nextNode = head;
        int counter = 0;
        while (counter < index && nextNode != NULL)
        {
            currentNode = nextNode;
            nextNode = nextNode->getNext();
            counter++;
        }
        if (nextNode == NULL)
        {
            cout << "Nothing to remove" << endl;
        }
        else
        {
            currentNode->setNext(nextNode->getNext());
            delete nextNode->getData();
            delete nextNode;
        }
    }
}
void LinkedList::print()
{
    Node *currentNode = head;
    cout << setw(10) << "Location" << setw(10) << "Time" << setw(10) << "CO2" << setw(10) << "NOx" << setw(10) << "SOx" << endl;
    while (currentNode != NULL)
    {
        currentNode->getData()->print();
        cout << endl;
        currentNode = currentNode->getNext();
    }
}

void LinkedList::swap(int index)
{

    if (head == NULL || head->getNext() == NULL)
    {
        cout << "Nothing to swap!" << endl;
        return;
    }

    if (index == 0)
    {
        Node *first = head;
        Node *second = first->getNext();

        first->setNext(second->getNext());
        second->setNext(first);
        head = second;
    }
    else
    {
        Node *currentNode;
        Node *nextNode = head;
        int counter = 0;

        while (counter < index && nextNode != NULL)
        {
            currentNode = nextNode;
            nextNode = nextNode->getNext();
            counter++;
        }

        if (nextNode == NULL)
        {
            cout << "Nothing to swap!" << endl;
            return;
        }

        Node *beforeFirst = currentNode;
        Node *first = nextNode;
        Node *second = first->getNext();

        first->setNext(second->getNext());
        second->setNext(first);
        beforeFirst->setNext(second);
        // review this one
    }
}

void LinkedList::sort(string value)
{

    if (head == NULL || head->getNext() == NULL)
    {
        return;
    }

    bool sorted = false;

    while (!sorted)
    {

        Node *currentNode = head;
        Node *nextNode = head->getNext();
        bool swapping = false;
        int index = 0;

        while (!swapping && nextNode != NULL)
        {
            float valCur, valNext;

            if (value == "location")
            {
                valCur = currentNode->getData()->getLocation();
                valNext = nextNode->getData()->getLocation();
            }
            else if (value == "time")
            {
                valCur = currentNode->getData()->getTime();
                valNext = nextNode->getData()->getTime();
            }
            else if (value == "CO2")
            {
                valCur = currentNode->getData()->getCO2();
                valNext = nextNode->getData()->getCO2();
            }
            else if (value == "NOx")
            {
                valCur = currentNode->getData()->getNOx();
                valNext = nextNode->getData()->getNOx();
            }
            else if (value == "SOx")
            {
                valCur = currentNode->getData()->getSOx();
                valNext = nextNode->getData()->getSOx();
            }

            if (valCur < valNext)
            {
                swapping = true;
                swap(index);
            }
            else
            {
                currentNode = nextNode;
                nextNode = nextNode->getNext();
                index++;
            }
        }

        if (nextNode == NULL)
        {
            sorted = true;
        }
    }
}

void LinkedList::addData(ifstream &input)
{
    float location = 0, time = 0, CO2 = 0, NOx = 0, SOx = 0;
    int index = 0;
    while (input >> location >> time >> CO2 >> NOx >> SOx >> index)
    {
        insert(location, time, CO2, NOx, SOx, index);
    }
}

int LinkedList::cutoffIndex(float time)
{
    Node *current = head;
    int index = 0;
    while (current != NULL)
    {
        if ((current->getData()->getTime()) < time)
        {
            return index;
        }
        current = current->getNext();
        index++;
    }

    return -1;
}

void LinkedList::removeData(float time)
{
    sort("time");
    int index = cutoffIndex(time);

    while (index >= 0)
    {
        remove(index);
        index = cutoffIndex(time);
    }
}

void LinkedList::printHead(int index)
{
    Node *current = head;
    int counter = 0;

    while (current != NULL && counter < index)
    {
        cout << current->getData()->getLocation() << " km" << endl;
        current = current->getNext();
        counter++;
    }
    if (counter == 0)
    {
        cout << "No nodes to print." << endl;
    }
}

int main()
{

    LinkedList list;
    ifstream data1("data1.txt");
    ifstream data2("data2.txt");

    list.addData(data1);
    cout << "5b add data from data1.txt" << endl;
    list.print();

    list.removeData(30);
    cout << endl
         << "5c Removed measurements earlier than 30 minutes" << endl;
    list.print();

    list.addData(data2);
    cout << endl
         << "5d add data from data2.txt" << endl;
    list.print();

    list.removeData(60);
    cout << endl
         << "5e Removed measurements earlier than 60 minutes" << endl;
    list.print();

    list.sort("CO2");
    cout << endl
         << "5f List of locations with most CO2 (ppm)" << endl;
    list.printHead(5);

    list.sort("NOx");
    cout << endl
         << "5g List of locations with most NOx (ppm)" << endl;
    list.printHead(5);

    list.sort("SOx");
    cout << endl
         << "5h List of locations with most SOx (ppm)" << endl;
    list.printHead(5);

    list.sort("location");
    cout << endl
         << "5g List sorted by location" << endl;
    list.print();
}

/*
5b add data from data1.txt
  Location      Time       CO2       NOx       SOx
     525.3      28.7       427      0.75      0.07
     546.4      97.6       418      0.85      0.06
      75.3      35.8       450         1      0.11
      54.1      91.2       430       1.1      0.05
     482.1      86.4       386      0.55      0.08
       402      41.1       384       0.3      0.24
     354.2      81.2       451       1.8      0.22
     123.4      70.3       370       0.8      0.13
     172.6      48.3       360       0.6      0.15
      27.2      12.4       420       1.2       0.2
     250.7      75.4       405       1.4      0.17
     320.9      21.2       432       1.6      0.19
      11.3      62.3       410       1.3       0.1
     563.7      55.7       409      0.95      0.04

5c Removed measurements earlier than 30 minutes
  Location      Time       CO2       NOx       SOx
     546.4      97.6       418      0.85      0.06
      54.1      91.2       430       1.1      0.05
     482.1      86.4       386      0.55      0.08
     354.2      81.2       451       1.8      0.22
     250.7      75.4       405       1.4      0.17
     123.4      70.3       370       0.8      0.13
      11.3      62.3       410       1.3       0.1
     563.7      55.7       409      0.95      0.04
     172.6      48.3       360       0.6      0.15
       402      41.1       384       0.3      0.24
      75.3      35.8       450         1      0.11

5d add data from data2.txt
  Location      Time       CO2       NOx       SOx
     503.2     117.2       432      0.65      0.09
     546.4      97.6       418      0.85      0.06
     108.2     101.3       390       0.9      0.12
     443.6     134.5       423      0.45      0.25
      54.1      91.2       430       1.1      0.05
     482.1      86.4       386      0.55      0.08
     337.6     141.6       392       1.7      0.21
     138.8     111.5       440       0.7      0.14
     210.1     128.3       460       0.4      0.16
     280.2     122.4       417       1.5      0.18
     354.2      81.2       451       1.8      0.22
     389.3     107.2       401       1.9      0.23
     250.7      75.4       405       1.4      0.17
     123.4      70.3       370       0.8      0.13
      11.3      62.3       410       1.3       0.1
     563.7      55.7       409      0.95      0.04
     172.6      48.3       360       0.6      0.15
       402      41.1       384       0.3      0.24
      75.3      35.8       450         1      0.11

5e Removed measurements earlier than 60 minutes
  Location      Time       CO2       NOx       SOx
     337.6     141.6       392       1.7      0.21
     443.6     134.5       423      0.45      0.25
     210.1     128.3       460       0.4      0.16
     280.2     122.4       417       1.5      0.18
     503.2     117.2       432      0.65      0.09
     138.8     111.5       440       0.7      0.14
     389.3     107.2       401       1.9      0.23
     108.2     101.3       390       0.9      0.12
     546.4      97.6       418      0.85      0.06
      54.1      91.2       430       1.1      0.05
     482.1      86.4       386      0.55      0.08
     354.2      81.2       451       1.8      0.22
     250.7      75.4       405       1.4      0.17
     123.4      70.3       370       0.8      0.13
      11.3      62.3       410       1.3       0.1

5f List of locations with most CO2 (ppm)
210.1 km
354.2 km
138.8 km
503.2 km
54.1 km

5g List of locations with most NOx (ppm)
389.3 km
354.2 km
337.6 km
280.2 km
250.7 km

5h List of locations with most SOx (ppm)
443.6 km
389.3 km
354.2 km
337.6 km
280.2 km

5g List sorted by location
  Location      Time       CO2       NOx       SOx
     546.4      97.6       418      0.85      0.06
     503.2     117.2       432      0.65      0.09
     482.1      86.4       386      0.55      0.08
     443.6     134.5       423      0.45      0.25
     389.3     107.2       401       1.9      0.23
     354.2      81.2       451       1.8      0.22
     337.6     141.6       392       1.7      0.21
     280.2     122.4       417       1.5      0.18
     250.7      75.4       405       1.4      0.17
     210.1     128.3       460       0.4      0.16
     138.8     111.5       440       0.7      0.14
     123.4      70.3       370       0.8      0.13
     108.2     101.3       390       0.9      0.12
      54.1      91.2       430       1.1      0.05
      11.3      62.3       410       1.3       0.1
*/