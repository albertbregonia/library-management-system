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
        for (int j = find; j < Reader::Reader_Number; j++)
        {
            if (j == Reader::/*Reader_Number*/ - 1) {
                Reader::/*Reader_Number--*/;
                break;
            }
            R[j] = R[j + 1];
        }
        for (int j = 0; j < U->/*user number*/; j++)
        {
            if (U[j].getUsername() == a) { find1 = j; break; }
        }
        for (int j = find1; j < U->User_Number; j++)
        {
            if (j == U->User_Number - 1) { U->User_Number--; break; }
            U[j] = U[j + 1];
        }
        cout << "delete successfully！" << endl;
    }
    else    cout << "The user don't exist！" << endl;
}