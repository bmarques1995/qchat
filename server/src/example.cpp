#include <crow.h>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]{
        crow::json::wvalue x({{"message", "Hello, World!"}});
        x["message2"] = "Hello, World.. Again!";
        return x;
    });

    app.port(8000).run();
}