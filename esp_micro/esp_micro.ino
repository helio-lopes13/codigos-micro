#include <ESP8266WiFi.h>
const char *ssid = "Helio";       //o esp8266 cria esta rede wifi, não é a rede do roteador local
const char *password = "helio321"; //senha para acessar a rede
WiFiServer server(80);           //define a porta 80 para comunicação
char data[250], dcr[250];       //variáveis para armazenar o caracteres da transmissão/recepção
int ind = 0, icd = 0;
WiFiClient client;

void setup() {
    Serial.begin(9600);            //taxa de transmissão
    IPAddress staticIP(192, 168, 4, 2); // IP estático do dispositivo
    IPAddress gateway(192, 168, 4, 1);  // Endereço gateway IP
    IPAddress subnet(255, 255, 255, 0); // Máscara de subrede
    WiFi.mode(WIFI_AP);            // Trabalhando como Access Point
    WiFi.softAP(ssid, password, 2, 0);
    WiFi.config(staticIP, gateway, subnet);
    server.begin();
    delay(5000);
}

void loop() {
    client = server.available();
    if (!client) { //verifica se o client existe
      return;
    }

    while (!client.available()) {
      delay(1);
    }

    String request = client.readStringUntil('\r');
    client.flush();

    delay(10);

    if (request.indexOf("ON") != -1) {
      Serial.println("L\r");
    } else if (request.indexOf("OFF") != -1) {
      Serial.println("D\r");
    }
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>table{width:100%;margin:auto;}td{border:solid black;text-align:center;background-color:black;}.botao{width: 50%;}.off{background-color: #dc1818;}.on{background-color: #4aa347;}a{display:block;font-size:200%;text-decoration:none;color:white;}</style></head>");
    client.println("<body><table class=\"table\">");
    client.println("<tr><td colspan=\"2\"><a><br><b>Micro - Lâmpada</b><br><br></a></td></tr>");
    client.println("<tr><td class=\"botao on\"><a href=\"/lampada=ON\"><br>ON<br><br></a></td><td class=\"botao off\"><a href=\"/lampada=OFF\"><br>OFF<br><br></a></td></tr>");
    client.println("</table></body></html>");
}
