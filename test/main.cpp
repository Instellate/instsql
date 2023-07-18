//
// Created by instellate on 7/18/23.
//

#include "instsql/Client.h"
#include <iostream>


int main() {
    instsql::Client client("postgresql://postgres@localhost:5432/test");

    auto result = client.runStatement("SELECT * FROM test");

    for(const auto &row: result) {
        std::cout << "{ id: " << std::get<int>(row["id"]);
        std::cout << ", txt: \"" << std::get<std::string >(row["txt"]) << "\" } \n";
    }

    return 0;
}