#ifndef MESSENGER_FACTORY_
#define MESSENGER_FACTORY_

#include <thread>

class Messenger;

using messenger_thread = std::pair<std::unique_ptr<Messenger>, std::unique_ptr<std::thread>>;

class MessengerFactory {
  public:
    MessengerFactory(){};
    virtual ~MessengerFactory(){};

    virtual std::unique_ptr<messenger_thread> attach(int sock, std::string address, uint16_t port) = 0;
};

#endif