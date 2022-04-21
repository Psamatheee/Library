//
// Created by julia on 07/04/2022.
//

#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H
#include <iostream>
#include <string>
#include <vector>


using namespace std;

namespace MyLib {
    enum class Genre {
        fiction=0, nonfiction, periodical, biography, children
    };

    class Invalid_ISBN {
    };



    class Book {
    public:


        Book(string tit, string aut, string isbn, Genre gen);

        // Non modifying operations:
        string return_title() const { return title; }

        string return_author() const { return author; }

        string return_ISBN() const { return ISBN; }

        Genre return_genre() const {return genre;}

        bool is_checked_out() { return checked_out; }

        friend ostream &operator<<(ostream &os, Book &book);

        friend bool operator==(const Book &book1, const Book &book2);

        friend bool operator!=(const Book &book1, const Book &book2);

    private:
        string title;
        string author;
        string ISBN;
        Genre genre;
        bool checked_out;
    };

    bool is_valid_ISBN(string &ISBN);
    string genre_str(Genre gen);

    class Patron{
    public:
        Patron(string name, int card_num);
        bool owes_fees();
        friend bool operator==(const Patron& patron1, const Patron& patron2);

        string get_name() const {return name;}
        int get_card() const {return card_num;}
        double get_fees() const {return fees;}

    private:
        string name;
        int card_num;
        double fees;

    };

    class Admin{
    public:
        Admin(string name, string password);
        string get_name(){return name;}
        string get_password(){return password;}
        friend ostream& operator<<(ostream& os, Admin& admin);
    private:
        string name;
        string password;

    };

    class Library{
    public:
        Library();
        struct Transaction{
            Book book;
            Patron patron;
            string date;
        };
        void add_patron(Patron& patron);
        void add_book(Book& book);
        int check_out(Patron& patron, Book& book);
        void late_patrons();
        void print_books();
        int patron_number();
        Patron& does_exist(string name, int num);
        void add_admin(Admin& admin);
        bool is_admin(string& name, string& password);

    private:
        vector<Book> books;
        vector<Patron> patrons;
        vector<Transaction> transactions;
        vector<Admin> admins;
    };



    }






#endif //LIBRARY_BOOK_H
