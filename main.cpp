#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
#include "util.h"
using namespace std;

/*
==TO DO==
- Convert all serial input to a string input
- Add a check for all string inputs


*/


//Mabye change database structure to also include letters in the serial?

int main(){

    sqlite3* db;
    //sqlite3_stmt* stmt;


    sqlite3_open("storage.db", &db);

    initTables(db);


    //Debug Driver
    //removeItemFromBox(db);

    menu(db);


    return 0;
}




