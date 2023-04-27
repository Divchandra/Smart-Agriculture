#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<SoftwareSerial.h>

SoftwareSerial mySerial (D1 ,D2);

/*Put your SSID & Password*/
const char* ssid = "Harsh";  // Enter SSID here
const char* password = "12121212";  //Enter Password here
String temp,hum,soil;
String str;
int pump;
ESP8266WebServer server(80);
double counter = 0;
uint8_t LED1pin = D7;
bool LED1status = LOW;

uint8_t LED2pin = D6;
bool LED2status = LOW;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
 
  pump = 10;
  delay(100);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {


str = mySerial.readString();

Serial.println(str);

Serial.println("next");
server.send(200, "text/html", SendHTML(LED1status,LED2status,temp,hum,soil)); 
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}

}














void handle_OnConnect() {
  LED1status = LOW;
  
  LED2status = LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,temp,hum,soil)); 
}

void handle_led1on() {
  LED1status = HIGH;
pump = 10;
 mySerial.write((byte *)&pump, sizeof(pump)); // Send the integer value over serial
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status,temp,hum,soil)); 
}

void handle_led1off() {
  LED1status = LOW;
pump = 10;
 mySerial.write((byte *)&pump, sizeof(pump)); // Send the integer value over serial
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status,temp,hum,soil)); 
}

void handle_led2on() {
  LED2status = HIGH;
 
  Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true,temp,hum,soil)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false,temp,hum,soil)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat,String t1,String h1,String s1){

  String ptr = "<!DOCTYPE html> <html>\n";

  ptr +="<head> \n";
  ptr +="<meta name = \"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\n";
  ptr +="<title>LED Control</title> \n";
  ptr +="<style> \n";
  ptr +="html { font-family: Century Gothic; display: inline-block; margin: 0px auto; text-align: center;background-image: url(https://thumbs.dreamstime.com/b/vector-light-grey-succulent-plant-texture-drawing-seamless-pattern-background-great-subtle-botanical-modern-backgrounds-fabric-90904464.jpg) ;} \n";
  ptr +="body{margin-top: 50px;}  \n";
  ptr +="h1 {color: #444444;margin: 50px auto 30px;}  \n";
  ptr +="h3 {color: #444444;margin-bottom: 50px;} \n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;} \n";
  ptr +=".button-on {background-color: #1abc9c;} \n";
  ptr +=".button-on:active {background-color: #16a085;} \n";
  ptr +=".button-off {background-color: #34495e;} \n";
  ptr +=".button-off:active {background-color: #2c3e50;} \n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;} \n";
  ptr +=".cards {margin-top: 15px;display: flex;justify-content: space-around;clear: both;} \n";
  ptr +=".card {text-align: center;padding: 10px;display: flex;border-bottom: 2px solid rgb(255, 255, 255);flex-direction: column;border-radius: 5%;margin: 10px;height: 15rem;width: 20rem;} \n";
  ptr +="#c1 {background-image: radial-gradient(#cef0c8, #a7f6ab);float: left;width: 25%;} \n";
  ptr +="#c2 {background-image: radial-gradient(#bcd8e3, #9bbff2);float: left;width: 25%;} \n";
  ptr +="#c3 {background-image: radial-gradient(#f1d0c6, #f8a890);float: left;width: 25%;} \n";
  ptr +="#c4 {background-image: radial-gradient(#f7def3, #f7a6f4);float: left;width: 25%;} \n";
  ptr +=".card__heading {border-bottom: 2px solid black;text-align: center;color: #ffffff;font-family: \"Garamond\", sans-serif;} \n";
  ptr +=".card p {margin: auto;color: white;font-family: \"Bree Serif\", serif;font-size: 15px;} \n";
  ptr +="</style></head><body> \n";
  ptr +="<h1>ESP8266 Web Server</h1><h3> Control Page </h3> \n";

if(led1stat)
  {ptr +="<p>Pump Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>Pump Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

ptr +="</p> \n";
ptr +="<div className=\"cards\"> \n";
ptr +="<div className=\"card\" id=\"c1\" ><div className=\"card__heading\"><h3>Temperature</h3></div><p>t1 C</p></div> \n";
ptr +="<div className=\"card\" id=\"c2\"><div className=\"card__heading\"><h3>Humidity</h3></div><p>t1 mm</p></div> \n";
ptr +="<div className=\"card\" id=\"c3\"><div className=\"card__heading\"><h3>Soil Moisture</h3></div><p>t1 mm</p></div> \n";
ptr +="<div className=\"card\" id=\"c4\"><div className=\"card__heading\"><h3>Location</h3></div><p>t1 degree</p></div> \n";
ptr +="</div> \n";

ptr +="</body> </html> \n";
  return ptr;
}