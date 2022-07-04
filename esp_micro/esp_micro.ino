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
    Serial.println("Server started");
    Serial.println(WiFi.softAPIP()); //mostra o IP pela serial - opcional
}

void loop() {
    if (!client.connected()) { //verifica a conexão com um client
        client = server.available();
    } else {
        //********INICIO DA ROTINA SERIAL - WIFI***********
//        if (Serial.available() > 0) {
//            while (Serial.available()) {                  //aguarda dados da serial
//                dcr[icd] = Serial.read(); //armazena em um vetor
//                icd++;
//            }
//            for (int j = 0; j < icd; j++) {                  //laço for para transmitir os dados para o client
//                client.print(dcr[j]); //transmite dados do vetor para o cliente
//            }
//        }
        //********INICIO DA ROTINA WIFI - SERIAL***********
        if (client.available() > 0) {
            String request = client.readStringUntil('\r');
            Serial.println(request);
            
//            while (client.available()) {                   //aguarda dados do cliente
//                data[ind] = client.read(); //armazena em um vetor
//                ind++;
//            }
            client.flush();

            delay(10);
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>table{width:100%;margin:auto;}td{border:solid black;text-align:center;background-color:black;}.botao{width: 50%;}.off{background-color: #dc1818;}.on{background-color: #4aa347;}a{display:block;font-size:200%;text-decoration:none;color:white;}</style></head>");
            client.println("<body><table class=\"table\">");
            client.println("<tr><td colspan=\"2\"><a><br><b>Micro - Lâmpada</b><br><br></a></td></tr>");
            client.println("<tr><td class=\"botao on\"><a href=\"/Cooler=ON\"><br>ON<br><br></a></td><td class=\"botao off\"><a href=\"/Cooler=OFF\"><br>OFF<br><br></a></td></tr>");
            client.println("</table></body></html>");
//            
//            for (int j = 0; j < ind; j++) {                   //laço for para transmitir os dados pela serial
//                Serial.print(data[j]); //transmite dados do vetor para a serial
//            }
        } else {
          return;
        }

        icd = 0;
        ind = 0;
    }
}
