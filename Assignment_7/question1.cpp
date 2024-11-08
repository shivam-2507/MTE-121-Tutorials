/*
Shivam Walia and Om Upadhyay
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// part b
void read_current_parking(ifstream &current, string names[], int status[], int parkingSpaces)
{
    int spot = 0;
    string name = "";
    int status_1 = -1;
    int index = 0;
    while (current >> status_1 >> name >> spot)
    {
        index = spot - 101;
        status[index] = status_1;
        names[index] = name;
    }
}

// part c
void populate_Add_RemoveArray(ifstream &file, string add_names[], bool add_status[], int count)
{
    int status = 0;
    string name = "";
    count = 0;
    while (file >> status >> name)
    {
        add_names[count] = name;
        add_status[count] = status;
        count++;
    }
}

// part d
void remove_person(string person, string names[], int status[], int count)
{
    bool exit = 1;
    for (int i = 0; i < count; i++)
    {
        if (person == names[i] && exit)
        {
            names[i] = "";
            status[i] = -1;
            exit = 0;
        }
    }
}

// part e
int avalible_parkingSpace(int status[], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (status[i] == -1)
        {
            return i;
        }
    }
    return -1;
}

// part f
bool assign_space(string name, int status_stored, int count, int status[], string names[])
{
    int available_index = avalible_parkingSpace(status, count);
    if (available_index == -1)
    {
        cout << "Parking lot is full." << endl;
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        if (status[i] == -1)
        {
            if (i < 25 && status_stored == 1)
            {
                names[i] = name;
                status[i] = status_stored;
                return true;
            }
            else if (i >= 25 && status_stored == 0)
            {
                names[i] = name;
                status[i] = status_stored;
                return true;
            }
        }
    }
    return false;
}

// part g
void movingFaculty(string names[], int statuses[], int parkingSpaces, string addNames[], bool addStatuses[], int peopleCount)
{
    string movedFaculty[peopleCount];
    int movedCount = 0;

    for (int i = 25; i < parkingSpaces; i++)
    {
        if (statuses[i] == 1)
        {
            string person = names[i];
            remove_person(person, names, statuses, parkingSpaces);
            movedFaculty[movedCount] = person;
            movedCount++;
        }
    }

    for (int i = 0; i < movedCount; i++)
    {
        bool assigned = assign_space(movedFaculty[i], 1, 25, statuses, names);

        if (!assigned)
        {
            cout << "No available spot in the first half for faculty member: " << movedFaculty[i] << endl;
        }
    }
}

// part h
void write_to_file(ofstream &output, int space_number, string names[], int status[])
{
    for (int i = 0; i < space_number; i++)
    {
        output << setw(20) << names[i] << setw(10) << status[i] << setw(20) << (i + 101) << endl;
    }
    output << endl;
}

int main()
{
    const int parking_spaces = 50;
    string names[parking_spaces];
    int status[parking_spaces];

    const int people_changing = 30;
    string add_names[people_changing];
    string remove_names[people_changing];
    bool add_status[people_changing];
    bool remove_status[people_changing];

    ifstream current("parking_current.txt");
    ifstream add_file("parking_add.txt");
    ifstream remove_file("parking_remove.txt");
    ofstream output("report.txt");

    // defaulting the array
    for (int i = 0; i < parking_spaces; i++)
    {
        status[i] = -1;
        names[i] = "";
    }

    if (!current.fail() && !add_file.fail() && !remove_file.fail())
    {
        output << "Status 1 Indicates Faculty" << endl
               << "Status 0 Indicates Student" << endl
               << "Status -1 Indicates Empty Lot " << endl;
        read_current_parking(current, names, status, parking_spaces);
        output << "Initial Parking Lot" << endl
               << setw(20) << "NAME" << setw(10) << "STATUS" << setw(20) << "LOT NUMBER" << endl;
        write_to_file(output, parking_spaces, names, status);
        populate_Add_RemoveArray(add_file, add_names, add_status, people_changing);
        populate_Add_RemoveArray(remove_file, remove_names, remove_status, people_changing);

        for (int i = 0; i < people_changing; i++)
        {
            remove_person(remove_names[i], names, status, parking_spaces);
        }

        movingFaculty(names, status, parking_spaces, add_names, add_status, people_changing);

        output << "Parking Lot After Removing and Reassiging" << endl
               << setw(20) << "NAME" << setw(10) << "STATUS" << setw(20) << "LOT NUMBER" << endl;

        write_to_file(output, parking_spaces, names, status);

        output << "Final Parking Lot" << endl;

        for (int i = 0; i < people_changing; i++)
        {
            bool assigned = assign_space(add_names[i], add_status[i], parking_spaces, status, names);
            if (!assigned && add_names[i] != "")
            {
                output << "No parking spot available for " << add_names[i] << endl;
            }
        }
        output << setw(20) << "NAME" << setw(10) << "STATUS" << setw(20) << "LOT NUMBER" << endl;

        write_to_file(output, parking_spaces, names, status);

        current.close();
        add_file.close();
        remove_file.close();
        output.close();
    }
    else
    {
        cout << "Error Opening One or More Files" << endl;
    }
    return 0;
}

/*
Status 1 Indicates Faculty
Status 0 Indicates Student
Status -1 Indicates Empty Lot
Initial Parking Lot
                NAME    STATUS          LOT NUMBER
Hamdullahpur_Feridun         1                 101
  de_Souza_Madeleine         1                 102
                            -1                 103
        Collins_Mike         1                 104
                            -1                 105
                            -1                 106
                            -1                 107
       Gryguc_Andrew         1                 108
      Campbell_Emily         1                 109
        Lovelace_Ada         0                 110
                            -1                 111
        Archimedes_A         0                 112
        da_Vinci_Leo         0                 113
   MacGregor_Carolyn         1                 114
                            -1                 115
        Yerxa_Meagan         0                 116
        Gorman_David         1                 117
           Owen_Bill         1                 118
                            -1                 119
         Nairn_David         1                 120
                            -1                 121
        Hurwitz_Marc         1                 122
        Consell_Ryan         1                 123
           McKay_Ken         1                 124
  Vandekerckhove_Sam         1                 125
          Tesla_Nick         0                 126
                            -1                 127
           Otto_Nick         0                 128
           Turing_Al         0                 129
     Teertstra_Peter         1                 130
             Aho_Alf         0                 131
           Bell_Alex         0                 132
      Stephenson_Geo         0                 133
          Pike_Robby         0                 134
        Hopper_Grace         0                 135
            Oh_Henry         0                 136
        Milne_Andrew         1                 137
                            -1                 138
         Cramer_Zack         1                 139
                            -1                 140
          Edison_Tom         0                 141
         Hulls_Carol         1                 142
                            -1                 143
      Payton_Forrest         1                 144
        Babbage_Chip         0                 145
         Casale_Matt         1                 146
          Goel_Vivek         1                 147
         Harris_Dave         1                 148
                            -1                 149
          Wells_Mary         1                 150

Parking Lot After Removing and Reassiging
                NAME    STATUS          LOT NUMBER
     Teertstra_Peter         1                 101
        Milne_Andrew         1                 102
         Cramer_Zack         1                 103
        Collins_Mike         1                 104
         Hulls_Carol         1                 105
      Payton_Forrest         1                 106
          Goel_Vivek         1                 107
       Gryguc_Andrew         1                 108
         Harris_Dave         1                 109
        Lovelace_Ada         0                 110
          Wells_Mary         1                 111
        Archimedes_A         0                 112
        da_Vinci_Leo         0                 113
                            -1                 114
                            -1                 115
                            -1                 116
        Gorman_David         1                 117
           Owen_Bill         1                 118
                            -1                 119
                            -1                 120
                            -1                 121
                            -1                 122
        Consell_Ryan         1                 123
                            -1                 124
  Vandekerckhove_Sam         1                 125
          Tesla_Nick         0                 126
                            -1                 127
                            -1                 128
           Turing_Al         0                 129
                            -1                 130
             Aho_Alf         0                 131
           Bell_Alex         0                 132
                            -1                 133
          Pike_Robby         0                 134
        Hopper_Grace         0                 135
                            -1                 136
                            -1                 137
                            -1                 138
                            -1                 139
                            -1                 140
                            -1                 141
                            -1                 142
                            -1                 143
                            -1                 144
        Babbage_Chip         0                 145
                            -1                 146
                            -1                 147
                            -1                 148
                            -1                 149
                            -1                 150

Final Parking Lot
No parking spot available for Imhotep_P
No parking spot available for Tepe_Go
No parking spot available for Armstrong_Nick
                NAME    STATUS          LOT NUMBER
     Teertstra_Peter         1                 101
        Milne_Andrew         1                 102
         Cramer_Zack         1                 103
        Collins_Mike         1                 104
         Hulls_Carol         1                 105
      Payton_Forrest         1                 106
          Goel_Vivek         1                 107
       Gryguc_Andrew         1                 108
         Harris_Dave         1                 109
        Lovelace_Ada         0                 110
          Wells_Mary         1                 111
        Archimedes_A         0                 112
        da_Vinci_Leo         0                 113
     Katherine_Idzik         1                 114
        Yerxa_Meagan         1                 115
           Zhou_Yang         1                 116
        Gorman_David         1                 117
           Owen_Bill         1                 118
        Khan_Aleysha         1                 119
       Meunier_Sarah         1                 120
      Benoit_Michael         1                 121
                            -1                 122
        Consell_Ryan         1                 123
                            -1                 124
  Vandekerckhove_Sam         1                 125
          Tesla_Nick         0                 126
        Payette_Jill         0                 127
         Fleming_San         0                 128
           Turing_Al         0                 129
          Eiffel_Gus         0                 130
             Aho_Alf         0                 131
           Bell_Alex         0                 132
        Wozniak_Stef         0                 133
          Pike_Robby         0                 134
        Hopper_Grace         0                 135
          Clarke_Edi         0                 136
            Lamarr_H         0                 137
         Roebling_Em         0                 138
         Jemison_May         0                 139
        Jackson_Mary         0                 140
         Johnson_Kat         0                 141
         Vaughan_Dot         0                 142
            Tlaa_Sha         0                 143
          Curie_Mary         0                 144
        Babbage_Chip         0                 145
       Stroustrup_Bj         0                 146
          Imahara_Gr         0                 147
         Frize_Molly         0                 148
          Guppy_Sara         0                 149
       Roebling_Emma         0                 150
*/