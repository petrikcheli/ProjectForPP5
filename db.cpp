#include "db.h"

namespace dbPixels {
    db::db() {
        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
            con->setSchema("pixels");
            stmt = con->createStatement();
        }
        catch (sql::SQLException e)
        {
            std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
            system("pause");
            exit(1);
        }
    }
    sql::Connection* db::get_connection() { return con; }
    sql::PreparedStatement* db::get_preparementStatement() { return pstmt; }
    sql::Statement* db::get_statement() { return stmt; }

}