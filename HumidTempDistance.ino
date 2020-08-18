/*
 Name:		HumidTempDistance.ino
 Created:	8/17/2020 6:41:47 PM
 Author:	lelin

 * Testing Sensors :
	 * Vcc - 5v pin in arudino
	 * GND - GND pin in arudino
	 * Common power source to bread board
	 *
	 * Sensor 1 : DHT11 - Temperature Humidity Sensor
	 * Data Pin - A0
	 *
	 * Sensor 2 : HC-SR04 - Ultrasonic Distance Sensor
	 * Trigger Pin - 13
	 * Echo Pin - 12
	 * Led - 7 for notification
	 * Buzzer - 6 for Warning
 */

#include <DHT_U.h>

//Initializing DHT Temp-Humidity Sensor
#define DHTPIN A0
#define DHTTYPE DHT11


//Initializing Ultrasonic Distance Sensor
const int triggerPin = 12;
const int echoPin = 13;
const int led = 7;
const int buz = 6;

// Initialize DHT sensor with Pin
DHT dht(DHTPIN, DHTTYPE, A0);

// the setup function runs once when you press reset or power the board
void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	// Init DHT
	dht.begin();
	//Init HC-SR04
	pinMode(led, OUTPUT);
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(buz, OUTPUT);
	//delay(500);

}

void loop() {
	// put your main code here, to run repeatedly:
	long duration, inches, cm;
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);

	Serial.print("Current Humidity = ");
	Serial.print(dht.readHumidity());
	Serial.print("% ; ");
	Serial.print("Current Temperature = ");
	Serial.print(dht.readTemperature());
	Serial.println("C ; ");
	Serial.print("Distance in CM = ");
	Serial.print(cm);
	Serial.print("cm ; ");
	Serial.print("Distance in Inches = ");
	Serial.print(inches);
	Serial.print("inches  \n\n");

	digitalWrite(buz, LOW);
	if (cm <= 10) {
		digitalWrite(led, LOW);
		Serial.print("Danger !!! Obstacle Ahead !!! \n\n");
		digitalWrite(buz, HIGH);
		delay(20);
		digitalWrite(buz, LOW);
		delay(20);

	}
	else if (cm > 10) {
		digitalWrite(led, HIGH);
		digitalWrite(buz, LOW);
	}

	delay(1000);
}

long microsecondsToInches(long microseconds) {
	return microseconds / 74 / 1;
}

long microsecondsToCentimeters(long microseconds) {
	return microseconds / 29 / 2;
}
