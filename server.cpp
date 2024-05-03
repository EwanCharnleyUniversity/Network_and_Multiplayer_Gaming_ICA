#include "accepter.h"
#include "queue.h"
#include "list.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "myserver.h"


int main()
{
    myserver newServer;
    newServer.runServer();

    return 0;
}
