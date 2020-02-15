#include "iostream"
#include "sqlite3.h"

char INSERT_CMD[256] = "INSERT INTO QRID_MAIN_SEG (ID,COMPANY_NAME,INTERIOR_ID,COLOR)" \
                       "VALUES (\"000001\", \"CIDI\", \"001\", \"WHITE\");" \
                       "SELECT * from QRID_MAIN_SEG;";
char DELETE_CMD[256] = "DELETE from QRID_MAIN_SEG where ID=\"000001\";" \
                       "SELECT * from QRID_MAIN_SEG;";
char CREATE_CMD[256] = "CREATE TABLE QRID_MAIN_SEG (" \
                       "ID TEXT PRIMARY KEY NOT NULL," \
                       "COMPANY_NAME TEXT NOT NULL," \
                       "INTERIOR_ID TEXT NOT NULL," \
                       "COLOR TEXT NOT NULL);" \
                       "SELECT * from QRID_MAIN_SEG;";
char CHECK_TB_CMD[256] = "SELECT count(type) FROM sqlite_master WHERE type=\"table\" AND name=\"QRID_MAIN_SEG\"";
char SELECT_CMD[256] = "SELECT * from QRID_MAIN_SEG where ID=\"000001\"";

int id_exist = 0;
static int callback(void *notUsed, int argc, char **argv, char **azColName){
    id_exist = argc;
    for(int i=0; i<argc; ++i){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int table_exist = 0;
static int check_callback(void *notUsed, int argc, char **argv, char **azColName){
    table_exist = atoi(argv[0]);
    std::cout << "table exist: " << table_exist <<std::endl;
    return 0;
}


int main(int argc, char **argv){
    sqlite3* db;
    char* errMsg = NULL;
    
    if(argc != 3){
        std::cout << "Usage: " << argv[0] << " xx.db insert/delete" << std::endl;
        return -1;
    }

    do{
        int rc = sqlite3_open(argv[1], &db);
        if(rc){
            std::cout << "failed to open database " << argv[1] << std::endl;
            break; 
        }

        char* pcmd = NULL;
        // check if table exists
        pcmd = CHECK_TB_CMD;
        rc = sqlite3_exec(db, pcmd, check_callback, 0, &errMsg);

        if(table_exist == 0){
            std::cout << "creating table..." << std::endl;
            pcmd = CREATE_CMD;
            rc = sqlite3_exec(db, pcmd, callback, 0, &errMsg);
        }
        
        if(strcmp(argv[2], "insert") == 0){
            id_exist = 0;
            pcmd = SELECT_CMD;
            rc = sqlite3_exec(db, pcmd, callback, 0, &errMsg);
            if(id_exist){
                std::cout << "id exist, can not insert!" << std::endl;
                break;
            }
            else{
                pcmd = INSERT_CMD;
                rc = sqlite3_exec(db, pcmd, callback, 0, &errMsg);
            }
        }
        if(strcmp(argv[2], "delete") == 0){
            pcmd = DELETE_CMD;
            rc = sqlite3_exec(db, pcmd, callback, 0, &errMsg);
        }
        if(rc != SQLITE_OK){
            std::cout << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }while(false);
    sqlite3_close(db);

    return 0;
}