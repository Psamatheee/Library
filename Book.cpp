//
// Created by julia on 07/04/2022.
//

//#include <string>
#include <regex>
#include <chrono>
#include "Book.h"
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip>
#include <fstream>

using namespace std;
namespace MyLib {

    class NoPatron : exception{};
    Book::Book(string tit, string aut, string isbn, Genre gen)
            : title{tit}, author{aut}, ISBN{isbn}, genre{gen}{
        checked_out = false;
        if (!is_valid_ISBN(isbn)) throw Invalid_ISBN{};
    }

    ostream &operator<<(ostream &os, Book &book) {
        return os << "Title: " << book.title << "\nAuthor: " << book.author << "\nISBN: " << book.ISBN << "\nGenre: " << genre_str(book.genre) << "\n";
    }

    bool is_valid_ISBN(string &ISBN) {
        char rx[] = "\\d+-\\d+-\\d+-[a-z0-9]";
        return (regex_match(ISBN, regex(rx)));
    }

    bool operator==(const Book &book1, const Book &book2) {
        return book1.ISBN == book2.ISBN;
    }

    bool operator!=(const Book &book1, const Book &book2) {
        return !(book1 == book2);
    }

    string genre_str(Genre gen){
        switch(gen){
            case Genre::fiction :
                return "Fiction";
                break;
            case Genre::nonfiction :
                return "Nonfiction";
                break;
            case Genre::biography :
                return "Biography";
                break;
            case Genre::periodical :
                return "Periodical";
                break;
            case Genre::children:
                return "Children";
                break;
        }
        return "";
    }

    Genre str_gen(string& gen){
        if(gen == "fiction"){
            return Genre::fiction;
        }
        if(gen == "nonfiction"){
            return Genre::nonfiction;
        }
        if(gen == "biography"){
            return Genre::biography;
        }
        if(gen == "periodical"){
            return Genre::periodical;
        }
        return Genre::children;
    }

    Patron::Patron(string name, int card_num) : name{name}, card_num{card_num}{
        fees = 0;
    }

    bool operator==(const Patron& pat1, const Patron& pat2){
        return pat1.card_num == pat2.card_num && pat1.name == pat2.name;
    }

    bool Patron::owes_fees() {
        if(fees==0){
            return false;
        }
        return true;
    }

    Library::Library() = default;
    void Library::add_book(Book& book) {
        books.push_back(book);
    }
    void Library::add_patron(Patron& patron) {
        patrons.push_back(patron);
    }
    int Library::check_out(Patron &patron, Book &book) {
        bool patron_in_lib = false;
        bool is_book = false;
        for(const Patron& pat : patrons){
            if (pat==patron) patron_in_lib = true;
        }
        if (!patron_in_lib) return 1;
        for(Book& bk : books){
            if(bk == book){
                is_book = true;
                if(bk.is_checked_out()) return 2;
            }
        }

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%d-%m-%Y %X");
        if(is_book){
            Transaction tr{book,patron,ss.str()};
            transactions.push_back(tr);
            return 0;
        }

        return 3;
    }

    void Library::late_patrons() {
        for(Patron& pat :patrons){
            if(pat.owes_fees()){
                cout << pat.get_name() << " (" << pat.get_card() << ") owes: " << pat.get_fees() << "\n";
            }
        }
    }

    void Library::print_books() {
        for(Book& book : books){
            cout << book;
        }
    }
    Admin::Admin(string name, string password){
        this->name =name;
        this->password=password;
    };

    void Library::add_admin(Admin &admin) {
        admins.push_back(admin);
    }

    bool Library::is_admin(string& name, string& password) {
        for(Admin& ad : admins){
            if(name == ad.get_name() && password == ad.get_password()) return true;
        }
        return false;
    }

    int Library::patron_number() {return patrons.size();}

    Patron& Library::does_exist(string name, int num) {
        for=(Patron& pat : patrons){
            if(pat.get_name() == name && pat.get_card() == num) return pat;
        }

        throw NoPatron{};
    }

    void execute(int option, Patron& pat, Library& lib){
        switch(option){
            case 1 : {

            }
            case 3 : {

            }
        }
    }






}

