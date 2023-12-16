#include<iostream>
#include<string>
#include "sqlite/sqlite3.h"
#include "util.h"
using namespace std;



int main(){

    sqlite3* db;
    //sqlite3_stmt* stmt;


    sqlite3_open("storage.db", &db);

    initTables(db);

    menu(db);


    return 0;
}



void menu(sqlite3* db){

    while(true){
        system("cls");

        cout << "Storage System\n";
        cout << "==============\n";
        cout << "1. Add a Box\n";
        cout << "2. Add items to a Box\n";
        cout << "3. Add an Item\n";
        cout << "4. Querry a Box\n";
        cout << "5. Quit\n";

        int selection; 

        cin >> selection; //fix at some point to be better


        switch(selection){
            case 1:
                //add a box
                addBoxtoDB(db);
                break;
            case 2:
                //add items to box
                break;
            case 3:
                //Add item
                break;
            case 4:
                //querry for a box
                queryForBox(db);
                break;
            case 5:
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
