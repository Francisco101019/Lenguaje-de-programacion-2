

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>

using namespace std;

int main()
{

    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;




    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    ret = SQLConnect(hDbc, (SQLWCHAR*)L"UNI", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {

        cout << "connected to database succesfully" << endl;

        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Empleado", SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {

            SQLCHAR Nombre[30];
                SQLCHAR Apellido_Paterno[30];
                while (SQLFetch(hStmt) == SQL_SUCCESS)
                {
                    SQLGetData(hStmt, 2, SQL_C_CHAR, Nombre, sizeof(Nombre), NULL);
                    SQLGetData(hStmt, 3, SQL_C_CHAR, Apellido_Paterno, sizeof(Apellido_Paterno), NULL);

                    cout << "+----------------+" << endl;
                    cout << "|    Nombre:     |"  << endl;
                    cout << "+----------------+" << endl;
                    cout << "|                |" << endl;
                        cout<<"| " << Nombre << " " << Apellido_Paterno  <<"  |"<< endl;
                        cout << "|                |" << endl;
                        cout << "|                |" << endl;
                        cout << "+----------------+" << endl;
                }


        }

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);


    }

    

    else {
        cout << "failed to connected to database." << endl;

    }

    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;

}


