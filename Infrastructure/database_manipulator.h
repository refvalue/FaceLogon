#pragma once

#include <memory>
#include <optional>
#include <filesystem>

struct sqlite3;

namespace glasssix
{
    namespace hello
    {
        struct glasssix_hello_interactive_logon;

        /// <summary>
        /// A wrapper for manipulation of the databse.
        /// </summary>
        class database_manipulator
        {
        public:
            database_manipulator(const std::filesystem::path& database_path);
            virtual ~database_manipulator();

            /// <summary>
            /// Query the feature array of a user.
            /// </summary>
            /// <param name="info">The call information</param>
            /// <returns>The feature array</returns>
            std::optional<std::vector<float>> query_feature(const glasssix_hello_interactive_logon& info) const;
        private:
            std::shared_ptr<sqlite3> context_;
            std::filesystem::path database_path_;
        private:
            inline static const std::string query_feature_sql_ = u8R"(SELECT feature FROM account_info WHERE sid = ? AND name = ?)";
        };
    }
}
