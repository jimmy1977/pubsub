//#include "util/util_telemetry.hpp"
//#include "util/util_webserver.hpp"
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <signal.h>
#include <thread>
#include <unistd.h>

//#include "ar_log.h"
//#include "discovery_connection.hpp"
//#include "discovery_connection_factory.hpp"
#include "network_manager.hpp"
#include "version.h"

#if 0 
class DiscoveryServerSettings {

  public:
    DiscoveryServerSettings() : port_(21000), web_server_port_(21001), webserver_on_(true) {
    }

    static void display_usage() {
        INFO("Usage ./discovery_server [-p PORT] [-w WEB_SERVER_PORT] [-n SHUTOFF WEB_SERVER_PORT]");
        INFO("By default the webserver is on. If -n is supplied, it will be shut off.");
    }

    bool parse_args(int argc, char** argv) {
        int c;
        while ((c = getopt(argc, argv, "np:w:v")) != -1) {
            switch (c) {
            case 'p':
                port_ = atoi(optarg);
                INFO("Setting discovery port to %d", port_);
                break;
            case 'w':
                web_server_port_ = atoi(optarg);
                INFO("Setting web server port to %d", web_server_port_);
                break;
            case 'n':
                webserver_on_ = false;
                break;
            case 'v':
                printf("%d.%d.%s\n", MAJOR_VERSION, MINOR_VERSION, GIT_TAG_COUNT);
                return false;
            case '?':
                ERROR("invalid option: -%c", optopt);
                display_usage();
                return false;
            }
        }
        return true;
    }

    uint16_t getPort() const {
        return port_;
    }

    uint16_t getWebServerPort() const {
        return web_server_port_;
    }

    bool webserverOn() const {
        return webserver_on_;
    }

  private:
    uint16_t port_;
    uint16_t web_server_port_;
    bool webserver_on_;
};

// same function in util_telemetry, but that's a member fucntion
std::string hostname() {
    char* hostip = std::getenv("HOSTIP");
    if (hostip != NULL) {
        return std::string(hostip);
    } else {
        char buffer[256];
        struct hostent* host_entry;
        int my_hostname;
        // To retrieve hostname
        my_hostname = gethostname(buffer, sizeof(buffer));
        // To retrieve host information
        host_entry = gethostbyname(buffer);
        hostip = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));
        (void)my_hostname;
        return std::string(hostip);
    }
}
#endif 

int main(int argc, char** argv) {
    // make sure we don't exit when writing to a broken tcp connection via receiving SIGPIPE
    signal(SIGPIPE, SIG_IGN);
#if 0 
    DiscoveryServerSettings settings;
    if (!settings.parse_args(argc, argv)) {
        return EXIT_FAILURE;
    }
#endif 
    INFO("discovery_server version - %d.%d.%s-%s (%s) (%s)", MAJOR_VERSION, MINOR_VERSION, GIT_TAG_COUNT, GIT_HASH,
         BUILD_TYPE, GIT_BRANCH);


#if 0 
    std::shared_ptr<DiscoveryConnectionFactory> discovery_factory = std::make_shared<DiscoveryConnectionFactory>();
    std::unique_ptr<NetworkManager> disc_nm = std::make_unique<NetworkManager>(discovery_factory, settings.getPort());
    std::thread discovery_nm_th(&NetworkManager::execute, disc_nm.get());

    if (settings.webserverOn()) {
        auto callback =
            std::bind(&DiscoveryConnectionFactory::webServerCallback, discovery_factory, std::placeholders::_1);
        std::unique_ptr<util::Webserver> ws = std::make_unique<util::Webserver>(
            hostname(), settings.getWebServerPort(), std::vector<std::string>{"about", "topic"}, callback);
        std::thread ws_th(&util::Webserver::start, ws.get());
        // wait until the webserver thread to join
        ws_th.join();
        if (disc_nm)
            disc_nm->cleanup();
    }

    discovery_nm_th.join();
#endif
    INFO("exited discovery server");
    return 0;
}