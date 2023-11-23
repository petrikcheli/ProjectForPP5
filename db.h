#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/resultset.h"
#include "cppconn/exception.h"

namespace dbPixels {
    class db
    {
    private:
        const std::string server = "127.0.0.1:3306";
        const std::string username = "root";
        const std::string password = "root";

        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;

    public:
        db();
        sql::Connection* get_connection();
        sql::Statement * get_statement();
        sql::PreparedStatement* get_preparementStatement();

    };
}
