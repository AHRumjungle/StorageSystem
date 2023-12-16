#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
#include "util.h"



bool noReturnExec(string sqlExec, sqlite3* db){
    char* err;

    int rc = sqlite3_exec(db, sqlExec.c_str(), NULL, NULL, &err);

    if(rc != SQLITE_OK){
        cout << "ERROR: " << err << endl;
        return false;
    }else{
        return true;
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



long long int safeLongIntInput(){
    string input;

    cin >> input;

    try{
        return stoll(input);
    }
    catch(std::invalid_argument){
        cout << "Invalid Input\n";
        system("pause");
        return -1;
    }

    return stoll(input);
}

int safeIntInput(){
    string input;

    cin >> input;

    try{
        return stoi(input);
    }
    catch(std::invalid_argument){
        cout << "Invalid Input\n";
        system("pause");
        return -1;
    }

    return stoi(input);
}


int coutCallbackWide(void* notUsed, int argc, char** argv, char** azColname){

    //cout << "Results: " << argc << endl; //debug

    for(int i = 0; i < argc; i++){
        cout << azColname[i] << ": " << argv[i] << endl;
    }


    return 0;
    
}

//////////////////

int coutCallbackDense(void* notUsed, int argc, char** argv, char** azColname){

    //cout << "Results: " << argc << endl; //debug

    for(int i = 0; i < argc; i++){
        
        if(i+1 < argc){
            cout << azColname[i] << ": " << argv[i] << " | ";
        } else {
            cout << azColname[i] << ": " << argv[i];
        }

        
    }

    cout << endl;

    return 0;
    
}