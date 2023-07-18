//
// Created by instellate on 7/17/23.
//

#include "instsql/result/Result.h"
#include <iostream>

namespace instsql::result {
    Result::Result(PGresult *pgresult) { this->result = pgresult; }

    Result::~Result() { PQclear(result); }

    Result::Iterator Result::begin() const {
        if (PQresultStatus(result) != PGRES_TUPLES_OK) {
            throw std::runtime_error("Not a tuple.");
        }
        return Result::Iterator({result, 0});
    }

    Result::Iterator Result::end() const {
        if (PQresultStatus(result) != PGRES_TUPLES_OK) {
            throw std::runtime_error("Not a tuple.");
        }
        return {{result, PQntuples(result)}, PQntuples(result)};
    }
    Row Result::operator[](int row) { return {result, row}; }

    Result::Iterator::Iterator(const Row &row) : pos(0), row(row) {
        this->lastPos = PQntuples(this->row.getResult());
    }

    Result::Iterator::Iterator(const Row &row, int pos) : pos(pos), lastPos(PQntuples(row.getResult())), row(row) {}

    bool Result::Iterator::operator==(const Result::Iterator &rhs) const { return this->pos == rhs.pos; }

    bool Result::Iterator::operator!=(const Result::Iterator &rhs) const { return this->pos != rhs.pos; }

    Result::Iterator &Result::Iterator::operator++() {
        ++pos;
        row.setRowPosition(pos);
        return *this;
    }

    Result::Iterator Result::Iterator::operator++(int) {
        Iterator tempIt{*this};
        ++pos;
        row.setRowPosition(pos);
        return tempIt;
    }

    Row &Result::Iterator::operator*() { return row; }
    Row *Result::Iterator::operator->() { return &row; }
}// namespace instsql::result