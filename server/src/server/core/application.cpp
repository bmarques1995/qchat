#include "application.hpp"
#include "settings.hpp"
#include "urls.hpp"
#include <unordered_map>
#include "users.hpp"

const std::unordered_map<std::string, std::string> s_AllowedArgs
{
  {"-c", "config"},
  {"--config", "config"}
};

QChatServer::Application* QChatServer::Application::s_Instance = nullptr;

QChatServer::Application::Application(int argc, char** argv)
{
    EnableSingleton(this);
    ProcessArgList(argc, argv);
    auto it = m_ArgList.find("config");
    if(it != m_ArgList.end())
    {
        m_Settings.reset(new Settings(it->second));
    }
    SetupDatabase();
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

void QChatServer::Application::ProcessArgList(int argc, char** argv)
{
    int currentArg = 0;
    while((currentArg + 2) < argc)
    {
        auto it = s_AllowedArgs.find(argv[currentArg + 1]);
        if(it != s_AllowedArgs.end())
            m_ArgList[it->second] = argv[currentArg + 2];
        currentArg += 2;
    }
}

void QChatServer::Application::SetupDatabase()
{
    auto config = std::make_shared<sqlpp::postgresql::connection_config>();
    config->user = m_Settings->GetValue<std::string>("database", "user");
    config->dbname = m_Settings->GetValue<std::string>("database", "database");
    config->password = m_Settings->GetValue<std::string>("database", "password");
    config->host = m_Settings->GetValue<std::string>("database", "host");
    config->port = (uint16_t)m_Settings->GetValue<uint32_t>("database", "port");
    config->connect_timeout = 3;
    
    m_DB.connect_using(config);
}

void QChatServer::Application::EnableSingleton(Application* ptr)
{
    s_Instance = ptr;
}
