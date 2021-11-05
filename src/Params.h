#ifndef PARAMS_H_
#define PARAMS_H_

#include <string>
#include <getopt.h>

class Params {
    public:
        std::string mqtt_id = "";
        std::string topic_publish = "";
        std::string topic_subscribe = "";
        std::string host = "";
        int port = -1;
        std::string username = "";
        std::string password = "";
        int pin_cs = -1;
        int pin_rst = -1;

        bool parseArgs(int argc, char **argv);
    
        Params();

        void print_usage();
        void print_params();

    private:
        std::string program_name = "";

        struct option long_options[10];

        bool all_params_valid();
        
        void set_mqtt_id(std::string optarg);
        void set_topic_publish(std::string optarg);
        void set_topic_subscribe(std::string optarg);
        void set_host(std::string optarg);
        void set_port(std::string optarg);
        void set_username(std::string optarg);
        void set_password(std::string optarg);
        void set_pin_cs(std::string optarg);
        void set_pin_rst(std::string optarg);
};


#endif // PARAMS_H_