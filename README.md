# RFID-2-MQTT
A simple mqtt client that publishes the current state of the RFID-RC522 reader. Based on https://github.com/mec-kon/simple-mqtt-client and https://github.com/Calvin-LL/RPi-MFRC522.

Upon every change of state of the rfid-reader (card appears, card disappears), a json state message is published: ```{"uid": "116:4:126:1", "present": "TRUE", "timestamp": "2009-11-10T23:00:00.0Z"}```. With uid equals the serial number of the present card and present equals TRUE if a card is present. If no card is present, uid is an empty string and present equals "FALSE". Timestamp is the local time when the card was accessed. 

The program listens on the subscribed topic for the message "TRUE". As soon as this message is received, it will broadcast the current state with the current timestamp. 

## Installation: ## 
### MQTT-Related ###
First you need to install all required dependencies.
You can do this with ```sudo apt-get install cmake libmosquittopp-dev build-essential``` on Debian or Ubuntu.

### RFID-Related ###
Get the RPI-MFRC522 implementation from https://github.com/tgd1975/RPi-MFRC522/, install the bcm2835 library, and build the mfrc522-library as described in the README.

### Build ###
1. Clone https://github.com/tgd1975/RFID-2-MQTT into the same folder as you have cloned RPI-MFRC522 into. Thus, the folder should contain at least the two subfolder ```RFID-2-MQTT``` and ```RPi-MFRC522```.
2. Change into the rfid-2-mqtt folder by entering ```cd RFID-2-MQTT```
3. Build the project by running the command
```bash
g++ -I ../RPi-MFRC522/lib src/*.cpp -lmosquittopp -L ../RPi-MFRC522/lib -lmfrc522 -lbcm2835 -std=c++17 -o rfid-2-mqtt
```
4. Runing the programm by entering
```bash
sudo ./rfid-2-mqtt
```

## Contribute ##

If you want to add more examples or improve the library, just create a pull request with proper commit message.
