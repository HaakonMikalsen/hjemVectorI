/*
Test for vibrating motors. Experimented with more than one motor at the same time and giving them each their own "turn" trying to let each motor spin up and down induvidualy allowing for closer pulses.
 Effectivness is not conlusive but seems to work to some degree. There is defintavley an incresse in prefomance when adding a third motor. 

 A potenisiometer is connected to simlate an input. The potiemeter is connected as a volatgedivider with resistors and uses the A0 for mesurments


*/




const int numberOfmotors = 3;
const int hapticFeedbackPin[numberOfmotors] = {9,10,11};
int motorIndex = 0;
const int potPin = A0;
const int stepCount = 25;
int steps[stepCount];
int prevPotVal = 0;
const int vibrationDuration =100;

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

void vibrate(int duration){
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
}
