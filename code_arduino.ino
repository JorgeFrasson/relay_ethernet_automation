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
boolean estado_RL1 = false;
boolean estado_RL2 = false;

//////////////////////

void setup(){

  pinMode(RL1, OUTPUT); //pin selected to control
  pinMode(RL2, OUTPUT);
  pinMode(RL1, HIGH);
  pinMode(RL2, HIGH);
  //start Ethernet
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println("Automacao Residencial Jorge Henrique Frasson"); // so I can keep track of what is loaded
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
            digitalWrite(RL1, LOW);    // set pin 4 high
            Serial.println("On");
            estado_RL1 = true;
          }
          else{
            if(readString.indexOf("?desligar1") >0)//checks for off
            {
              digitalWrite(RL1, HIGH);    // set pin 4 low
              Serial.println("Off");
              estado_RL1 = false;
            }
          }
          
          if(readString.indexOf("?ligar2") >0)//checks for on
          {
            digitalWrite(RL2, LOW);    // set pin 4 high
            Serial.println("On");
            estado_RL2 = true;
          }
          else{
            if(readString.indexOf("?desligar2") >0)//checks for off
            {
              digitalWrite(RL2, HIGH);    // set pin 4 low
              Serial.println("Off");
              estado_RL2 = false;
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
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          client.println("<script type='text/javascript' src='https://cdn.jsdelivr.net/gh/JorgeFrasson/relay_ethernet_automation@dc7ba526cd72fb8cadb76c00c6e330d48ff626d8/my_js.js'></script>");
          client.println("<link rel='stylesheet' type='text/css' href=''>");
          client.println("</head>");
          client.println("<body>");
          client.println("<a id='rele1'><button class='botao'>rele1</button></a>");
          client.println("<a id='rele2'><button class='botao'>rele2</button></a>"); 
          if (estado_RL1){
            Serial.print(estado_RL1);
            client.println("<p id='estado1' hidden='true'>1</p>");
          }
          else {
            Serial.print(estado_RL1);
            client.println("<p id='estado1' hidden='true'>0</p>");
          }
          if (estado_RL2){
            Serial.print(estado_RL2);
            client.println("<p id='estado2' hidden='true'>1</p>");
          }
          else {
            Serial.print(estado_RL2);
            client.println("<p id='estado2' hidden='true'>0</p>");
          }
          client.println("<script>AlteraEstadoRele();</script>");
          client.println("</body>");
          client.println("</html>");

          delay(1);
          //stopping client
          client.stop();



        }
      }
    }
  }
}
