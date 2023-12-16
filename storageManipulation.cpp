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


    if(!noReturnExec(sql, db)){
        system("pause"); //Pause to show error
    }
    
    

}

////////////////

void addItem(sqlite3* db){
    system("cls");

    cout << "Add an Item to Database\n";
    cout << "=======================\n";
    cout << "Item Name: ";

    string name;
    cin.ignore();
    getline(cin, name);


    cout << "Item Description: ";

    string description;

    getline(cin, description);

    cout << "Item Serial(Optinal): ";

    long long int serial = safeLongIntInput();


    string sql;

    if(serial == -1){
        //Invalid or no input

         sql = "INSERT INTO item (name, description) "
                 "VALUES (\"" + name + "\", \"" + description + "\");";


    }else{

        sql = "INSERT INTO item (serial, name, description) "
        "VALUES (" + to_string(serial) + " ,\"" + name + "\", \"" + description + "\");";

    }


    cout << sql; // debug
    system("pause"); //debug


    if(!noReturnExec(sql, db)){
        system("pause"); //Pause to show error
    }


}

////////////////

void queryForBox(sqlite3* db){
    system("cls");

    cout << "Query for Box\n";
    cout << "==============\n";
    cout << "Serial: ";

    long long int serial = safeLongIntInput();

    string sql = "SELECT * FROM box WHERE serial=" + to_string(serial) + ";";

    system("cls");

    cout << "==BOX DESCRIPTION==\n";

    sqlite3_exec(db, sql.c_str(), coutCallback, NULL, NULL);


    cout << "==CONTENTS OF BOX==\n";

    sql = "SELECT * FROM itembox WHERE boxid=" + to_string(serial) + ";";


    sqlite3_exec(db, sql.c_str(), coutCallback, NULL, NULL);


    system("pause");
}