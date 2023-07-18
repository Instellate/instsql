//
// Created by instellate on 7/17/23.
//

#pragma once

#include <chrono>
#include <iterator>
#include <libpq-fe.h>
#include <string_view>
#include <variant>

namespace instsql::result {
    using ColumnVal = std::
            variant<std::monostate, std::string, int, long, std::chrono::time_point<std::chrono::system_clock>>;

    class Row {
    private:
        PGresult *result;
        int rowPos;

        static ColumnVal valToVariant(char *str, Oid type);

    public:
        Row(PGresult *pgresult, int colNum);
        Row(const Row &) noexcept = default;
        Row(Row &&) noexcept = default;

        ColumnVal operator[](const std::string &columnName) const;
        ColumnVal operator[](int columnPos) const;

        [[nodiscard]] PGresult *getResult() const;
        void setRowPosition(int pos);
    };
}// namespace instsql::result