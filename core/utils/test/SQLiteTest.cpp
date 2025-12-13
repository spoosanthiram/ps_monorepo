#include "core/utils/SQLite.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("SQLite try_sqlite throw")
{
    sqlite3* db{nullptr};
    REQUIRE_THROWS(Ps::Core::try_sqlite(sqlite3_open_v2("non_existing.db", &db, SQLITE_OPEN_READONLY, nullptr)));
    if (db != nullptr) {
        sqlite3_close(db);
    }
}

TEST_CASE("SQLite try_sqlite no_throw")
{
    sqlite3* db{nullptr};
    REQUIRE_NOTHROW(
        Ps::Core::try_sqlite(sqlite3_open_v2("core/utils/test/data/infostore.db", &db, SQLITE_OPEN_READONLY, nullptr)));
    REQUIRE_NOTHROW(Ps::Core::try_sqlite(sqlite3_close(db)));
}

TEST_CASE("SQLite Stmt")
{
    sqlite3* db{nullptr};
    REQUIRE_NOTHROW(
        Ps::Core::try_sqlite(sqlite3_open_v2("core/utils/test/data/infostore.db", &db, SQLITE_OPEN_READONLY, nullptr)));
    {
        std::string_view sql{"SELECT name, website FROM Login"};
        auto stmt = Ps::Core::prepare_sqlite_stmt(db, sql);
        Ps::Core::try_sqlite(sqlite3_step(stmt.get()));
        auto col_text = sqlite3_column_text(stmt.get(), 0);
        size_t col_text_len = sqlite3_column_bytes(stmt.get(), 0);
        std::string name{col_text, &col_text[col_text_len]};
        REQUIRE(name == "Google Account");
    }
    REQUIRE_NOTHROW(Ps::Core::try_sqlite(sqlite3_close(db)));
}
