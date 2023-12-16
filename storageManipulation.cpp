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

    cout << "Item Serial(Optinal, input 0 to skip): ";

    long long int serial = safeLongIntInput();


    string sql;

    if(serial == -1 || serial == 0){
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

    sqlite3_exec(db, sql.c_str(), coutCallbackWide, NULL, NULL);


    cout << endl << "==CONTENTS OF BOX==\n";

    string sql2 = "SELECT item.name, boxitem.quantity "
                  "FROM box "
                  "JOIN boxitem ON box.id = boxitem.boxid "
                  "JOIN item ON item.id = boxitem.itemid "
                  "WHERE box.serial = " + to_string(serial) + ";";



    sqlite3_exec(db, sql2.c_str(), coutCallbackDense, NULL, NULL);


    system("pause");
}


////////////////

void addItemToBox(sqlite3* db){
    system("cls");

    cout << "Add Item to Box\n";
    cout << "===============\n";
    cout << "1. Add by Item Name\n";
    cout << "2. Add by Item Serial\n";


    int input = safeIntInput();

    if(input == 1){
        //Add by Name

        system("cls");
        cout << "Add Item to Box by Name\n";
        cout << "=======================\n";

        cout << "Item Name: ";

        string itemName;
        cin.ignore();
        getline(cin, itemName);

        cout << "Quantity: ";

        int quantity = safeIntInput();

        cout << "Box Serial: ";

        long long int serial = safeLongIntInput();


        string sql = "INSERT INTO boxitem (boxid, itemid, quantity) "
                     "SELECT box.id, item.id, " + to_string(quantity) + " "
                     "FROM box, item "
                     "WHERE box.serial = " + to_string(serial) + " "
                     "AND item.name = \"" + itemName + "\";";

        noReturnExec(sql, db);

        //system("pause"); //debug


    }else if(input == 2){
        //Add by Serial


         system("cls");
        cout << "Add Item to Box by Serial\n";
        cout << "=======================\n";

        cout << "Item Serial: ";

        long long int itemSerial = safeLongIntInput();

        cout << "Quantity: ";

        int quantity = safeIntInput();


        cout << "Box Serial: ";

        long long int serial = safeLongIntInput();

        string sql = "INSERT INTO boxitem (boxid, itemid, quantity) "
                     "SELECT box.id, item.id, " + to_string(quantity) + " "
                     "FROM box, item "
                     "WHERE box.serial = " + to_string(serial) + " "
                     "AND item.serial = " + to_string(itemSerial) + ";";

        noReturnExec(sql, db);

    }


}

///////////////

void searchForItem(sqlite3* db){
    system("cls");

    cout << "Search for Item\n";
    cout << "===============\n";
    cout << "1. Fuzzy Search by Item Name/Description\n";
    cout << "2. Search by Item Serial\n";


    int input = safeIntInput(); //Make a dedicated safeIntInput()?

    if(input == 1){
        system("cls");
        cout << "Search for Item by Name/Description\n";
        cout << "=======================\n";
        cout << "Item Name/Description: ";

        string itemName;

        cin.ignore();
        getline(cin, itemName);

        cout << endl;
        cout << "==RESULTS==\n";

        string sql = "SELECT item.name, box.location AS \"box location\", box.description as \"box description\", boxitem.quantity "
                     "FROM box "
                     "JOIN boxitem ON box.id = boxitem.boxid "
                     "JOIN item ON item.id = boxitem.itemid "
                     "WHERE item.name LIKE '%' || \"" + itemName + "\" || '%' " 
                     "OR item.description LIKE '%' || \"" + itemName + "\" || '%';";


        sqlite3_exec(db, sql.c_str(), coutCallbackDense, NULL, NULL);


        cout << endl;
        system("pause");


    }else if(input == 2){
         system("cls");
        cout << "Search for Item by Serial\n";
        cout << "=======================\n";
        cout << "Item Serial: ";

        long long int serial = safeLongIntInput();


        cout << endl;
        cout << "==RESULTS==\n";

        string sql = "SELECT item.name, box.location AS \"box location\", box.description as \"box description\", boxitem.quantity "
                     "FROM box "
                     "JOIN boxitem ON box.id = boxitem.boxid "
                     "JOIN item ON item.id = boxitem.itemid "
                     "WHERE item.serial=" + to_string(serial) + ";";


        sqlite3_exec(db, sql.c_str(), coutCallbackDense, NULL, NULL);


        cout << endl;
        system("pause");


    }
}