#include "application.hpp"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

int main(int argc, char** argv)
{
    QChatServer::Application app(argc, argv);
    app.Run();
    return 0;
}