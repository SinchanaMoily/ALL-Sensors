#define BLYNK_TEMPLATE_ID "TMPL3mFxZbwRS"
#define BLYNK_TEMPLATE_NAME "led"
#define BLYNK_AUTH_TOKEN "2BrwykMa-i9iOZMbG0ohZxhm5bE6Zk4d"
#define BLYNK_PRINT Serial
#include<WiFi.h>
#include<BlynkSimpleEsp32.h>

char auth[] = "2BrwykMa-i9iOZMbG0ohZxhm5bE6Zk4d";
char ssid[] = "workspace6";
char pass[] = "passcode6";

BLYNK_WRITE(V0){
  int pinvalue=param.asInt();
  digitalWrite(5,pinvalue);
}
void setup() {
 Serial.begin(9600);
 pinMode(5,OUTPUT);
 WiFi.begin(ssid,pass);
 while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.println("Not connected");
 }
 Serial.println("Connected");
 Blynk.begin(auth,ssid,pass);

}

void loop() {
  Blynk.run();
}