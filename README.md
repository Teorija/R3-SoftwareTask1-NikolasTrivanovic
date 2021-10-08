# R3-SoftwareTask1-NikolasTrivanovic

<p align="center">
  <img width="260" height="400" src="https://user-images.githubusercontent.com/81877767/136609085-2e440aed-14ad-4148-a20e-1c96b40ff81f.png">
</p>

  Displayed above is a diagram of a circuit/system that translates the potentiometer position to a number between 0 and 99. The circuit consists of an arduino uno, 2 7-segment displays, 2 7-segment decoders and 1 potentiometer. A potentiometer is a variable resistor so the value being translated to the two 7-segment displays is the current resistance level (0 being minimum and 99 being maximum). In order to display the translated value mentioned previously 2 7-segment decoders are used to convert binary coded decimal (BCD) values to the desired digit on the display. These BCD values turn on specific segments of the display (A,B,C,D,E,F,G) creating the desired number. Ten different BCD values are used to represent the 10 possible digits, 0-9. The inputs of the decoders are connected to unused pins on the arduino from which a program can assign HIGH (1) and LOW (0) values to the decoder depending on the potentiometers position (resistance level). 

  When starting the task the first issue was mapping the potentiometer value. When the potentiometer is connected to the arduino through the analog input pin the resistance level (10bit number) was determined to range from 0 to 1023. When trying to manually turn the potentiometer with the mouse the value changed by around 20-21, eg 1023 ---> 1003 ---> 982 etc... Dividing the max value recorded from the potentiometer by the step size (20-21) gives the number of 2 digit values that can be smoothly represented. By smoothily represented I mean that every step or turn from the potentiometer changes the displayed value 1 digit at a time. For example 00,01,02,03,...,99 is smoothly transitioning but 99,97,95,93,....,0 is not. Given the step size of 20-21 and the max value being 1023 the highest 2 digit number you can display smoothly is roughly 1023/20.5 = 49.9 = 49.
  
  After figuring out how to map the potentiometers the only step left was to seperate the 2 digit number (eg, 00, 12, 78) into it's respective ones column and tens column. By seperating these two columns the individual 7-segment display can be set with them. In order to determine the ones column of a 2 digit number you can take the modulo10 of that number. This is done because we are looking for the ones column and modulo gives the remainder after division, if we use modulo10 the remainder is the ones value that doesn't divide into 10 (eg, 9modulo10 = 0, 19modulo10 = 9). In order to find the tens column all we have to do is divide by 10 using the same logic previously mentioned. 
  
  Once the potentiometer value has been mapped and the ones and tens digits have been seperated we can loop through an array storing all the possible digits (0-9) with their respective BCD value (eg, 9 BCD=1001 ---> A(1),B(1),C(1),D(0),E(0),F(1),G(1)). Using these prestored BCD values we can set the output voltage (1=HIGH, 0=LOW) to the pins for the decoders to turn on the 7-segment displays (to the appropriate digit) as the potentiometer changes positions/values.

  After finishing programming the logic for the circuit it can be clearly seen that setting the range to something below 50 results in every number from 1-49 being displayed with every turn of the potentiometer. Whereas when the range is set to 0-99 double the limit every other digit is show from 0-99, eg 99,97,95,93, etc...

Below are six diagrams showing the difference between the range below 50 and above 50.

![output-onlinepngtools (8)](https://user-images.githubusercontent.com/81877767/136610008-daa967ab-06e7-4dc3-aa6b-4a5b57ae7a95.png)
![output-onlinepngtools (9)](https://user-images.githubusercontent.com/81877767/136610030-67f02b3c-f077-4db5-8187-fcd4490f992c.png)
![output-onlinepngtools (10)](https://user-images.githubusercontent.com/81877767/136610040-a993c50f-a04d-433c-a16b-7ce5ae1fdb7c.png)

![output-onlinepngtools (11)](https://user-images.githubusercontent.com/81877767/136610046-bfff57d2-7639-4203-88de-523255bb44bf.png)
![output-onlinepngtools (12)](https://user-images.githubusercontent.com/81877767/136610067-d37240f0-96c6-495c-b05c-e2d1d500345a.png)
![output-onlinepngtools (13)](https://user-images.githubusercontent.com/81877767/136610069-c53a040b-b5fd-422d-a685-23da0ee5a6a0.png)

link to the TinkerCAD circuit simulation: 
https://www.tinkercad.com/things/0JJsqN7cakL-trainingtask1
