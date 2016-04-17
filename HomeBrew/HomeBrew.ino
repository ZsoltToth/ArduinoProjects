#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#include <OneWire.h>
#include <DallasTemperature.h>


/*
Settings of LCD Panel.
*/

#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
 
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin,BACKLIGHT_PIN,POSITIVE);
LCD *myLCD = &lcd;

/*
 * Settings of Thermometer DS18B20
 */
const int THERMOMETER_BUS= A0; // Thermometer 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(THERMOMETER_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
 * Initialize LCD and Starts the communication with the thermometer
 */
void setup()
{
  lcd.begin(16,2);               // initialize the lcd
  lcd.home ();                   // go home
  sensors.begin();
}

/*
 * Measures the temperature and print it to the LCD Panel.
 */
void loop()
{
  sensors.requestTemperatures();
  
  lcd.home();
  //lcd.print(sensorValue);
  lcd.print("Temp: ");
  lcd.print(sensors.getTempCByIndex(0));
  delay (100);
}
