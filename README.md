
# Conectando Wifi e alternando Leds

Esse é um projeto que pra mim foi muito divertido de construir, pois interliguei um código compilado no esp32, que cria um servidor com base no próprio IP dele e na minha rede Wifi e através desse servidor, que eu enviei um site, consigo alternar leds!


## Desafios

Acredito que meus principais desafios nesse projeto foram:
- Primeira vez utilizando o ESP(no caso o ESP32).
- Primeira vez trabalhando com as entradas do ESP.
- Primeira vez mexendo com Wifi.
- Conectando Wifi na rede local.
- Enviando informações via rede local.
## Aprendizados

Por final aprendi algumas coisas interessantes como: 
### Conectando o Esp32 ao meu Wifi

```c++
#include <WiFi.h>

const char* ssid     = "------";  // Your Network 
const char* password = "******"; // Your Network Password 

const int ledBlue = 26; // the number of the BLUE LED pin
const int ledRed = 27; // the number of the RED LED pin

WiFiServer server(80);

void setup()
{
    pinMode(ledBlue, OUTPUT); // Starting the PIN of blue led
    pinMode(ledRed, OUTPUT); // Starting the PIN of red led
    
    Serial.begin(115200);

    delay(10);

    // We start by connecting to a WiFi network

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); // Starting connection

    while (WiFi.status() != WL_CONNECTED) {
        // Loop while is connecting
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

```

### Estilizando o site
Nesse trecho eu coloquei todo o código html da pasta "Site" em uma linha e printei ela no meu "client", ou seja, meu ip.
```c++
void loop(){
    ...
        client.print("<!DOCTYPE html><html lang='pt-BR'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Leds</title></head><style>* {margin: 0;padding: 0;border: 0;font-family: sans-serif;}body {background-color: #202020;display: flex;flex-direction: column;align-items: center;justify-content: space-around;min-height: 80vh;padding: 10vh 0;}a {text-decoration: none;text-transform: uppercase;padding: 35px 50px;border: 2px solid #fff;font-size: 20px;color: #fff;transition: 0.25s;&:hover {opacity: 0.75;cursor: pointer;transition: 0.5s;}} .blue {border: 2px solid rgb(0, 15, 255);&:hover {background-color: rgb(0, 15, 255);}}.blue-active {background-color: rgb(0, 15, 255);}.red {border: 2px solid rgb(255, 15, 0);&:hover {background-color: rgb(255, 15, 0);}}.red-active {background-color: rgb(255, 15, 0);}</style><body><a class='blue' href='?led=blue'> Blue </a><a class='red' href='?led=red'> Red </a></body><script>let currentURL = window.location.href;if (currentURL.includes('blue')) {document.querySelector('.blue').classList.add('blue-active');}if (currentURL.includes('red')) {document.querySelector('.red').classList.add('red-active');}</script></html>");
    ...
}
```

### Recebendo valores da web
No trecho abaixo eu verifico se a url passa o parâmetro para o led "red"(ligando o led vermelho) ou "blue"(ligando o led azul).
```c++
void loop(){
    ...
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
    ...
}
```
# Resultado

[Ver vídeo do projeto funcionando!](https://www.youtube.com/watch?v=S7EanehuTS0)
## Autores

- [@Victor-Lis](https://github.com/Victor-Lis)

