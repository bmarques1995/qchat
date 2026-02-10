#pragma once

#include <json/json.h>
#include <json/value.h>
#include <algorithm>

namespace QChatServer
{
    class Settings
    {
    public:
        Settings();
        Settings(std::string file);

        ~Settings();

        template<typename T>
        T GetValue(const std::string context, const std::string key)
        {
            return m_Configs[context][key].as<T>();
        }

    private:
        std::string m_ConfigFile;
        Json::Value m_Configs;

        void ReadConfigFile();
    };
}