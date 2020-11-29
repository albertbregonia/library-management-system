#include "Librarian.h"

//Constructor
Librarian::Librarian() : User("admin", "admin") {}

Librarian::Librarian(string username, string password) : User(username, password) {}


void Librarian::delet_user(User* U, Reader* r) {
    string a;
    cout << "Enter the user name you want to delete:";
    cin >> a; // user name
    int flag = 0, find = 0, find1 = 0;
    for (int i = 0; i < Reader::reader_number; i++) // check is user exist
    {
        if (r[i].getUsername() == a) {
            flag = 1; find = i; break;
        }
    }
    if (flag) //user exist
    {
        for (int i = 0; i < Reader::reader_number; i++) {
            Database::getReaders().erase(Database::getReaders().begin() + i);
            cout << "delete successfully！" << endl;
        }
    }
    else    cout << "The user don't exist！" << endl;
}