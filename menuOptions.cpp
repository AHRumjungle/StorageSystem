#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
#include "util.h"


void menu(sqlite3* db){

    while(true){
        system("cls");

        cout << "Storage System\n";
        cout << "==============\n";
        cout << "1. Add\n";
        cout << "2. Query\n";
        cout << "3. Remove\n";
        cout << "4. Exit\n";
     
        int selection; 

        selection = safeIntInput();


        switch(selection){
            case 1:
                //Add Menu
                addSubMenu(db);
                break;
            case 2:
                querySubMenu(db);
                break;
            case -1:
                break;
            default:
                cout << "Invalid Input\n";
                system("pause");
                break;
            
            case 4:
                //close data base and exit

                int rc =  sqlite3_close(db);

                if(rc == SQLITE_OK){
                    exit(0);
                }else{
                    cout << "Error: " << rc << endl;
                    system("pause");
                }
                break;
        }
    }

}

////////////////////////////

void addSubMenu(sqlite3* db){
    while(true){
        system("cls");
        cout << "Add Menu\n";
        cout << "========\n";
        cout << "1. Add Item to Database\n";
        cout << "2. Add Box to Database\n";
        cout << "3. Add Item to Box\n";
        cout << "0. Back\n";

        int selection2 = safeIntInput();

        switch(selection2){
            case 1:
                //Add Item
                addItem(db);
                break;
            case 2:
                //Add Box
                addBoxtoDB(db);
                break;
            case 3:
                //Add item to box
                addItemToBox(db);
                break;
            case 0:
                return;
                break;
            case -1:
                break;
            default:
                cout << "Invalid Input\n";
                system("pause");
                break;
        }


    }
}


///////////////////


void querySubMenu(sqlite3* db){
    while(true){
        system("cls");
        cout << "Query Menu\n";
        cout << "==========\n";
        cout << "1. Query For Item\n";
        cout << "2. Query For Box\n";
        cout << "0. Back\n";

        int selection2 = safeIntInput();

        switch(selection2){
            case 1:
                searchForItem(db);
                break;
            case 2:
                queryForBox(db);
                break;
            case 0:
                return;
                break;
            case -1:
                break;
            default:
                cout << "Invalid Input\n";
                system("pause");
                break;
        }
    }
}