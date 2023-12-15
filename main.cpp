#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
#include "utilFunctions.h"
using namespace std;



int main(){

    sqlite3* db;
    //sqlite3_stmt* stmt;


    sqlite3_open("storage.db", &db);

    initTables(db);




    return 0;
}

