/*
* Foondi_Works.ino
*
* Created: 8/27/2016 11:42:17
* Author: Kennedy
*/
//int button = 2;
//int led1 = 11;
//int led2 = 12;
//int button_status = HIGH;
//float light = 0;
//int ldr = A0;
//
//
//void setup()
//{
//
//	/* add setup code here, setup code runs once when the processor starts */
//	pinMode(led1, OUTPUT);
//	pinMode(led2, OUTPUT);
//	pinMode(button, INPUT);
//	Serial.begin(9600);
//
//}
//
//void loop()
//{
//
//	/* add main program code here, this code starts again each time it ends */
//	light = analogRead(ldr);
//	Serial.print("Light Intensity: ");
//	int  buttonR = digitalRead(button);
//	Serial.println(buttonR);
//	Serial.println(light);
//
//	delay(500);
//	digitalWrite(led2, HIGH);
//	button_status = digitalRead(button);
//
//	if (button_status == LOW)
//	{
//		digitalWrite(led1, HIGH);
//	}
//	else
//	{
//		digitalWrite(led1, LOW);
//	}
//
//
//}
#include "DHT.h"
#include <Servo.h>

int button = 2;
int btn_state= HIGH;
int buzzer = 4;
int ldr = A0;
float lightInt = 0;

#define DHTPIN 3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Servo servo1;  
int pos = 0;    

void setup() {
	servo1.attach(9);  // attaches the servo on pin 9 to the servo object
	pinMode(button, INPUT);
	pinMode(buzzer, OUTPUT);
	digitalWrite(buzzer, LOW);
	pinMode(ldr, INPUT);
	attachInterrupt(digitalPinToInterrupt(button), openDoor, OUTPUT);


	Serial.begin(9600);
	Serial.println("TEMP HUMIDITY AND LIGHT SENSOR");

	dht.begin();
}

void loop() {

	//openDoor();


	Serial.println("DATA: \tLIGHT \tTEMP \tHUMIDITY");
	delay(2000);

	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	float f = dht.readTemperature(true);

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}
	lightInt = analogRead(ldr);
	Serial.print("\t");
	Serial.print(lightInt);
	Serial.print("\t");
	Serial.print(t);
	Serial.print("\t");
	Serial.print(h);
	Serial.print("%");
	Serial.println();

	if (t > 25)
	
	Serial.println("It's Really Hot");
	
	if (t < 20) 
		Serial.println("Feels Cold");
		
	
	if (t >= 20 | t <= 25) 
		Serial.println("Things Look Cool");

	
}
void openDoor()
{
	btn_state = digitalRead(button);
	if (btn_state == LOW)
	{
		Serial.println();
		Serial.println("Opening Door");
		for (int servoPos = 0; servoPos < 180; servoPos++)
		{
			servo1.write(servoPos);
			delay(10);
			digitalWrite(buzzer, HIGH);
			delay(5);
			digitalWrite(buzzer, LOW);
		}

	}
}

