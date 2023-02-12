
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;
char filename[] = "contacts.txt";

struct person
{
    string name;
    string gender;
    string phone;
    string email;
};
person* contacts = new person[1000];
int contactsCount;

void menu();
void addContact();
void showContacts();
bool saveContactToFile(person p);
void getContactsFromFile();
bool retContact(string name, person& pp);
void editContact();
bool deleteContactFromFile(string nm);
void deleteContact();
void searchContacts();

string lowercase(string ss)
{
    for (int i = 0; i < ss.length(); i++)
        ss[i] = tolower(ss[i]);

    return ss;
}

int main()
{
    menu();

    return 0;
}
void menu()
{
    system("cls");
    cout << ("\t\t**PhoneBook*");

    cout << ("\n\n\t\t\tMENU\t\t\n\n");
    cout << ("\t1.Add New Contact   \t2.Show Saved Contacts   \t3.Edit Contact  \n\t4.Search Contacts \t5.Delete Contacts\t6.Exit\n\n\n");
    cout << "Enter Your Choice: ";
    char choice;
    cin >> choice;
    switch (choice)
    {
    case '1':
        addContact();
        break;
    case '2':
        showContacts();
        break;
    case '3':
        editContact();
        break;
    case '4':
        searchContacts();
        break;
    case '5':
        deleteContact();
        break;
    case '6':
        exit(0);
        break;
    default:
        system("cls");
        cout << "\nEnter a choice from 1 to 6 only";
        cout << "\n Press enter to continue...";
        cin.ignore();
        getchar();

        menu();
    }
}
void addContact()
{
    system("cls");
    person p, n;
    cout << "Enter Contact's Name: " << endl;
    cin.ignore();
    getline(cin, p.name);
    bool found = retContact(p.name, n);
    if (found) {
        cout << "\nThis Name already exists.\n";
    }
    else {
        cout << "Enter Contact's Phone Number: ";
        cin >> p.phone;
        cout << "\n1. Male\t\t2. Female\n";
        cout << "Choose Contact's Gender: ";

        string gender;
        cin >> gender;
        gender = lowercase(gender);

        if (gender == "1" || gender == "male")
            p.gender = "Male";
        else
            p.gender = "Female";

        cout << "Enter Contact's email:";
        cin >> p.email;

        bool saved = saveContactToFile(p);
        if (saved)
            cout << "\nContact Added Successfully!";
        else
            cout << "\nCouldn't open file! Please try again.";
    }
    cout << "\n\nPress Enter to continue:\n";
    cin.ignore();
    getchar();
    system("cls");
    menu();
}
bool saveContactToFile(person p)
{
    ofstream save_contacts(filename, fstream::app);

    if (!save_contacts.is_open())
        return false;

    save_contacts << p.name << endl
        << p.gender << endl
        << p.phone << endl
        << p.email << endl;
    save_contacts.close();

    return true;
}
void getContactsFromFile()
{
    contactsCount = 0;
    ifstream read_contacts(filename);
    if (read_contacts.is_open())
    {
        while (!read_contacts.eof())
        {
            getline(read_contacts, contacts[contactsCount].name);
            getline(read_contacts, contacts[contactsCount].gender);
            getline(read_contacts, contacts[contactsCount].phone);
            getline(read_contacts, contacts[contactsCount].email);


            if (contacts[contactsCount].name != "")
                contactsCount++;
        }
    }
    read_contacts.close();
}

bool retContact(string name, person& pp)
{
    name = lowercase(name);
    bool found = 0;
    ifstream read_contacts(filename);
    if (read_contacts.is_open())
    {
        while (!read_contacts.eof())
        {
            pp.name = "";
            getline(read_contacts, pp.name);
            getline(read_contacts, pp.gender);
            getline(read_contacts, pp.phone);
            getline(read_contacts, pp.email);
            if (lowercase(pp.name) == name)
            {
                found = 1;
                break;
            }
        }
    }
    read_contacts.close();

    return found;
}

