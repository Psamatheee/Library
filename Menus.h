//
// Created by julia on 16/04/22.
//

#include <iostream>
#ifndef LIBRARY_MENUS_H
#define LIBRARY_MENUS_H
using namespace std;

class AdminMenu{
public:
    AdminMenu();
    friend ostream& operator<<(ostream& os, AdminMenu& menu);

private:

};


#endif //LIBRARY_MENUS_H
