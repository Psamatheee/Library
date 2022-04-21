//#include <iostream>
#include "Book.cpp"
using namespace std;
//using namespace MyLib;

int main() {
    MyLib::Library lib = MyLib::Library();
    MyLib::Library& libref = lib;
    string iname{"LibBooks.txt"};
    ifstream ift(iname);
    string line;
    if (!ift) cout << "no";
    while (getline(ift, line)) {
        istringstream ss(line);
        string title;
        string aut;
        string isbn;
        string genre;
        getline(ss, title, ',');
        getline(ss, aut, ',');
        getline(ss, isbn, ',');
        getline(ss, genre, ',');

        MyLib::Book book{title, aut, isbn, MyLib::str_gen(genre)};
        lib.add_book(book);
    }

    string patrons_file = "patrons.txt";
    string admins_file = "admins.txt";
    ifstream ipatrons{patrons_file};
    string patron_line;
    while (getline(ipatrons, patron_line)) {
        istringstream ss(patron_line);
        string name;
        getline(ss, name, ',');
        int card_num;
        ss >> card_num;
        MyLib::Patron pat{name, card_num};
        lib.add_patron(pat);
    }
    ofstream opatrons{patrons_file, fstream::app};

    ifstream iadmins{admins_file};
    string admin_line;
    while (getline(iadmins, admin_line)) {
        istringstream ss(admin_line);
        string name;
        getline(ss, name, ',');
        string pass;
        ss >> pass;
        MyLib::Admin admin{name, pass};
        lib.add_admin(admin);
    }

    cout << "Welcome to the Library!\n";
    cout << "Options: \n" << "Enter 1: Sign Up\nEnter 2: Log In\nEnter 3: Log In as admin\nEnter 4: Exit\n";
    int input = 0;
    while (input != 4) {
        if (cin >> input && input >= 1 && input <= 4) {
            switch (input) {
                case 1: {
                    string name;
                    cout << "Enter your name: ";
                    cin >> name;
                    MyLib::Patron patron{name, lib.patron_number() + 1};
                    lib.add_patron(patron);
                    opatrons << name << ',' << patron.get_card() << "\n";

                    cout << "Welcome " << name << "! Your card number is: " << patron.get_card() << "\n";
                    cout << "Use this number to log in!\n";
                    break;
                }
                case 2: {
                    cout << "Enter your name: ";
                    string name;
                    cin >> name;
                    int card_num;
                    cout << "Enter your card number: ";
                    cin >> card_num;
                    try{
                        MyLib::Patron& pat = lib.does_exist(name, card_num);
                        cout << "Welcome " << name << "\n";
                        cout << "Options:\n1: View your loans\n2: Renew\n3: Return\n4: Borrow\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        int option;
                        cin >> option;
                        MyLib::execute(option, pat, libref);
                    }catch (MyLib::NoPatron&){
                        cout << "Sorry! Either this account doesn't exist or you entered the wrong details!\n";
                    }
                    break;

                }
                case 3 : {

                    cout << "Enter your name: ";
                    string name;
                    cin >> name;
                    string password;
                    cout << "Enter your password: ";
                    cin >> password;
                    cout << password << "\n";
                    if (lib.is_admin(name, password)) {
                        cout << "Welcome " << name << "\n";





                    } else {
                        cout << "Sorry! Either this account doesn't exist or you entered the wrong details!\n";
                    }
                    break;
                }

            }
        } else {
            cout << "Sorry! I don't recognise the command!\n";
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Options: \n" << "Enter 1: Sign Up\nEnter 2: Log In\nEnter 3: Log In as admin\nEnter 4: Exit\n";

    }
    return 0;
}
