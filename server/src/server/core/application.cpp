#include "application.hpp"
#include "urls.hpp"

QChatServer::Application* QChatServer::Application::s_Instance = nullptr;

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

constexpr auto users = entity::Users{};

QChatServer::Application::Application(int argc, char** argv)
{
    EnableSingleton(this);
    auto config = std::make_shared<sqlpp::postgresql::connection_config>();
    config->user = "qchat";
    config->dbname = "qchat";
    config->password = "qchat_pq";
    config->host = "127.0.0.1";
    config->port = 5432;
    config->connect_timeout = 3;

    // Create a connection
    
    m_DB.connect_using(config);

    //m_DB(insert_into(users).set(users.name = "foobar"));

    auto query = m_DB(select(all_of(users)).from(users));

    for (const auto& row : query)
    {
        std::cout << "id=" << row.id
                << ", name=" << row.name << '\n';
    }

    RegisterRoutes(&m_CrowApp);
}

QChatServer::Application::~Application()
{

}

void QChatServer::Application::Run()
{
    m_CrowApp.bindaddr("0.0.0.0").port(7700).run();
}

QChatServer::Application* QChatServer::Application::GetInstance()
{
    return s_Instance;
}

void QChatServer::Application::EnableSingleton(Application* ptr)
{
    s_Instance = ptr;
}