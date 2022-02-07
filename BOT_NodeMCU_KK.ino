#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
//RX Pin GPIO-14/D5
//TX Pin GPIO-12/D6
SoftwareSerial mSerial(14, 12);
#define Bot_Name "_I"
//======================================WIFI CREDENTIALS for Hotspot==================================
//const char* ssid = "Pinwheel";
//const char* pwd = "magentalight";

//const char* ssid = "Honor 9N";
//const char* pwd = "kittu0165";

const char* ssid = "JBR POS";
const char* pwd = "6262848492";
//====================================================================================================
String URL;
int httpCode;
String payload;
String ID;
String state;


//====================================================================================================
String k;
//=============================================define the objects======================================
ESP8266WebServer server(80);
HTTPClient http;
//=========================================SETUP PART==================================================
void setup() {
  Serial.begin(115200);
  mSerial.begin(115200);
  WiFi.disconnect();
  pinMode(5, OUTPUT); //Pin D1 on NodeMCU
  pinMode(4, OUTPUT);  //Pin D2 on NodeMCU
  Serial.print("Connecting to WIFI:");
  WiFi.begin( ssid, pwd);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("I am Connected, ");
  Serial.print("My Local IP is : ");
  Serial.println((WiFi.localIP()));
  digitalWrite(5, 1);    //LED on pin D1 of node MCU turns on
  
  server.on("/", handleroot);
  server.on("/M", Pause);
  server.on("/L", Resume);
  server.on("/ispinwheel", Handshake);
  server.on("/TurnOn", Connected);
  server.on("/TurnOff", Disconnected);
  server.on("/Battery", Battery);
  server.on("/Next", Next);
  server.on("/Reset", Reset);
  server.on("/Home", Home);
  server.on("/Stop", Stop);
  server.on("/T1", T1);
  server.on("/T2", T2);
  server.on("/T3", T3);
  server.on("/T4", T4);
  server.on("/T5", T5);
  server.on("/T6", T6);
  server.begin();
}
//=====================================handle root page================================================
void handleroot() {
  server.send(200, "text/plain", "Welcome TO @JUST BLR");
}
//===================================AutoBot control page===========================================
void Handshake()
{
 server.send(200, "text/plain", String("yes")+String(Bot_Name));
  Serial.println("yes");
}
void Connected()
{
  digitalWrite(4, 1); 
  Serial.println("Connected");
}
void Disconnected()
{
  digitalWrite(4, 0); 
  Serial.println("Disconnected");
}
void Pause() {
  server.send(200, "text/plain", "Pause");
  mSerial.println("P");
  Serial.println("P");
}
void Resume() {
  server.send(200, "text/plain", "Resume");
  mSerial.println("T");
  Serial.println("T");
}
void Next() {
  server.send(200, "text/plain", "Next");
  mSerial.println("N");
  Serial.println("N");
}
void Reset() {
  server.send(200, "text/plain", "Reset");
  mSerial.println("R");
  Serial.println("R");
}
void Home() {
  server.send(200, "text/plain", "Home");
  mSerial.println("H");
  Serial.println("H");
}
void Stop() {
  server.send(200, "text/plain", "Stop");
  mSerial.println("S");
  Serial.println("S");
}

void T1() {
  server.send(200, "text/plain", "T1");
  mSerial.println("K");
  Serial.println("K");
}
void T2() {
  server.send(200, "text/plain", "T2");
  mSerial.println("V");
  Serial.println("V");
}
void T3() {
  server.send(200, "text/plain", "T3");
  mSerial.println("W");
  Serial.println("W");
}
void T4() {
  server.send(200, "text/plain", "T4");
  mSerial.println("X");
  Serial.println("X");
}
void T5() {
  server.send(200, "text/plain", "T5");
  mSerial.println("Y");
  Serial.println("Y");
}
void T6() {
  server.send(200, "text/plain", "T6");
  mSerial.println("Z");
  Serial.println("Z");
}
void Battery() {
  mSerial.println("B");
  Serial.println("B");
  k = "";
  while (mSerial.available()) {
    char c = mSerial.read();
    k += c;
  }
  server.send(200, "text/plain", String(k));
  
}
//==============================================LOOP===================================================

void loop () 
{

  server.handleClient();
//k = "";
  //if (mSerial.available()) {
    //String myString = String(mSerial.read());
//server.send(200, "text/plain",myString);
//}

}
