
String voice;
int motor1 = 3; //Connect motor 1 To Pin #3 left motor
int motor2 = 9; //Connect motor 2 To Pin #9 rear motor
int motor3 = 11; //Connect motor 3 To Pin #11, right motor

//--------------------------Call A Function-------------------------------//

//the values after each anlogWrite commands are controlling the motor's speed, the max value is 255
//if your drone isn't in balance try to modify the values, example change 130 to 135 if your drone goes backward

void middlespeed() {
  analogWrite(motor1, 130);
  analogWrite(motor2, 130);
  analogWrite(motor3, 130);
}
void fastspeed() {
  analogWrite(motor1, 255);
  analogWrite(motor2, 255);
  analogWrite(motor3, 255);
}

void lowspeed() {
  analogWrite(motor1, 100);
  analogWrite(motor2, 100);
  analogWrite(motor3, 100);

}
//-----------------------------------------------------------------------//
void setup() {
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
}
//-----------------------------------------------------------------------//
void loop() {
  while (Serial.available()) { //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {
      break; //Exit the loop when the # is detected after the word
    }
    voice += c; //Shorthand for voice = voice + c
  }
  if (voice.length() > 0) {
    Serial.println(voice);
    //-----------------------------------------------------------------------//
    //----------Control motors----------//
    if (voice == "*start motors") {
      lowspeed(); //The motors start spin, and the drone slowly comes downer if already flies
    }
    else if (voice == "*fly low") {
      middlespeed(); //Fly the drone, stay in one place
    }
    else if (voice == "*fly higher") {
      fastspeed(); //Maximum motor speed, the drone will go upward very fast
    }

    //----------Directions----------//
    //The drone can be controlled the best in middlespeed state
    else if (voice == "*go left") {
      analogWrite(motor1, 100);
      delay(450);
      analogWrite(motor1, 130);
    }
    else if (voice == "*go right") {
      analogWrite(motor3, 100);
      delay(450);
      analogWrite(motor3, 130);
    }
    else if (voice == "*go backward") {
      analogWrite(motor2, 130);
      delay(300);
      analogWrite(motor2, 130);
    }
    else if (voice == "*go forward") {
      analogWrite(motor2, 200);
      delay(350);
      analogWrite(motor2, 130);
    }
    else if (voice == "*right back") {
      analogWrite(motor1, 200);
      delay(350);
      analogWrite(motor1, 130);
    }
    else if (voice == "*left back") {
      analogWrite(motor3, 200);
      delay(350);
      analogWrite(motor3, 130);
    }

    //-----------------------------------------------------------------------//
    voice = "";
  }
} //Reset the variable after initiating
