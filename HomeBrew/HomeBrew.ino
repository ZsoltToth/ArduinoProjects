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
 * Setup of motor rotation. 
 * H bridge L911S
 * 
 */
const int MOTOR_FORWARD = 10;
const int MOTOR_BACKWARD = 11;
const int MOTOR_SPEED_POTMETER = A1;
const int DELAY_TIME = 500;
const int SPINNING_TIME = 5000;
const int SPIN_FORWARD = 0;
const int SPIN_BACKWARD = 1;

int timeCounter = 0;
int spinDirection = 0;
/*
 * Initialize LCD and Starts the communication with the thermometer
 */
void setup()
{
  lcd.begin(16,2);               // initialize the lcd
  lcd.home ();                   // go home
  sensors.begin();
  pinMode(MOTOR_FORWARD, OUTPUT);
  pinMode(MOTOR_BACKWARD, OUTPUT);
  pinMode(MOTOR_SPEED_POTMETER, INPUT);
  timeCounter = 0;
}

/*
 * Measures the temperature and print it to the LCD Panel.
 */
void loop()
{
  sensors.requestTemperatures();
  int speedPotValue = analogRead(MOTOR_SPEED_POTMETER);
  int spinSpeed = map(speedPotValue,25,1000,0,255); //0-25 is considered 0 and above 1000 is considered 1024 max value
  lcd.home();
  //lcd.print(sensorValue);
  lcd.print("Temp: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(0,1);
  lcd.print(speedPotValue);
  lcd.print(";");
  timeCounter = (timeCounter + DELAY_TIME) % SPINNING_TIME;
  if(timeCounter == 0){
    spinDirection = spinDirection == SPIN_FORWARD ? SPIN_BACKWARD : SPIN_FORWARD;
  }
  if(spinDirection == SPIN_FORWARD){
    forward(spinSpeed);
  }
  if(spinDirection == SPIN_BACKWARD){
    backward(spinSpeed);
  }

  lcd.setCursor(0,1);
  lcd.print(speedPotValue);
  lcd.print(";");
  lcd.print(timeCounter);
  lcd.print(";");
  lcd.print(spinDirection);
  lcd.print("  ");
  delay (DELAY_TIME);
}

void forward(int spinningSpeed){
  analogWrite(MOTOR_FORWARD,spinningSpeed);
  analogWrite(MOTOR_BACKWARD, 0);
}

void backward(int spinningSpeed){
  analogWrite(MOTOR_FORWARD,0);
  analogWrite(MOTOR_BACKWARD, spinningSpeed);
}

