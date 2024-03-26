//#include <data.h> hay que crear la libreria data para poder meter ahí la página web a mostrarle al cliente
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiManager.h>
WebServer server(443); //80
//http = 80, https = 443
//ws = 80, wss =443 (ws = web socket, conexión bilateral)

const char* ssid = "RobotInicial-00XX";
const char* password = "Futhurtech";
const byte ledPin = 19;
const byte relayPin = 5;
bool releState = false;
bool Estado = false;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(releState, HIGH);
  delay(100);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  if (!MDNS.begin("Robotinicial00XX")) {
    Serial.println("Error configurando mDNS!");
    while(1) {
      delay(1000);
    }
  }
  Serial.println("mDNS configurado");

  //estos eventos son los que van a manejar las peticiones del cliente, tener en cuenta para manejar los eventos onClick de la pagina web botonera
  //las funciones handle utilizadas como parametros acá no llevan las () de cierre solo se las llama sin mas.
  //la forma de iniciar la peticion del cliente es con "/peticion" la/peticion viene del html, esa peticion se pasa como primer parametro y el segundo parametro es el encargado de enviar la respuesta
  server.on("/", handleConnectionRoot);
  server.on("/relayOn", handleRelayOn);
  server.on("/relayOff", handleRelayOff);
  server.on("/", inicio);
  server.onNotFound(handleNotFound);
  


  server.begin();
  MDNS.addService("HTTP", "TCP", 443); //80
  Serial.println("Servidor HTTP iniciado");
  delay(150);
}

void loop() {
  server.handleClient();
  /*if (releState) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(relayPin, LOW);
  }
  else {
    digitalWrite(LedPin,LOW);
    digitalWrite(relayPin,HIGH);
  } */
}


//La respuesta en html
String answer = "";


void inicio() {
  /*Verifica si se recibió el comando inicio
  server.hasArg("inicio") verifica si el servidor tiene un argumento llamado "inicio". La función hasArg() devolverá true si el argumento está presente y false si no lo está.
  server.arg("inicio") == "push" verifica si el valor del argumento "inicio" es igual al string "push". La función arg() se utiliza para obtener el valor del argumento "inicio", si el valor 
  del argumento es igual a "push", la condición se considera verdadera y se ejecutará el bloque de código dentro. 
  */
  //hay dos opciones a encarar hacer todo en una misma funcion con varios if, else if o en su defecto con switch case, o encarar con distintas funciones una para cada acción,
  //eso se va a resolver al momento de integrar todo el código y ver cual de las opciones es mas acorde y se ajusta a las necesidades y problemas que surjan.
  if (server.hasArg("inicio") && server.arg("inicio") == "push") {
    //realizar la acción de presionar boton inicio, o en su defecto sumar la órden inicio
  }
  else if (server.hasArg("adelante") && server.arg("adelante") == "push") {
    //sumar la órden x
  }
}

//responder a la url raíz (root /)
void handleConnectionRoot() {
  server.send(200, "text/html", answer);
}

void handleRelayOn() {
  //releState = true;
  server.send(200, "text/html", answer);
}

void handleRelayOff() {
  //releState = false;
  server.send(200, "text/html", answer);
}

void handleNotFound() {
  server.send(404, "text/plain", "<h1>Error Not Found</h1>");
}

//Esta funcion gestiona el metodo get de la página web (el evento javascript) desde el lado esp32
void verificarMensaje(String answer) {
  if (answer.indexOf("GET /inicio") >= 0) {
    Serial.println("Estopy listo para recibir órdenes");
    Estado = true;
  }
  else if (answer.indexOf("GET /go") >= 0) {
    Serial.println("Allá voy!");
    Estado = false;
  }
}



















