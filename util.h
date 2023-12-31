#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
using namespace std;

// Menu Functions
void menu(sqlite3* db);
void addSubMenu(sqlite3* db);
void querySubMenu(sqlite3* db);
void removeSubMenu(sqlite3* db);
void motifySubMenu(sqlite3* db);


// User selected Actions
void addBoxtoDB(sqlite3* db);
void queryForBox(sqlite3* db);
void addItem(sqlite3* db);
void addItemToBox(sqlite3* db);
void searchForItem(sqlite3* db);
void removeItemFromBox(sqlite3* db);
void removeBoxFromDatabase(sqlite3* db);
void removeItemFromDatabase(sqlite3* db);
void motifyQuantity(sqlite3* db);
void motifyBox(sqlite3* db);

// Utility Functions
bool noReturnExec(string sqlExec, sqlite3* db);
void initTables(sqlite3* db);
long long int safeLongIntInput();
int  safeIntInput();
string safeAndCheckedStringInput(bool doIgnore);

int coutCallbackWide(void* notUsed, int argc, char** argv, char** azColname);
int coutCallbackDense(void* notUsed, int argc, char** argv, char** azColname);

//Check Functions
bool blobStringCheck(string blobString);


