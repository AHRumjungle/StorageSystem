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

        if(serial == 0){
            //exit option
            return;
        }

        cout << "Box Location: ";

        location = safeAndCheckedStringInput(true);



        cout << "Box Description: ";

        
        description = safeAndCheckedStringInput(false);

  

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
    name = safeAndCheckedStringInput(true);


    cout << "Item Description: ";

    string description;

    description = safeAndCheckedStringInput(false);

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


    //cout << sql; // debug
    //system("pause"); //debug


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

        itemName = safeAndCheckedStringInput(true);

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


    int input = safeIntInput();

    if(input == 1){
        system("cls");
        cout << "Search for Item by Name/Description\n";
        cout << "=======================\n";
        cout << "Item Name/Description: ";

        string itemName;

        itemName = safeAndCheckedStringInput(true);

        cout << endl;
        cout << "==CLOSEST MATCHES==\n";

        string sql1 = "SELECT name FROM item WHERE name LIKE '%' || \"" + itemName + "\" || '%' " 
                      "OR description LIKE '%' || \"" + itemName + "\" || '%' "
                      "LIMIT 3;";

        //cout << sql1 << endl; //Debug
        //system("pause"); //Debug

        sqlite3_exec(db, sql1.c_str(), coutCallbackDense, NULL, NULL);


        cout << endl;
        cout << "==RESULTS==\n";

        string sql2 = "SELECT item.name, box.location AS \"box location\", box.description as \"box description\", boxitem.quantity "
                     "FROM box "
                     "JOIN boxitem ON box.id = boxitem.boxid "
                     "JOIN item ON item.id = boxitem.itemid "
                     "WHERE item.name LIKE '%' || \"" + itemName + "\" || '%' " 
                     "OR item.description LIKE '%' || \"" + itemName + "\" || '%';";


        sqlite3_exec(db, sql2.c_str(), coutCallbackDense, NULL, NULL);


        cout << endl;
        system("pause");


    }else if(input == 2){
        //Search By Serial

         system("cls");
        cout << "Search for Item by Serial\n";
        cout << "=======================\n";
        cout << "Item Serial: ";

        long long int serial = safeLongIntInput();

        system("cls");
        cout << "==ITEM DESCRIPTION==\n";

        string sql = "SELECT * FROM item WHERE serial =" + to_string(serial) + ";";

        sqlite3_exec(db, sql.c_str(), coutCallbackWide, NULL, NULL);


        cout << endl;
        cout << "==RESULTS==\n";

        sql = "SELECT item.name, box.location AS \"box location\", box.description as \"box description\", boxitem.quantity "
                     "FROM box "
                     "JOIN boxitem ON box.id = boxitem.boxid "
                     "JOIN item ON item.id = boxitem.itemid "
                     "WHERE item.serial=" + to_string(serial) + ";";


        sqlite3_exec(db, sql.c_str(), coutCallbackDense, NULL, NULL);


        cout << endl;
        system("pause");


    }
}


//////////////////


void removeItemFromBox(sqlite3* db){

     system("cls");

    cout << "Remove Item to Box\n";
    cout << "==================\n";
    cout << "1. Remove by Item Name\n";
    cout << "2. Remove by Item Serial\n";


    int input = safeIntInput();

    if(input == 1){
        //Add by Name

        system("cls");
        cout << "Remove Item to Box by Name\n";
        cout << "==========================\n";

        cout << "Item Name: ";

        string itemName;

        itemName = safeAndCheckedStringInput(true);

        cout << "Box Serial: ";

        long long int serial = safeLongIntInput();


        string sql = "DELETE FROM boxitem "
                     "WHERE boxid = ( "
                     "  SELECT id FROM box WHERE serial = " + to_string(serial) + " "
                     ") AND itemid = ( "
                     "  SELECT id FROM item WHERE name LIKE '%' || \"" + itemName + "\" || '%' "
                     ");";

        noReturnExec(sql, db);

        //system("pause"); //debug


    }else if(input == 2){
        //Remove by Serial


         system("cls");
        cout << "Remove Item to Box by Serial\n";
        cout << "============================\n";

        cout << "Item Serial: ";

        long long int itemSerial = safeLongIntInput();


        cout << "Box Serial: ";

        long long int boxSerial = safeLongIntInput();

        string sql = "DELETE FROM boxitem "
                     "WHERE boxid = "
                        "(SELECT id FROM box WHERE serial = " + to_string(boxSerial) + ") "
                     "AND itemid = "
                        "(SELECT id FROM item WHERE serial = " + to_string(itemSerial) + ")"
                     ";";

        noReturnExec(sql, db);

    }


}


