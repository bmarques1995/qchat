#include "info.hpp"

crow::json::wvalue QChatServer::info::GetSample()
{    
    crow::json::wvalue x({{"message", "Hello, World!"}});
    x["message2"] = "Hello, World.. Again!";
    return x;
}

crow::json::wvalue QChatServer::info::PostSample()
{
    crow::json::wvalue x({{"message", "Hello, World!"}});
    x["message2"] = "Hello, World... this time from a POST";
    return x;
}
