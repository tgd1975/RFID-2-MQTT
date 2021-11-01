# RFID-2-MQTT
a simple mqtt client that publishes the current state of the RFID-RC522 reader. Based on https://github.com/mec-kon/simple-mqtt-client and https://github.com/Calvin-LL/RPi-MFRC522.

## Installation: ## 
First you need to install all required dependencies.
You can do this with ```sudo apt-get install cmake libmosquittopp-dev build-essential``` on Debian or Ubuntu.

Then, all you have to do is create a new folder with ```mkdir build``` in the current project folder, change to this folder with ```cd build``` and create a makefile  
with ```cmake ..``` .  
Then you can create the executables by simply typing ```make```  

## Contribute ##

If you want to add more examples or improve the library, just create a pull request with proper commit message.
