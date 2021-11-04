#ifndef PARAMS_H_
#define PARAMS_H_

#include <string>

struct params {
    std::string mqtt_id;
    std::string topic_publish;
    std::string topic_subscribe;
    std::string host;
    int port;
    std::string username;
    std::string password;
    int pin_cs;
    int pin_rst;
};

params getParams(int argc, char **argv);

#endif // PARAMS_H_