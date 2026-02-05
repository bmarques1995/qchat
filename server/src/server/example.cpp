#include <crow.h>
#include <sqlpp23/core/database/connection.h>
#include <sqlpp23/core/type_traits/data_type.h>
#include <sqlpp23/sqlpp23.h>
#include <sqlpp23/postgresql/postgresql.h>
#include <iostream>

namespace db
{
  struct Users_
  {
    struct Id
    {
      SQLPP_CREATE_NAME_TAG_FOR_SQL_AND_CPP(id, id);
      using data_type = ::sqlpp::integral;
      using has_default = std::true_type;
    };

    struct Name
    {
      SQLPP_CREATE_NAME_TAG_FOR_SQL_AND_CPP(name, name);
      using data_type = ::sqlpp::text;
      using has_default = std::true_type;
    };

    SQLPP_CREATE_NAME_TAG_FOR_SQL_AND_CPP(users, users);
    template<typename T>
    using _table_columns = sqlpp::table_columns<T,
               Id,
               Name>;
    using _required_insert_columns = sqlpp::detail::type_set<>;
  };
  using Users = ::sqlpp::table_t<Users_>;
}

constexpr auto users = db::Users{};

int main() {

    auto config = std::make_shared<sqlpp::postgresql::connection_config>();
    config->user = "qchat";
    config->dbname = "qchat";
    config->password = "qchat_pq";
    config->host = "127.0.0.1";
    config->port = 5432;
    config->connect_timeout = 3;

    // Create a connection
    sqlpp::postgresql::connection db;
    db.connect_using(config);

    //db(insert_into(users).set(users.name = "foobar"));

    auto query = db(select(all_of(users)).from(users));

    for (const auto& row : query)
    {
        std::cout << "id=" << row.id
                << ", name=" << row.name << '\n';
    }

    crow::SimpleApp app;

    CROW_ROUTE(app, "/").methods("GET"_method)
    ([]{
        crow::json::wvalue x({{"message", "Hello, World!"}});
        x["message2"] = "Hello, World.. Again!";
        return x;
    });

    CROW_ROUTE(app, "/add_json")
        .methods("POST"_method)  // Specify that this route only accepts POST requests
        ([]{
            crow::json::wvalue x({{"message", "Hello, World!"}});
            x["message2"] = "Hello, World... this time from a POST";
            return x;
        });

    app.bindaddr("0.0.0.0").port(7700).run();
}