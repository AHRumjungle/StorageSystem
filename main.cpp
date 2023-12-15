#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
using namespace std;

void noReturnExec(string, sqlite3*);

int main(){

    sqlite3* db;
    //sqlite3_stmt* stmt;


    sqlite3_open("test.db", &db);

    noReturnExec("CREATE TABLE IF NOT EXISTS test(id INT, num INT);", db);

 

    cout << "SQL Include test\n";

    return 0;
}




void noReturnExec(string sqlExec, sqlite3* db){
    char* err;

    int rc = sqlite3_exec(db, sqlExec.c_str(), NULL, NULL, &err);

    if(rc != SQLITE_OK){
        cout << "ERROR: " << err << endl;
    }
}