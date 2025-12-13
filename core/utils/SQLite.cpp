#include "core/utils/SQLite.h"

#include <format>

namespace Ps::Core {

void try_sqlite(int result)
{
    if ((result != SQLITE_OK) && (result != SQLITE_DONE) && (result != SQLITE_ROW)) {
        throw std::runtime_error{std::format("sqlite3 failed! {}: {}. ", result, sqlite3_errstr(result))};
    }
}

SQLiteStmt prepare_sqlite_stmt(sqlite3* db, std::string_view sql)
{
    sqlite3_stmt* stmt{nullptr};
    try_sqlite(sqlite3_prepare_v2(db, sql.data(), static_cast<int>(sql.length()), &stmt, nullptr));
    return SQLiteStmt{stmt};
}

}  // namespace Ps::Core