void showContacts()
{
    system("cls");
    getContactsFromFile();
    if (contactsCount > 0)
    {
        for (int i = 0; i < contactsCount; i++)
        {
            system("cls");
            cout << "Contact #" << i + 1 << ":\n";
            cout << "Contact Name: " << contacts[i].name << "\n";
            cout << "Contact Phone: " << contacts[i].phone << "\n";
            cout << "Contact Email: " << contacts[i].email << "\n";
            cout << "Contact Gender: " << contacts[i].gender << "\n";
            cout << "\n1.Press Enter to show next contact\t\t\t2. to exit press q or Q\n";
            cin.ignore();
            char cc = getchar();


            if (cc == 'q' || cc == 'Q')
                break;
        }
    }
    else
    {
        cout << "\n No Contacts Found! Press Enter to continue. \n"
            << endl;
        cin.ignore();
        getchar();
    }

    system("cls");
    menu();
}
void searchContacts()
{
    system("cls");

    cout << "Enter Contact's name to search:" << endl;
    string name;
    cin.ignore();
    getline(cin, name);

    person n;
    bool found = retContact(name, n);
    if (found)
    {
        cout << "Contact Name: " << n.name << "\n";
        cout << "Contact Phone: " << n.phone << "\n";
        cout << "Contact Email: " << n.email << "\n";
        cout << "Contact Gender: " << n.gender << "\n";
    }
    else
    {
        cout << "Contact Not Found!";
    }
    cout << "\n\nPress Enter to continue:\n";

    cin.ignore();
    getchar();
    system("cls");
    menu();
}
bool deleteContactFromFile(string name)
{
    name = lowercase(name);
    person p;
    ifstream read_contacts(filename);
    ofstream tempfile("temp.txt", fstream::app);
    bool flag = 0;
    if (read_contacts.is_open() && tempfile.is_open())
    {
        while (!read_contacts.eof())
        {
            p.name = "";
            getline(read_contacts, p.name);
            getline(read_contacts, p.gender);
            getline(read_contacts, p.phone);
            getline(read_contacts, p.email);
            if (p.name != "")
            {
                if (lowercase(p.name) != name)
                    tempfile << p.name << endl
                    << p.gender << endl
                    << p.phone << endl
                    << p.email << endl;
                else
                    flag = 1;
            }
        }
        read_contacts.close();
        tempfile.close();
        if (flag != 1)
            remove("temp.txt");
        else
        {
            remove(filename);
            rename("temp.txt", filename);
        }
    }
    return flag;
}

void deleteContact()
{
    system("cls");

    bool flag = 0;
    string name;
    cout << "Enter Contact's Name:" << endl;
    cin.ignore();
    getline(cin, name);

    bool deleted = deleteContactFromFile(name);
    if (deleted)
        cout << "Contact Deleted Successfully!" << endl;
    else
        cout << "Contact Not Found!" << endl;

    cout << "\n Press Enter to continue..." << endl;

    cin.ignore();
    getchar();
    system("cls");
    menu();
}

void editContact()
{
    system("cls");
    string name;
    cout << "Enter Name:";
    cin >> name;
    person n, m;
    bool found = retContact(name, n);
    if (found)
    {
        cout << endl
            << "Name: " << n.name << endl;
        cout << "Phone: " << n.phone << endl;
        cout << "Email: " << n.email << endl;
        cout << "Gender: " << n.gender << endl
            << endl;
        deleteContactFromFile(name);

        cout << "Enter New Contact's Name: " << endl;
        cin.ignore();
        getline(cin, m.name);
        cout << "Enter New Contact's Phone: ";
        cin >> m.phone;

        cout << "\n1.Male \t\t 2.Female" << endl;
        cout << "Choose New Contact's Gender: ";

        string gender;
        cin >> gender;
        gender = lowercase(gender);
        if (gender == "1" || gender == "male")
            m.gender = "Male";
        else
            m.gender = "Female";

        cout << "Enter New Contact's Email: ";
        cin >> m.email;
        bool saved = saveContactToFile(m);
        if (saved)
            cout << "\nContact Edited Successfully!" << endl;
        else
            cout << "\nCouldn't open file! Please try again.";
    }
    else
    {
        cout << "\nContact Not Found!";
    }

    cout << "\nPress Enter to continue..." << endl;
    cin.ignore();
    getchar();
    system("cls");
    menu();
}