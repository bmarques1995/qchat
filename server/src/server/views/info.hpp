#pragma once

#include <crow/json.h>

namespace QChatServer
{
    namespace info
    {
        crow::json::wvalue GetSample();
        crow::json::wvalue PostSample();
    }
}