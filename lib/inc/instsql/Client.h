#pragma once

#include "result/Result.h"
#include <functional>
#include <libpq-events.h>
#include <string>
#include <vector>

namespace instsql {
    class Client {
    private:
        PGconn *conn;

    public:
        Client(const std::string &connStr);

        result::Result runStatement(const std::string &sql);

        ~Client();
    };
}// namespace instsql