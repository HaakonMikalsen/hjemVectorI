/*
Test for vibrating motors. Experimented with more than one motor at the same time and giving them each their own "turn" trying to let each motor spin up and down induvidualy allowing for closer pulses.
 Effectivness is not conlusive but seems to work to some degree. There is defintavley an incresse in prefomance when adding a third motor. 

 A potenisiometer is connected to simlate an input. The potiemeter is connected as a volatgedivider with resistors and uses the A0 for mesurments


*/


/*
Un optemized
sketch uses 3174 bytes (9%) of program storage space. Maximum is 32256 bytes.
Global variables use 248 bytes (12%) of dynamic memory, leaving 1800 bytes for local variables. Maximum is 2048 bytes.

const int numberOfmotors = 3;
const int hapticFeedbackPin[numberOfmotors] = {9,10,11};
int motorIndex = 0;
const int potPin = A0;
const int stepCount = 25;
int steps[stepCount];
int prevPotVal = 0;
const int vibrationDuration =100;
*/


/*
Variable type optemized
ketch uses 3148 bytes (9%) of program storage space. Maximum is 32256 bytes.
Global variables use 243 bytes (11%) of dynamic memory, leaving 1805 bytes for local variables. Maximum is 2048 bytes.

const byte numberOfmotors = 3;
const byte hapticFeedbackPin[numberOfmotors] = {9,10,11};
byte motorIndex = 0;
const byte potPin = A0;
const byte stepCount = 25;
int steps[stepCount];
int prevPotVal = 0;
const byte vibrationDuration =100;

Note:
Some imporvemt. Definitvly good if memory becomes problem later

*/

/*
Program mem Optimized + Variable type
Sketch uses 3150 bytes (9%) of program storage space. Maximum is 32256 bytes.
Global variables use 241 bytes (11%) of dynamic memory, leaving 1807 bytes for local variables. Maximum is 2048 bytes.

#include <avr/pgmspace.h>

const PROGMEM byte numberOfmotors = 3;
const PROGMEM byte hapticFeedbackPin[numberOfmotors] = {9,10,11};
byte motorIndex = 0;
const PROGMEM byte potPin = A0;
const PROGMEM byte stepCount = 25;
int steps[stepCount];
int prevPotVal = 0;
const PROGMEM byte vibrationDuration =100;

Note:
Memeory improvemt was small and uses more flash memory wich could be a problem later
*/

#include <avr/pgmspace.h>

const PROGMEM byte numberOfmotors = 3;
const PROGMEM byte hapticFeedbackPin[numberOfmotors] = {9,10,11};
byte motorIndex = 0;
const PROGMEM byte potPin = A0;
const PROGMEM byte stepCount = 25;
int steps[stepCount];
int prevPotVal = 0;
const PROGMEM byte vibrationDuration =100;

void setup() {
  Serial.begin(9600);
  for (const auto & pin : hapticFeedbackPin){
    pinMode(pin,OUTPUT);
  }
  pinMode(potPin,INPUT);


  for (int i = 0;i<stepCount;i++){
    steps[i] = floor(1000/stepCount)*i;
  }

}

void vibrate(const int duration){
  int tenthDuration = floor(duration/10);
  const int pin = hapticFeedbackPin[motorIndex];
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin,LOW);
  delay(tenthDuration);
  motorIndex++;
  if (numberOfmotors == motorIndex){
    motorIndex = 0;
  }
}

// void vibrateTwo(int duration){
//   int tenthDuration = floor(duration/10);
//   for (const auto & pin : hapticFeedbackPin){
//     digitalWrite(pin, HIGH);
//     delay(duration);
//     digitalWrite(pin,LOW);
//     delay(tenthDuration*3);
//   }
// }


void loop() {
  int currentStepIndex = 0;
  int prevStepIndex = 0;
  int potVal = analogRead(potPin);
  for (int i = 0; i<(stepCount-1);i++){
    if (potVal >= steps[i]){
      if (potVal < steps[i+1]){
        currentStepIndex = i;
      }
    }
    if (prevPotVal >= steps[i]){
      if (prevPotVal < steps[i+1]){
        prevStepIndex = i;
      }
    }
  }
  if (prevStepIndex != currentStepIndex){
    vibrate(vibrationDuration);
  }
  prevPotVal = potVal;
  Serial.println(potVal);

  // vibrate(5000);
}
