#include<string>
#include "sqlite/sqlite3.h"
using namespace std;

void noReturnExec(string sqlExec, sqlite3* db);

void initTables(sqlite3* db);




void noReturnExec(string sqlExec, sqlite3* db){
    char* err;

    int rc = sqlite3_exec(db, sqlExec.c_str(), NULL, NULL, &err);

    if(rc != SQLITE_OK){
        cout << "ERROR: " << err << endl;
    }
}


void initTables(sqlite3* db){
    //Create Tables
    string itemTable = "CREATE TABLE IF NOT EXISTS item("
        "id INTEGER NOT NULL UNIQUE," 
        "serial INTEGER UNIQUE," 
        "name TEXT,"
        "description BLOB,"
        "PRIMARY KEY(id AUTOINCREMENT));";

    noReturnExec(itemTable, db);

    string boxTable = "CREATE TABLE IF NOT EXISTS box ("
	"id	INTEGER NOT NULL UNIQUE,"
	"serial	INTEGER NOT NULL UNIQUE,"
	"location	BLOB,"
	"description	BLOB,"
	"PRIMARY KEY(id AUTOINCREMENT)"
    ");";

    noReturnExec(boxTable, db);


    string itemBoxTable = "CREATE TABLE IF NOT EXISTS boxitem ("
	"itemid	INTEGER NOT NULL,"
	"boxid	INTEGER NOT NULL,"
	"quantity	INTEGER NOT NULL DEFAULT 0,"
	"FOREIGN KEY(boxid) REFERENCES box(id),"
	"FOREIGN KEY(itemid) REFERENCES item(id)"
    ");";

    noReturnExec(itemBoxTable, db);
}