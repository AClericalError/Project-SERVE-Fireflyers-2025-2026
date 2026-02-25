#include "max6675.h"


//Thermocouple Declaration
int thermoDO = 12;
int thermoCLK = 13;

int thermoCS_low = 2;
// int thermoCS_mid = 3;
// int thermoCS_up = 4;

MAX6675 thermocouple_low(thermoCLK, thermoCS_low, thermoDO);
// MAX6675 thermocouple_low(thermoCLK, thermoCS_mid, thermoDO);
// MAX6675 thermocouple_low(thermoCLK, thermoCS_up, thermoDO);

float temp_low;
// float temp_mid;
// float temp_up;

//MOSFET Declaration
int gate_low = 5;

//Relay
int relay = 7;

//PID Setup
float minTemp = 72; //Room temperature
float target = 95; //Degrees Fahrenheit 
float error_low;
float error_mid;
float error_up;

float output_low;

//constants
float k_p = 255/(target-minTemp); 
float k_i;
float k_d;


void setup() {
  Serial.begin(9600);
  delay(500);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
  

  pinMode(relay, OUTPUT);

  pinMode(gate_low, OUTPUT);
}

void loop() {

    digitalWrite(relay, LOW); //Turn on relay
    
  //Testing 
  Serial.print("F = ");
  Serial.println(thermocouple_low.readFahrenheit());
  //  Serial.print("Error = ");
  // Serial.println(error_low);
  Serial.print("Current output = ");
  Serial.println(output_low);
  
 //LOWER REGION
  temp_low = thermocouple_low.readFahrenheit();
  error_low = (target-temp_low); //Calculate temperature difference
  

  if(error_low > (target - minTemp)) { //If the temperature is lower than minTemp, output the maximum power
    output_low = 255;
  }
  else if(error_low >= 0) {
    output_low = error_low*k_p ; //Translate temperature error to output voltage
  }
  else {
    output_low = 0;
  }

  
  analogWrite(gate_low, output_low);



//MIDDLE REGION

//UPPER REGION



  delay(250); //For the MAX6675 to update, delay AT LEAST 250ms between reads
}
