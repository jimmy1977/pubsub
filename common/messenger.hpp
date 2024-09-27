#ifndef MESSENGER_HPP_
#define MESSENGER_HPP_

#include <atomic>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class Messenger {
  public:
    Messenger(int32_t sock, std::string address, uint16_t port)
        : sock_(sock), address_(address), port_(port), closing_(false), done_(false){};

    virtual ~Messenger() {
        cleanup();
    };

    virtual void handle() = 0;

    void cleanup() {
        closing_ = true;
        shutdown(sock_, SHUT_WR);
        shutdown(sock_, SHUT_RD);
        close(sock_);
    }

    bool done() {
        return done_;
    };

  protected:
    int32_t           sock_;
    std::string       address_;
    uint16_t          port_;
    std::atomic<bool> closing_;
    bool              done_;
};

#endif