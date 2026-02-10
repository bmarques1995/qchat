#include "urls.hpp"
#include "info.hpp"

void QChatServer::RegisterRoutes(crow::SimpleApp *app)
{
    CROW_ROUTE((*app), "/add_json").methods("GET"_method)(info::GetSample);
    CROW_ROUTE((*app), "/add_json").methods("POST"_method)(info::PostSample);
}