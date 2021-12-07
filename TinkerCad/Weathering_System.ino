String ssid     = "Simulator Wifi"; 
String password = ""; 
String host     = "api.thingspeak.com"; 
const int httpPort   = 80;
String url      = "/update?api_key=ILU77UNCMQXCUZ3X&field1=";


int setupESP8266(void) {
  Serial.begin(115200);   
  Serial.println("AT");   
  delay(10);        
  if (!Serial.find("OK")) return 1;
    
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        
  if (!Serial.find("OK")) return 2;
  
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void anydata(void) {
  //Temprature
  float temp = map(analogRead(A0),20,358,-40,125);
  //PMT
  int a = analogRead(A2);
  int b = map(a,0,1023,0,255);
  //Atmospheric pressure
  float force = analogRead(A1);
  float press = force/100;
  //Light Sensor
  int light = map(analogRead(A3),0,1023,0,255);
  //Humidity Sensor
  int humid = map(analogRead(A4),0,1023,10,70);
  Serial.println(humid);
  
  String httpPacket = "GET " + url + String(temp) 
    +"&field2="+ String(b) 
    +"&field3="+ String(press) 
    +"&field4="+ String(light)
    +"&field5="+ String(humid)
    + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  //Serial.println(length2);
  
  delay(10); 
  Serial.print(httpPacket);
  delay(10);
  if (!Serial.find("SEND OK\r\n")) return;
  
  
}


void setup() {
  
  setupESP8266();
               
}

void loop() {
  
 anydata();
  
  delay(4000);
}
