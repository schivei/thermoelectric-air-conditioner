#include <SPI.h>
#include <WiFiNINA.h>

#include <ArduinoOTA.h>

#include "secrets.h"

#include "dimmer.h"

#include "temperature.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

bool mode;

Dimmer dimmer;

Temperature temp;

int dc;
float tempC, tempF, tempK;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  while (!Serial);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true) {
      mode = !mode;
      digitalWrite(13, mode ? HIGH : LOW);
      delay(100);
    }
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  ArduinoOTA.begin(WiFi.localIP(), ARDOTA_NAME, ARDOTA_PASS, InternalStorage);

  server.begin();

  temp.Setup();
}

void loop() {
  ArduinoOTA.poll();
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }

          dc = temp.DeviceCount();
          for(int device = 0; device < dc; device++) {
            client.print("Sensor ");
            client.print(device+1);
            client.print(" : ");
            tempC = temp.Temp(TempType::C, device);
            client.print(tempC);
            client.print((char)176);//shows degrees character
            client.print("C  |  ");
            tempF = temp.Temp(TempType::F, device);
            client.print(tempF);
            client.print((char)176);//shows degrees character
            client.println("F | ");
            tempK = temp.Temp(TempType::K, device);
            client.print(tempK);
            client.print((char)176);//shows degrees character
            client.println("K");
            client.println("<br />");
          }
          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
