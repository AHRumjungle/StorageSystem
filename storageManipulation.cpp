#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
#include "util.h"

using namespace std;


void addBoxtoDB(sqlite3* db){
    long long int serial;
    string location;
    string description;

    while(true){

        system("cls");
        cout << "Add a Box to Data Base\n";
        cout << "======================\n";


        cout << "Box Serial Number: ";

        
        serial = safeLongIntInput();

        cout << "Box Location: ";

        
        cin.ignore();
        getline(cin, location);


        cout << "Box Description: ";

        
        getline(cin, description);


        system("cls");

        cout << "Serial: " << serial << endl;
        cout << "Location: " << location << endl;
        cout << "Description: " << description << endl;
        cout << endl;
        cout << "Is this correct?(y, n)\n";

        char selection;
        cin >> selection;

        if(selection == 'y'){
            break;
        }

    }


    system("cls");
    //build sql statement

    string sql = "INSERT INTO box (serial, location, description) "
                 "VALUES (" + to_string(serial) + ", \"" + location + "\", \"" + description + "\");";



    //cout << sql << endl; //debug
    //system("pause"); //debug


    noReturnExec(sql, db);
    
    system("pause");

}


////////////////

void queryForBox(sqlite3* db){
    system("cls");

    cout << "Querry for Box\n";
    cout << "==============\n";
    cout << "Serial: ";

    long long int serial = safeLongIntInput();

    string sql = "SELECT * FROM box WHERE serial=" + to_string(serial) + ";";



    sqlite3_exec(db, sql.c_str(), coutCallback, NULL, NULL);

    system("pause");
}