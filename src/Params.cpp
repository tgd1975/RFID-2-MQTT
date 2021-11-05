#include "Params.h"
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>


Params::Params() { 
  long_options[0] = {"mqtt_id",         required_argument, 0,  'm' };
  long_options[1] = {"topic_publish",   required_argument, 0,  't' };
  long_options[2] = {"topic_subscribe", required_argument, 0,  's' };
  long_options[3] = {"host",            required_argument, 0,  'h' };
  long_options[4] = {"port",            required_argument, 0,  'p' };
  long_options[5] = {"username",        required_argument, 0,  'u' };
  long_options[6] = {"password",        required_argument, 0,  'P' };
  long_options[7] = {"pin_cs",          required_argument, 0,  'c' };
  long_options[8] = {"pin_rst",         required_argument, 0,  'r' };
  long_options[9] = {0,                 0,                 0,  0   };
}

bool Params::parseArgs(int argc, char **argv) {
  program_name = std::string(argv[0]);

  int opt;
    int long_index =0;
    while ((opt = getopt_long_only(argc, argv,"", 
                   long_options, &long_index )) != -1) {
        std::string optionargument = std::string(optarg);
        switch (opt) {
             case 'm' : set_mqtt_id(optionargument); break;
             case 't' : set_topic_publish(optionargument); break;
             case 's' : set_topic_subscribe(optionargument); break;
             case 'h' : set_host(optionargument); break;
             case 'p' : set_port(optionargument); break;
             case 'u' : set_username(optionargument); break;
             case 'P' : set_password(optionargument); break;
             case 'c' : set_pin_cs(optionargument); break;
             case 'r' : set_pin_rst(optionargument); break;
             default: return false;
        }
    }

    return all_params_valid();
}

void Params::print_params() {
  std::cout << "set parameters:" << std::endl;
  std::cout << " -" << long_options[0].name << ": '" << mqtt_id << "'" << std::endl;
  std::cout << " -" << long_options[1].name << ": '" << topic_publish << "'" << std::endl;
  std::cout << " -" << long_options[2].name << ": '" << topic_subscribe << "'" << std::endl;
  std::cout << " -" << long_options[3].name << ": '" << host << "'" << std::endl;
  std::cout << " -" << long_options[4].name << ": " << port << std::endl;
  std::cout << " -" << long_options[5].name << ": '" << username << "'" << std::endl;
  std::cout << " -" << long_options[6].name << ": '" << password << "'" << std::endl;
  std::cout << " -" << long_options[7].name << ": " << pin_cs << std::endl;
  std::cout << " -" << long_options[8].name << ": " << pin_rst << std::endl;

}

void Params::print_usage() {
  std::cout << "usage:" << std::endl;
  std::cout << program_name;
  std::cout << " -" << long_options[0].name << " ID";
  std::cout << " -" << long_options[1].name << " TOPIC";
  std::cout << " -" << long_options[2].name << " TOPIC";
  std::cout << " -" << long_options[3].name << " HOST";
  std::cout << " -" << long_options[4].name << " PORT";
  std::cout << " -" << long_options[5].name << " USERNAME";
  std::cout << " -" << long_options[6].name << " PASSWORD";
  std::cout << " -" << long_options[7].name << " PIN";
  std::cout << " -" << long_options[8].name << " PIN";
  std::cout << std::endl;
}

bool Params::all_params_valid() {
  return (port > -1) && (pin_rst > -1) && (pin_cs > -1) && (!mqtt_id.empty()) && (!topic_publish.empty()) && 
         (!topic_subscribe.empty()) && (!host.empty()) && (!username.empty()) && (!password.empty());
}

void Params::set_mqtt_id(std::string optarg) {
  mqtt_id = optarg;
}

void Params::set_topic_publish(std::string optarg) {
  topic_publish = optarg;
}

void Params::set_topic_subscribe(std::string optarg) {
  topic_subscribe = optarg;
}

void Params::set_host(std::string optarg) {
  host = optarg;
}

void Params::set_port(std::string optarg) {
  try {
    port = stoi(optarg);
  } catch (...) {
    //
  }
}

void Params::set_username(std::string optarg) {
  username = optarg;
}

void Params::set_password(std::string optarg) {
  password = optarg;
}

void Params::set_pin_cs(std::string optarg) {
  try {
    pin_cs = stoi(optarg);
  } catch (...) {
    //
  }
}

void Params::set_pin_rst(std::string optarg) {
  try {
    pin_rst = stoi(optarg);
  } catch (...) {
    //
  }
}


