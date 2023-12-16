#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
using namespace std;

// Menu Functions
void menu(sqlite3* db);
void addBoxtoDB(sqlite3* db);
void queryForBox(sqlite3* db);
void addItem(sqlite3* db);
void addItemToBox(sqlite3* db);
void searchForItem(sqlite3* db);

// Utility Functions
bool noReturnExec(string sqlExec, sqlite3* db);
void initTables(sqlite3* db);
long long int safeLongIntInput();
int  safeIntInput();

int coutCallbackWide(void* notUsed, int argc, char** argv, char** azColname);
int coutCallbackDense(void* notUsed, int argc, char** argv, char** azColname);


