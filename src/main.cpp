#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h> // getuid

#include "Mqtt.h"
#include "Params.h"
#include "MFRC522.h"

std::string formatAs02X(uint8_t hex) {
    char buff[100];
    snprintf(buff, sizeof(buff), "%02X", hex);
    return buff;
}

std::string uidToString(uint8_t *buffer, size_t bufferSize) {
    std::string result = "";
    for (size_t i=0; i<bufferSize; i++) {
        result.append(":"+formatAs02X(buffer[i]));
    }
    if (!result.empty()) {
        result = result.substr(2);
    }
    return result;
}

int main(int argc, char **argv) {
    Params p = Params();
    if (!p.parseArgs(argc, argv)) {
        p.print_usage();
        return 1;
    }

    if (getuid()) {
        std::cout << "programm must be executed as root." << std::endl;
        return 1;
    }

    p.print_params();

    Mqtt *mqtt = new Mqtt(p.mqtt_id, p.topic_publish, p.topic_subscribe, p.host, p.port, p.username, p.password);
    MFRC522 rfid = MFRC522(p.pin_cs, p.pin_rst);  // Instance of the class
    
    State rfid_state = State();

    rfid.PCD_Init();  

    while (1) {
        if (rfid.PICC_IsCardPresent()) {
            if (!rfid_state.getCardPresent()) {
                if (rfid.PICC_ReadCardSerial()) {
                    rfid_state.setValues(uidToString(rfid.uid.uidByte, rfid.uid.size), true);
                    mqtt->publishRfidState(rfid_state);
                }
            }
            rfid.PICC_HaltA();
            rfid.PCD_StopCrypto1();
        } else {
            if (rfid_state.getCardPresent()) {
                // debouncing - wait for 100 ms and try again
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (!rfid.PICC_IsCardPresent()) {
                    rfid_state.setValues("", false);
                    mqtt->publishRfidState(rfid_state);
                } else {
                    rfid.PICC_HaltA();
                    rfid.PCD_StopCrypto1();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    delete mqtt;

    return 0;
}
