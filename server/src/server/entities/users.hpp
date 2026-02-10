#pragma once

namespace entity
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

namespace QChatServer
{
    constexpr auto users = entity::Users{};
}
