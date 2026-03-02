#include "max6675.h"


//Thermocouple Declaration
int thermoSO = 12;
int thermoCLK = 13;

int thermoCS_upper = 2;
int thermoCS_mid = 4;
int thermoCS_low = 7;

MAX6675 thermocouple_low(thermoCLK, thermoCS_upper, thermoSO);
MAX6675 thermocouple_low(thermoCLK, thermoCS_mid, thermoSO);
MAX6675 thermocouple_low(thermoCLK, thermoCS_low, thermoSO);

float temp_upper;
float temp_mid;
float temp_low;

int load_upper = 3;
int load_mid = 5;
int load_low = 6;

//PID Setup
float minTemp = 72; //Room temperature
float target = 95; //Degrees Fahrenheit 

float error_upper;
float error_mid;
float error_low;

float output_upper;
float output_mid;
float output_low;

//constants
float k_p = 255/(target-minTemp); 
// float k_i;
// float k_d;


void setup() {
  Serial.begin(9600);
  delay(500);   // wait for MAX chip to stabilize

  
  pinMode(load_upper, OUTPUT);
  pinMode(load_mid, OUTPUT);
  pinMode(load_low, OUTPUT);
}

void loop() {
    analogWrite(load_upper, 50); 
    analogWrite(load_mid, 50); 
    analogWrite(load_low, 50); 


  //Testing 
  Serial.print("F = ");
  Serial.println(thermocouple_low.readFahrenheit());
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




//MIDDLE REGION
  temp_mid = thermocouple_mid.readFahrenheit();
  error_mid = (target-temp_mid); //Calculate temperature difference
  

  if(error_mid > (target - minTemp)) { //If the temperature is lower than minTemp, output the maximum power
    output_mid = 255;
  }
  else if(error_mid >= 0) {
    output_mid = error_mid*k_p ; //Translate temperature error to output voltage
  }
  else {
    output_mid = 0;
  }



//UPPER REGION
  temp_upper = thermocouple_mid.readFahrenheit();
  error_upper = (target-temp_upper); //Calculate temperature difference
  

  if(error_upper > (target - minTemp)) { //If the temperature is lower than minTemp, output the maximum power
    output_upper = 255;
  }
  else if(error_upper >= 0) {
    output_upper = error_upper*k_p ; //Translate temperature error to output voltage
  }
  else {
    output_upper = 0;
  }


  delay(250); //For the MAX6675 to update, delay AT LEAST 250ms between reads
}