////////////////////////


void removeBoxFromDatabase(sqlite3* db){
    system("cls");
    cout << "Remove Box From Database\n";
    cout << "========================\n";
    cout << "Box Serial (Type 0 to quit): ";


    long long int boxSerial = safeLongIntInput();

    if(boxSerial == 0){
        return;
    }

    while(true){

    
        system("cls");
        cout << "==DANGER==\n";
        cout << "You are about to delete a box with the serial: " << boxSerial << " and all connections with items.\n";
        cout << "Are you sure you want to continue? (y, n):\n";

        char choice;

        cin >> choice;


        if(choice == 'n'){
            return;
        }else if(choice == 'y'){

            string sql1 = "DELETE FROM boxitem WHERE boxid = (SELECT id FROM box WHERE serial = " + to_string(boxSerial) + ");";

            noReturnExec(sql1, db);


            string sql2 = "DELETE FROM box WHERE serial = " + to_string(boxSerial) + ";";

            noReturnExec(sql2, db);


            cout << "Deleted box with serial: " << boxSerial << endl;
            system("pause");

            return;
        }

    }
    

}


///////////////////////////


void removeItemFromDatabase(sqlite3* db){
    system("cls");
    cout << "Remove Item From Database\n";
    cout << "=========================\n";
    cout << "1. Remove Item by Name\n";
    cout << "2. Remove Item by Serial\n";
    cout << "0. Back\n";

    int selection3 = safeIntInput();

    if(selection3 == 0){
        return;
    }

    if(selection3 == 1){
        //Remove by Name


        system("cls");
        cout << "Remove Item From Database by Name\n";
        cout << "===================================\n";
        cout << "Item Name: ";

        string itemName;

        itemName = safeAndCheckedStringInput(true);

        while(true){
            system("cls");
            cout << "==DANGER==\n";
            cout << "You are about to delete an item with the name: \"" << itemName << "\" and all connections with boxes.\n";
            cout << "Are you sure you want to continue? (y, n):\n";

            char choice;

            cin >> choice;

            if(choice == 'n'){

            return;

            }else if(choice == 'y'){

                string sql1 = "DELETE FROM boxitem WHERE itemid = (SELECT ID FROM item WHERE name = \"" + itemName + "\");";

                noReturnExec(sql1, db);

                string sql2 = "DELETE FROM item WHERE name = \"" + itemName + "\";";

                noReturnExec(sql2, db);

                cout << "Item with name \"" << itemName << "\" has been deleted\n";
                system("pause");
                return;

            }
         }



    }else if(selection3 == 2){
        //Remove by Serial

        system("cls");
        cout << "Remove Item From Database by Serial\n";
        cout << "===================================\n";
        cout << "Item Serial: ";

        long long int itemSerial = safeLongIntInput();


        while(true){
            system("cls");
            cout << "==DANGER==\n";
            cout << "You are about to delete an item with the serial: " << itemSerial << " and all connections with boxes.\n";
            cout << "Are you sure you want to continue? (y, n):\n";

            char choice;

            cin >> choice;

            if(choice == 'n'){

            return;

            }else if(choice == 'y'){
                
                string sql1 = "DELETE FROM boxitem WHERE itemid = (SELECT id FROM item WHERE serial = " + to_string(itemSerial) + ");";

                noReturnExec(sql1, db);

                string sql2 = "DELETE FROM item WHERE serial = " + to_string(itemSerial) + ";";

                noReturnExec(sql2, db);

                
                cout << "Item with serial: " << itemSerial << " has been deleted from the database\n";
                system("pause");

                return;

            }
        }

    }
}


