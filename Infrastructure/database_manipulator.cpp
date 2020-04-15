#include "stdafx.h"
#include "common.hpp"
#include "database_manipulator.h"
#include "glasssix_hello_interactive_logon.hpp"

#include <sqlite3.h>

#define SQLITE_SUCCESS(x) ((x) == SQLITE_OK)

namespace glasssix
{
    namespace hello
    {
        database_manipulator::database_manipulator(const std::filesystem::path& database_path) : database_path_{ database_path }
        {
            // Create all the paths if neccessary.
            std::filesystem::create_directories(database_path_.parent_path());

            // Open or create the database.
            sqlite3* context;
            if (SQLITE_SUCCESS(sqlite3_open(database_path_.u8string().c_str(), &context)))
            {
                context_.reset(context, sqlite3_close);
            }
        }

        database_manipulator::~database_manipulator()
        {
        }

        /// <summary>
        /// Query the feature array of a user.
        /// </summary>
        /// <param name="info">The call information</param>
        /// <returns>The feature array</returns>
        std::optional<std::vector<float>> database_manipulator::query_feature(const glasssix_hello_interactive_logon& info) const
        {
            if (!context_)
            {
                return std::nullopt;
            }

            // Create a SQL statement with parameters.
            sqlite3_stmt* statement;
            if (!SQLITE_SUCCESS(sqlite3_prepare_v2(context_.get(), query_feature_sql_.c_str(), static_cast<int>(query_feature_sql_.size()), &statement, nullptr)))
            {
                return std::nullopt;
            }

            std::shared_ptr<sqlite3_stmt> statement_scope{ statement, sqlite3_finalize };
            
            // Bind all parameters.
            int index = 1;
            if (!SQLITE_SUCCESS(sqlite3_bind_text16(statement, index++, info.user_sid.Buffer, info.user_sid.Length, nullptr)))
            {
                return std::nullopt;
            }

            if (!SQLITE_SUCCESS(sqlite3_bind_text16(statement, index++, info.user_name.Buffer, info.user_name.Length, nullptr)))
            {
                return std::nullopt;
            }

            // Evaluate the statement and get the first row.
            if (sqlite3_step(statement) != SQLITE_ROW)
            {
                return std::nullopt;
            }

            // Check the count of the columns.
            if (sqlite3_column_count(statement) < 1)
            {
                return std::nullopt;
            }

            // Get the feature size.
            auto size = sqlite3_column_bytes(statement, 0);
            if (size <= 0)
            {
                return std::nullopt;
            }
            
            // Get the feature text encoded in Base64.
            auto text = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

            return common::base64_decode_as<float>(text, size);
        }
    }
}
