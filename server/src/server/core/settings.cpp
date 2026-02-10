#include "settings.hpp"
#include <iostream>
#include <fstream>

QChatServer::Settings::Settings()
{

}

QChatServer::Settings::~Settings()
{

}

QChatServer::Settings::Settings(std::string file) :
    m_ConfigFile(file)
{
    std::string output;
    ReadConfigFile();
}

void QChatServer::Settings::ReadConfigFile()
{
    std::ifstream ifs;
    ifs.open(m_ConfigFile);

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &m_Configs, &errs)) {
        std::cout << errs << std::endl;
    }
}
