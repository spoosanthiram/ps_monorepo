#pragma once

#include <sqlite3.h>

#include <memory>
#include <string_view>

namespace Ps::Core {

class SQLiteStmtDeleter
{
public:
    void operator()(sqlite3_stmt* stmt) const { sqlite3_finalize(stmt); }
};
using SQLiteStmt = std::unique_ptr<sqlite3_stmt, SQLiteStmtDeleter>;

void try_sqlite(int result);

/// @brief Prepare sqlite statement by calling sqlite3_prepare_v2
/// returns unique_ptr which automatically calls sqlite3_finalize on destruction
///
SQLiteStmt prepare_sqlite_stmt(sqlite3* db, std::string_view sql);

}  // namespace Ps::Core
