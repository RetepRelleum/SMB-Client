

#include <SMB.h>
#include <Debug.h>
#include <SPI.h>
#include <Arduino.h>
#include <WiFi101.h>
#include "arduino_secrets.h"



int keyIndex = 0;            // your network key Index number (needed only for WEP)

WiFiClient client;
SMB smb(&client);
int status = WL_IDLE_STATUS;
void printWiFiStatus() {
        // print the SSID of the network you're attached to:
        debug_print("SSID: ");
        debug_println(WiFi.SSID());

        // print your WiFi shield's IP address:
        IPAddress ip = WiFi.localIP();
        debug_print("IP Address: ");
        debug_println(ip);

        // print the received signal strength:
        long rssi = WiFi.RSSI();
        debug_print("signal strength (RSSI):");
        debug_print(rssi);
        debug_println(" dBm");
}

void setup() {
        Serial.begin(115200);
        while (!Serial) {
                ; // wait for serial port to connect. Needed for native USB port only
        }

        // check for the presence of the shield:
        if (WiFi.status() == WL_NO_SHIELD) {
                debug_println("WiFi shield not present");
                // don't continue:
                while (true);
        }


        // attempt to connect to WiFi network:
        while (status != WL_CONNECTED) {
                debug_print("Attempting to connect to SSID: ");
                debug_println(ssid);
                // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
                status = WiFi.begin(ssid, pass);

                // wait 10 seconds for connection:
                while (WiFi.status()!=WL_CONNECTED) {
                        delay(10);
                }
        }
        debug_println("Connected to wifi");
        printWiFiStatus();

        String path="\\\\internetbox-nas.home\\usb disk";

        String name="Testwwww\\aa";
        smb.begin(path,"","");
        SMBFile f=smb.open(name,FILE_READ);
        SMBFile f2(&client);
        while (true) {
                f2=f.openNextFile();
                Serial.print("name: ");
                Serial.print(f2.name());
                Serial.print(" Size: ");
                Serial.println(f2.size());
                if (!f2) {
                        Serial.println("break");
                        break;
                }
                f2.close();
        }
        f.rewindDirectory();
        while (true) {
                f2=f.openNextFile();
                Serial.print("name: ");
                Serial.print(f2.name());
                Serial.print(" Size: ");
                Serial.println(f2.size());
                if (!f2) {
                        Serial.println("break");
                        break;
                }
                f2.close();
        }
        Serial.print("end: ");


        smb.loggOff();
}


void loop() {
        delay(100);

}
