#include <DHT.h>
#include <DHT_U.h>


#include <SoftwareSerial.h>
#define DHTPIN 31
#define LED 11
#define LED2 10
#define SOIL A7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
String str;

int val;
SoftwareSerial mySerial(2, 3); 
int relay = 11;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
dht.begin();
delay(2000);
pinMode(LED, OUTPUT);  
 pinMode(relay, OUTPUT);
pinMode(A7,INPUT); 
pinMode(LED2, INPUT);  
digitalWrite(LED, HIGH);  
}

void loop() {
  // put your main code here, to run repeatedly:

delay(500);

float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
Serial.print("H: ");
Serial.print(h); 

Serial.print(" T: ");
Serial.print(t); 
Serial.print("C\n");
	int val = analogRead(SOIL); 
Serial.println(val);

char buffer1[32];
dtostrf(t,5,2,buffer1);
for(int i =0;i<32;i++)
delay(100);
String b1 = String(buffer1);
b1 = "*"+ b1;
b1 = b1+ "*";
b1.toCharArray(buffer1, sizeof(buffer1));
mySerial.write(buffer1);
Serial.println("");

char buffer2[32];
dtostrf(h,5,2,buffer2);
for(int i =0;i<32;i++)
delay(100);
String b2 = String(buffer2);
b2 = "_"+ b2;
b2 = b2+ "_";
b2.toCharArray(buffer2, sizeof(buffer2));
mySerial.write(buffer2);
Serial.println("");

char buffer3[32];
dtostrf(val,5,2,buffer3);
for(int i =0;i<32;i++)
delay(100);
String b3 = String(buffer3);
b3 = "-"+ b3;
b3 = b3+ "-";
b3.toCharArray(buffer3, sizeof(buffer3));
mySerial.write(buffer3);
Serial.println("");
int p ;
p = digitalRead(LED2);
Serial.println(p);

 
delay(1000);
if(p==1)
{
     digitalWrite(relay, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);    
}
else
{
     digitalWrite(relay, HIGH);    // turn the LED off by making the voltage LOW
  delay(2000);    
}

}








