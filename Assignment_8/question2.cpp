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
    measurement *data;
    Node *next;

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
    cout << setprecision(2) << fixed;

    list.addData(data1);
    cout << "5b add data from data1.txt" << endl;
    list.print();

    list.removeData(30);
    cout << endl
         << "5c Removed at 30 List" << endl;
    list.print();

    list.addData(data2);
    cout << endl
         << "5d add data from data2.txt" << endl;
    list.print();

    list.removeData(60);
    cout << endl
         << "5e Input List" << endl;
    list.print();

    list.sort("CO2");
    cout << endl
         << "5f List of Location with most CO2 (ppm)" << endl;
    list.printHead(5);

    list.sort("NOx");
    cout << endl
         << "5g List of Location with most NOx (ppm)" << endl;
    list.printHead(5);

    list.sort("SOx");
    cout << endl
         << "5h List of Location with most SOx (ppm)" << endl;
    list.printHead(5);

    list.sort("location");
    cout << endl
         << "5g List sorted by location" << endl;
    list.print();
}

/*
5b add data from data1.txt
  Location      Time       CO2       NOx       SOx
    525.30     28.70    427.00      0.75      0.07
    546.40     97.60    418.00      0.85      0.06
     75.30     35.80    450.00      1.00      0.11
     54.10     91.20    430.00      1.10      0.05
    482.10     86.40    386.00      0.55      0.08
    402.00     41.10    384.00      0.30      0.24
    354.20     81.20    451.00      1.80      0.22
    123.40     70.30    370.00      0.80      0.13
    172.60     48.30    360.00      0.60      0.15
     27.20     12.40    420.00      1.20      0.20
    250.70     75.40    405.00      1.40      0.17
    320.90     21.20    432.00      1.60      0.19
     11.30     62.30    410.00      1.30      0.10
    563.70     55.70    409.00      0.95      0.04

5c Removed at 30 List
  Location      Time       CO2       NOx       SOx
    546.40     97.60    418.00      0.85      0.06
     54.10     91.20    430.00      1.10      0.05
    482.10     86.40    386.00      0.55      0.08
    354.20     81.20    451.00      1.80      0.22
    250.70     75.40    405.00      1.40      0.17
    123.40     70.30    370.00      0.80      0.13
     11.30     62.30    410.00      1.30      0.10
    563.70     55.70    409.00      0.95      0.04
    172.60     48.30    360.00      0.60      0.15
    402.00     41.10    384.00      0.30      0.24
     75.30     35.80    450.00      1.00      0.11

5d add data from data2.txt
  Location      Time       CO2       NOx       SOx
    503.20    117.20    432.00      0.65      0.09
    546.40     97.60    418.00      0.85      0.06
    108.20    101.30    390.00      0.90      0.12
    443.60    134.50    423.00      0.45      0.25
     54.10     91.20    430.00      1.10      0.05
    482.10     86.40    386.00      0.55      0.08
    337.60    141.60    392.00      1.70      0.21
    138.80    111.50    440.00      0.70      0.14
    210.10    128.30    460.00      0.40      0.16s
    280.20    122.40    417.00      1.50      0.18
    354.20     81.20    451.00      1.80      0.22
    389.30    107.20    401.00      1.90      0.23
    250.70     75.40    405.00      1.40      0.17
    123.40     70.30    370.00      0.80      0.13
     11.30     62.30    410.00      1.30      0.10
    563.70     55.70    409.00      0.95      0.04
    172.60     48.30    360.00      0.60      0.15
    402.00     41.10    384.00      0.30      0.24
     75.30     35.80    450.00      1.00      0.11

5e Input List
  Location      Time       CO2       NOx       SOx
    337.60    141.60    392.00      1.70      0.21
    443.60    134.50    423.00      0.45      0.25
    210.10    128.30    460.00      0.40      0.16
    280.20    122.40    417.00      1.50      0.18
    503.20    117.20    432.00      0.65      0.09
    138.80    111.50    440.00      0.70      0.14
    389.30    107.20    401.00      1.90      0.23
    108.20    101.30    390.00      0.90      0.12
    546.40     97.60    418.00      0.85      0.06
     54.10     91.20    430.00      1.10      0.05
    482.10     86.40    386.00      0.55      0.08
    354.20     81.20    451.00      1.80      0.22
    250.70     75.40    405.00      1.40      0.17
    123.40     70.30    370.00      0.80      0.13
     11.30     62.30    410.00      1.30      0.10

5f List of Location with most CO2 (ppm)
210.10 km
354.20 km
138.80 km
503.20 km
54.10 km

5g List of Location with most NOx (ppm)
389.30 km
354.20 km
337.60 km
280.20 km
250.70 km

5h List of Location with most SOx (ppm)
443.60 km
389.30 km
354.20 km
337.60 km
280.20 km

5g List sorted by location
  Location      Time       CO2       NOx       SOx
    546.40     97.60    418.00      0.85      0.06``
    503.20    117.20    432.00      0.65      0.09
    482.10     86.40    386.00      0.55      0.08
    443.60    134.50    423.00      0.45      0.25
    389.30    107.20    401.00      1.90      0.23
    354.20     81.20    451.00      1.80      0.22
    337.60    141.60    392.00      1.70      0.21
    280.20    122.40    417.00      1.50      0.18
    250.70     75.40    405.00      1.40      0.17
    210.10    128.30    460.00      0.40      0.16
    138.80    111.50    440.00      0.70      0.14
    123.40     70.30    370.00      0.80      0.13
    108.20    101.30    390.00      0.90      0.12
     54.10     91.20    430.00      1.10      0.05
     11.30     62.30    410.00      1.30      0.10
*/