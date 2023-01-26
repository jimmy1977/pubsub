#ifndef NETWORK_MANAGER_
#define NETWORK_MANAGER_

#include "messenger_factory.hpp"
#include <atomic>
#include <functional>
#include <list>
#include <mutex>
#include <thread>

class NetworkManager
{
public:
    NetworkManager(std::shared_ptr<MessengerFactory> factory, int port, int recvBufLen = 256 * 1024 /* 256k */)
        : messenger_factory_(factory), port_(port), recv_buf_len_(recvBufLen), closing_(false), callback_(nullptr){};
    ~NetworkManager();
    int execute();
    void cleanup();
    void prune_completed_threads();
    void periodic_thread();
    void handler(std::function<void(std::string, uint16_t, bool)> callback) {
        callback_ = callback;
    }

private:
    std:: shared_ptr<MessengerFactory>                messenger_factory_;
    int32_t                                           port_;
    int32_t                                           recv_buf_len_;
    std::mutex                                        threads_mutex_;
    std::unique_ptr<std::thread>                      periodic_thread_;
    std::list<std::unique_ptr<messenger_thread>>      threads_;
    std::atomic<bool>                                 closing_;
    int32_t                                           server_socket_;
    std:: function<void(std::string, uint16_t, bool)> callback_;

    const uint32_t PRUNING_PERIOD = 5;
};

#endif