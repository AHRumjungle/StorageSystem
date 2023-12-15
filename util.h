#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
using namespace std;

// Other Functions
void menu(sqlite3* db);
void addBoxtoDB(sqlite3* db);

// Utility Functions
void noReturnExec(string sqlExec, sqlite3* db);
void initTables(sqlite3* db);


