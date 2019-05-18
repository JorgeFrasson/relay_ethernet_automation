#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x09, 0xA7 }; //physical mac address
byte ip[] = { 192, 168, 0, 99 }; // ip in lan
byte gateway[] = { 192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

int RL1 = 9;
int RL2 = 7;
boolean estado_RL1 = true;
boolean estado_RL2 = true;

//////////////////////

void setup(){

  pinMode(RL1, OUTPUT); //pin selected to control
  pinMode(RL2, OUTPUT);
  //start Ethernet
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println("RoboCore Remote Automation V1.1"); // so I can keep track of what is loaded
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          //Serial.print(c);
        }

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////////// control arduino pin
          Serial.println(readString); //print to serial monitor for debuging
          if(readString.indexOf("?ligar1") >0)//checks for on
          {
            digitalWrite(RL1, HIGH);    // set pin 4 high
            Serial.println("On");
            estado_RL1 = false;
          }
          else{
            if(readString.indexOf("?desligar1") >0)//checks for off
            {
              digitalWrite(RL1, LOW);    // set pin 4 low
              Serial.println("Off");
              estado_RL1 = true;
            }
          }
          
          if(readString.indexOf("?ligar2") >0)//checks for on
          {
            digitalWrite(RL2, HIGH);    // set pin 4 high
            Serial.println("On");
            estado_RL2 = false;
          }
          else{
            if(readString.indexOf("?desligar2") >0)//checks for off
            {
              digitalWrite(RL2, LOW);    // set pin 4 low
              Serial.println("Off");
              estado_RL2 = true;
            }
          }
          //clearing string for next read
          readString="";


          ///////////////

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<html>");
          client.println("<head>");
          client.println("<title>RoboCore - Remote Automation</title>");
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          client.println("<link rel='stylesheet' type='text/css' href='http://www.robocore.net/upload/projetos/RemoteAutomationV1.0.css' />");
          client.println("<script type='text/javascript' src='I:\\Meus Documentos\\Desktop\\automacao_ethernet'></script>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div id='wrapper'>RoboCore Remote Automation V1.1");
          client.print("<div id='rele'></div><div id='estado1' style='visibility: hidden;'>");
          client.print("<div id='rele'></div><div id='estado2' style='visibility: hidden;'>");
          client.print(estado_RL1);
          client.print(estado_RL1);
          client.println("</div>");
          client.println("<div id='botao1' class='botao'></div>");
          client.println("</div>");
          client.println("</div>");
          client.println("<div id='botao2' class='botao'></div>");
          client.println("</div>");
          client.println("<script>AlteraEstadoRele()</script>");
          client.println("</body>");
          client.println("</head>");

          delay(1);
          //stopping client
          client.stop();



        }
      }
    }
  }
}
