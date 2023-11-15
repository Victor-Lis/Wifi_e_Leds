#include <WiFi.h>

const char* ssid     = "Oalis";
const char* password = "oalis636807";

const int ledBlue =  26;      // the number of the LED pin
const int ledRed =  27;      // the number of the LED pin

WiFiServer server(80);

void setup()
{
    pinMode(ledBlue, OUTPUT);
    pinMode(ledRed, OUTPUT);
    
    Serial.begin(115200);

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<!DOCTYPE html><html lang='pt-BR'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Leds</title></head><style>* {margin: 0;padding: 0;border: 0;font-family: sans-serif;}body {background-color: #202020;display: flex;flex-direction: column;align-items: center;justify-content: space-around;min-height: 80vh;padding: 10vh 0;}a {text-decoration: none;text-transform: uppercase;padding: 35px 50px;border: 2px solid #fff;font-size: 20px;color: #fff;transition: 0.25s;&:hover {opacity: 0.75;cursor: pointer;transition: 0.5s;}} .blue {border: 2px solid rgb(0, 15, 255);&:hover {background-color: rgb(0, 15, 255);}}.blue-active {background-color: rgb(0, 15, 255);}.red {border: 2px solid rgb(255, 15, 0);&:hover {background-color: rgb(255, 15, 0);}}.red-active {background-color: rgb(255, 15, 0);}</style><body><a class='blue' href='?led=blue'> Blue </a><a class='red' href='?led=red'> Red </a></body><script>let currentURL = window.location.href;if (currentURL.includes('blue')) {document.querySelector('.blue').classList.add('blue-active');}if (currentURL.includes('red')) {document.querySelector('.red').classList.add('red-active');}</script></html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        Serial.println(currentLine.endsWith("GET"));
        if (currentLine.endsWith("GET /?led=blue")) {
          Serial.println("Blue");
          digitalWrite(ledBlue, HIGH);   
          digitalWrite(ledRed, LOW);   
        }
        if (currentLine.endsWith("GET /?led=red")) {
          Serial.println("Red");
          digitalWrite(ledBlue, LOW);   
          digitalWrite(ledRed, HIGH);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
