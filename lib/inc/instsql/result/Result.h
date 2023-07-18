//
// Created by instellate on 7/17/23.
//

#pragma once

#include "Row.h"
#include <libpq-fe.h>

namespace instsql::result {
    class Result {
    private:
        PGresult *result;

    public:
        explicit Result(PGresult *pgresult);

        ~Result();

        Row operator[](int row);

        class Iterator {
        private:
            int pos;
            int lastPos;
            Row row;

        public:
            using iterator_category = std::forward_iterator_tag;

            explicit Iterator(const Row &row);
            Iterator(const Row &row, int pos);
            Iterator(const Iterator &) noexcept = default;
            Iterator(Iterator &&) noexcept = default;

            bool operator==(const Iterator &rhs) const;
            bool operator!=(const Iterator &rhs) const;

            Iterator &operator++();
            Iterator operator++(int);

            Row &operator*();
            Row *operator->();
        };

        [[nodiscard]] Iterator begin() const;

        [[nodiscard]] Iterator end() const;
    };

}// namespace instsql::result
