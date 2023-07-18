#include "../inc/instsql/Client.h"

#include <iostream>

namespace instsql {

    Client::Client(const std::string &connStr) {
        this->conn = PQconnectdb(connStr.c_str());
        if (PQstatus(this->conn) == CONNECTION_BAD) {
            throw std::runtime_error("Bad connection string.");
        }
    }

    Client::~Client() { PQfinish(conn); }

    result::Result Client::runStatement(const std::string &sql) {
        PGresult *result = PQexec(conn, sql.c_str());

        if (PQresultStatus(result) == PGRES_FATAL_ERROR) {
            throw std::runtime_error(PQerrorMessage(conn));
        }

        return result::Result(result);
    }

}// namespace instsql