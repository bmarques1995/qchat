#pragma once

#include <crow.h>
#include <sqlpp23/core/database/connection.h>
#include <sqlpp23/core/type_traits/data_type.h>
#include <sqlpp23/sqlpp23.h>
#include <sqlpp23/postgresql/postgresql.h>

namespace QChatServer
{
    class Application
    {
    public:
        Application(int argc, char** argv);
        ~Application();

        void Run();

        static Application* GetInstance();
    
    protected:
        static Application* s_Instance;
        crow::SimpleApp m_CrowApp;
        sqlpp::postgresql::connection m_DB;

        static void EnableSingleton(Application* ptr);
    };
}