#include <Wire.h>
#include "MAX30105.h"
#include <SoftwareSerial.h>
SoftwareSerial myserial(5,6); //tx=5, rx=6
MAX30105 particleSensor;
int heartrate=0;

#include <Adafruit_MLX90614.h>
//#include <Adafruit_MLX_Sensor90614.h>
char *Object_Type[]={"Object","Ambient"};

Adafruit_MLX90614 MLX_Sensor = Adafruit_MLX90614();

void setup() {
  Serial.println("MLX90614 Sensor MicroLab");  
  MLX_Sensor.begin();  
  Serial.begin(9600);
  myserial.begin(9600);
  myserial.write("Hello in Bluetooth");
  // Initialize sensor
  if (particleSensor.begin() == false) {
    Serial.println("MAX30102 was not found. Please check wiring/power.");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive
  
}

void loop() {
  
  Serial.print(" R[");//print no
  Serial.print(particleSensor.getRed());
  Serial.print("] IR[");
  Serial.print(particleSensor.getIR());
  Serial.println("]");
  Serial.print("heartrate=");
   heartrate =particleSensor.getRed()-particleSensor.getIR();
   heartrate=heartrate*0.0030357;
   Serial.println(heartrate);
  delay(100);
  if (myserial.available())
 {

  if (myserial.read() == '1' )
  {myserial.write("heartrate=");
  myserial.write((heartrate));}
  }
  Display_Temperature('A'); //Get Object temperature in Celsius
  Display_Temperature('B'); //Get Ambient temperature in Celsius
  
  Display_Temperature('C'); //Get Object temperature in Keliven
  Display_Temperature('D'); //Get Ambient temperature in Keliven

  
  Display_Temperature('E'); //Get Object temperature in Fahrenheit
  Display_Temperature('F'); //Get Ambient temperature in Fahrenheit
  Serial.println("########");

  delay(2000);

}



float Get_Temperature_Sample(char type)
{
    float temp_value;
    float Object_Temperature = MLX_Sensor.readObjectTempC();
    float Ambient_Temperature = MLX_Sensor.readAmbientTempC();
   if(type =='E')
   {
    temp_value = MLX_Sensor.readObjectTempF(); //Fah. Object
   }else if(type =='F')
   {
    temp_value = MLX_Sensor.readAmbientTempF();//Fah Ambient
   }else if(type =='C')
   {
    temp_value = Object_Temperature + 273.15;// Object Kelvin
   }else if(type =='D')
   {
    temp_value = Ambient_Temperature + 273.15;//Ambient Kelvin
   }else if(type =='A')
   {
    temp_value = Object_Temperature;
   }else if(type =='B')
   {
    temp_value = Ambient_Temperature;
   }
   return temp_value;
 
}

void Display_Temperature(char type)
{
  float temp_data =Get_Temperature_Sample(type);

  if(type =='A')
  {
    Serial.print(Object_Type[0]);
    Serial.print(" ");    
    Serial.print(temp_data);
    Serial.print("°");      
    Serial.println("C");
  }else if(type =='B')
  {
    Serial.print(Object_Type[1]);
    Serial.print(" ");     
    Serial.print(temp_data);
    Serial.print("°");      
    Serial.println("C");
  }else if(type =='C')
  {
    Serial.print(Object_Type[0]);
    Serial.print(" ");     
    Serial.print(temp_data);
    Serial.print("°");      
    Serial.println("F");
  }else if(type =='D')
  {
    Serial.print(Object_Type[1]);
    Serial.print(" ");     
    Serial.print(temp_data);
    Serial.print("°");      
    Serial.println("F");
  }

  else if(type =='E')
  {
    Serial.print(Object_Type[0]);
    Serial.print(" ");     
    Serial.print(temp_data);  
    Serial.print("°");       
    Serial.println(" K");
  }  
  else if(type =='F')
  {
    Serial.print(Object_Type[1]);
    Serial.print(" ");     
    Serial.print(temp_data);  
    Serial.print("°");       
    Serial.println(" K");
  }

}
