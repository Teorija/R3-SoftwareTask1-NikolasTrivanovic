//first digit decoder input pins
#define INPUTA1 3
#define INPUTA2 5
#define INPUTA3 4
#define INPUTA4 2
//second digit decoder input pins
#define INPUTB1 10
#define INPUTB2 13
#define INPUTB3 12
#define INPUTB4 11

void setup() {
  Serial.begin(9600);
  
  //set up the pins on the arduino to output data to the connected inputs on the decoder
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void convertPotentiometerToDisplay(int potentiometer_value_10bit, int range_min, int range_max) {
  int size = range_max - range_min;
  
  //the default output value of the potentiometer is from 0 to 1023
  //if we want the change in the potentiometer to correspond to digits 0-X digits
  //then we need to scale down the default output of the potentiometer from 1023 to X,
  //0-X (X numbers, 0/anything=0 so we don't need to include it), 1023/X= step size
  //by dividing 1023 by 1023/X  every movement of the potentiometer is mapped from 0-X
  float potentiometer_value_decimal = (float)potentiometer_value_10bit/((float)1023/(float)size);
  
  //to obtain the value of the ones digit the modulo is used
  //modulo is used because it gives the reamined after division
  //by using modulo10 the remained will always be the ones digit
  //to use modulo to obtain the ones digit the value must be a whole number (integer)
  //eg 56modulo10 ---> R=6 (ones digit)
  int ones_digit = ((int)(potentiometer_value_decimal))%10;
  
  //to obtain the tens value of the potentiometer decimal value
  //we find out how many times 10 goes into the decimal value
  //this time were ignoring the remainder
  //eg 56/10 ---> D=5 (tens digit)
  int tens_digit = ((int)(potentiometer_value_decimal))/10;
  
  //hardcoded array of digits 0-9 in BCD for the decoder inputs (A,B,C,D)
  //the first 4 elements of the array is the BCD (LSB- 1st, MSB - 4th)
  //the fifth element is the digit identifier for the potentiometer value passed in
  int digits[10][5] 
  {
  {0,0,0,0,0},
  {1,0,0,0,1},
  {0,1,0,0,2},
  {1,1,0,0,3},
  {0,0,1,0,4},
  {1,0,1,0,5},
  {0,1,1,0,6},
  {1,1,1,0,7},
  {0,0,0,1,8},
  {1,0,0,1,9}
  }; 
  
  //given the ones and tens value run through the array of digits to find its BCD match
  //when a digit matches use the BCD associated with the digit as input for the decoder
  for (int i=0; i<10; i++) {
    //write to 7 segment display showing the ones digit
    if (digits[i][4] == ones_digit) {   
      digitalWrite(INPUTB1, digits[i][0]);
 	  digitalWrite(INPUTB2, digits[i][1]);
  	  digitalWrite(INPUTB3, digits[i][2]);
  	  digitalWrite(INPUTB4, digits[i][3]);
    }
    //write to 7 segment display showing the tens digit
    if (digits[i][4] == tens_digit) {
      digitalWrite(INPUTA1, digits[i][0]);
 	  digitalWrite(INPUTA2, digits[i][1]);
  	  digitalWrite(INPUTA3, digits[i][2]);
  	  digitalWrite(INPUTA4, digits[i][3]); 
    }
  } 
}

void loop() {
  //read the voltage value from A0 after it passes through the potentiometer
  int potentiometer_value_10bit = analogRead(A0);
  
  //translate the potentiometer to the displays given a specific range of values to be mapped to
  convertPotentiometerToDisplay(potentiometer_value_10bit, 0, 99);
}