//////////////////////


void motifyQuantity(sqlite3* db){
    system("cls");

    cout << "Motify Quantity of Item in Box\n";
    cout << "==============================\n";
    cout << "1. Motify by Item Name\n";
    cout << "2. Motify by Item Serial\n";
    cout << "0. Back\n";

    int selection2 = safeIntInput();

    if(selection2 == 0){
        return;
    }


    if(selection2 == 1){
        //Motify by Name

        system("cls");
        cout << "Motify Quantity of Item in Box by Name\n";
        cout << "======================================\n";
        cout << "Item Name: ";

        string itemName;

        itemName = safeAndCheckedStringInput(true);

        cout << "New Quantity: ";
        int newQuantity = safeIntInput();

        cout << "Box Serial: ";
        long long int boxSerial = safeLongIntInput();


        string sql = "UPDATE boxitem "
                     "SET quantity = " + to_string(newQuantity) + " "
                     "WHERE itemid = "
                        "(SELECT id FROM item WHERE name = \"" + itemName + "\") " 
                     "AND boxid = "
                        "(SELECT id FROM box WHERE serial = " + to_string(boxSerial) + ")"
                     ";";


        //cout << sql << endl; // Debug
        //system("pause");     //

        noReturnExec(sql, db);
        
    }




    if(selection2 == 2){
        //Motify by Serial

        system("cls");
        cout << "Motify Quantity of Item in Box by Serial\n";
        cout << "========================================\n";
        cout << "Item Serial: ";

        long long int itemSerial = safeLongIntInput();

        cout << "New Quantity: ";
        int newQuantity = safeIntInput();

        cout << "Box Serial: ";
        long long int boxSerial = safeLongIntInput();


        string sql = "UPDATE boxitem "
                     "SET quantity = " + to_string(newQuantity) + " "
                     "WHERE itemid = "
                        "(SELECT id FROM item WHERE serial = " + to_string(itemSerial) + ") " 
                     "AND boxid = "
                        "(SELECT id FROM box WHERE serial = " + to_string(boxSerial) + ")"
                     ";";


        //cout << sql << endl; // Debug
        //system("pause");     //

        noReturnExec(sql, db);
    }
}

///////////////////////////////////

void motifyBox(sqlite3* db){
    system("cls");

    cout << "Motify Box\n";
    cout << "==========\n";
    cout << "1. Motify Location\n";
    cout << "2. Motify Description\n";
    cout << "0. Back\n";

    int selection = safeIntInput();

    if (selection == 0){
        return;
    }


    if(selection == 1){
        //Motify Location
        system("cls");

        cout << "Motify Box Location\n";
        cout << "===================\n";
        cout << "Box Serial: ";

        long long int boxSerial = safeLongIntInput();

        cout << "New Location: ";

        string newLocation = safeAndCheckedStringInput(true);

        string sql = "UPDATE box "
                     "SET location = \"" + newLocation + "\" "
                     "WHERE serial = " + to_string(boxSerial) + ";";

        noReturnExec(sql, db);

        return;

    }

    if(selection == 2){
        //Motify Description
        system("cls");

        cout << "Motify Box Description\n";
        cout << "===================\n";
        cout << "Box Serial: ";

        long long int boxSerial = safeLongIntInput();

        cout << "New Description: ";

        string newDescription = safeAndCheckedStringInput(true);

        string sql = "UPDATE box "
                     "SET description = \"" + newDescription + "\" "
                     "WHERE serial = " + to_string(boxSerial) + ";";

        noReturnExec(sql, db);

        return;
    }

    return;
}