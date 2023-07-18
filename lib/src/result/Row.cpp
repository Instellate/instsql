//
// Created by instellate on 7/17/23.
//

#include "../../inc/instsql/result/Row.h"

#include <postgresql/server/catalog/pg_type_d.h>

namespace instsql::result {
    Row::Row(PGresult *pgresult, int colNum) {
        this->result = pgresult;
        this->rowPos = colNum;
    }

    ColumnVal Row::operator[](const std::string &columnName) const {
        int pos = PQfnumber(result, columnName.c_str());
        if (pos < 0) {
            throw std::runtime_error("Table does not exist.");
        }

        int isNull = PQgetisnull(result, rowPos, pos);
        if (isNull) {
            return std::monostate{};
        }

        char *value = PQgetvalue(result, rowPos, pos);
        Oid type = PQftype(result, pos);
        return valToVariant(value, type);
    }

    ColumnVal Row::operator[](int columnPos) const {
        int amount = PQnfields(result);
        if (amount - 1 > columnPos) {
            throw std::runtime_error("Overflow");
        }

        int isNull = PQgetisnull(result, rowPos, columnPos);
        if (isNull) {
            return std::monostate{};
        }

        char *value = PQgetvalue(result, rowPos, columnPos);
        Oid type = PQftype(result, columnPos);
        return valToVariant(value, type);
    }

    ColumnVal Row::valToVariant(char *str, Oid type) {
        switch (type) {
            case TEXTOID:
            case VARCHAROID:
            case CHAROID:
                return std::string(str);
            case INT4OID:
                return std::stoi(str);
            case INT8OID:
                return std::stol(str);
            default:
                return std::monostate{};
        }
    }

    PGresult *Row::getResult() const { return this->result; }

    void Row::setRowPosition(int pos) {
        int amount = PQntuples(result);
        if (pos > amount) {
            throw std::runtime_error("Too big.");
        }
        rowPos = pos;
    }
}// namespace instsql::result