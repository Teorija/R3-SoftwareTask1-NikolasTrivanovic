# R3-SoftwareTask1-NikolasTrivanovic

<p align="center">
  <img width="260" height="400" src="https://user-images.githubusercontent.com/81877767/136469263-36d8c45d-d036-4b87-8614-06a24f9e427b.png">
</p>

  Displayed above is a diagram of a circuit/system that translates the potentiometer position to a number between 0 and 99. The circuit consists of an arduino uno, 2 7 segment displays, 2 7-segment decoders and 1 potentiometer. A potentiometer is a variable resistor so the value being translated to the two 7 segment displays is the current resistance level (0 being minimum and 99 being maximum). In order to display the translated value mentioned previously 2 7-segment decoders are used to convert binary coded decimal (BCD) values to the desired digit on the display. These BCD values turn on specific segments of the display (A,B,C,D,E,F,G) creating the desired number. Ten different BCD values are used to represent the 10 possible digits, 0-9. The inputs of the decoders are connected to unused pins on the arduino from which a program can assign HIGH (1) and LOW (0) values to the decoder depending on the potentiometers position (resistance level). 

  When starting the task the first issue was mapping the potentiometer value. When the potentiometer is connected to the arduino through the analog input pin the resistance value (10bit number) was determined to range from 0 to 1023. When trying to manually turn the potentiometer with the mouse the value changed by around 20-21, eg 1023 ---> 1003 ---> 982 etc... Dividing the max value recorded from the potentiometer by the step size (20-21) gives the number of 2 digit values that can be smoothly represented. By smoothily represented I mean that every step or turn from the potentiometer changes the displayed value 1 digit at a time. For example 00,01,02,03,...,99 is smoothly transitioning but 99,97,95,93,....,0 is not. Given the step size of 20-21 and the max value being 1023 the highest 2 digit number you can display smoothly is roughly 1023/20.5 = 49.9 = 49.
  
  After figuring out how to map the potentiometers the only step left was to seperate the 2 digit number (eg, 00, 12, 78) into it's respective ones column and tens column. By seperating these two columns the individual 7-segment display can be set with them. In order to determine the ones column of a 2 digit number you can take the modulo10 of that number. This is done because we are looking for the ones column and modulo gives the remained after division, if we use modulo10 the remained is the ones value that doesn't divide into 10 (eg, 9modulo10 = 0, 19modulo10 = 9). In order to find the tens column all we have to do is divide by 10 using the same logic previously mentioned. 
  
  Once the potentiometer value has been mapped and the ones and tens digits have been seperated we can loop through an array storing all the possible digits (0-9) with their respective BCD value (eg, 9 BCD=1001 ---> A(1),B(1),C(1),D(0),E(0),F(1),G(1)). Using these prestored BCD values we can set the output voltage (1=HIGH, 0=LOW) to the pins for the decoders to turn on the 7-segment displays as the potentiometer changes positions/values.

  After finishing programming the logic for the circuit it can be clearly seen that setting the range to something below 50 results in every number from 1-49 being displayed with every turn of the potentiometer. Whereas when the range is set to 0-99 double the limit every other digit is show from 0-99, eg 99,97,95,93, etc...

Below are six diagrams showing the difference between and range below 50 and above 50.

![output-onlinepngtools](https://user-images.githubusercontent.com/81877767/136445098-b2f88fc9-4b53-4687-ac2b-9a338a230fea.png)
![output-onlinepngtools (1)](https://user-images.githubusercontent.com/81877767/136445100-1f951f87-c921-4f67-be4d-10290d3eadd8.png)
![output-onlinepngtools (2)](https://user-images.githubusercontent.com/81877767/136445096-7f4cc84b-23f0-4f0f-9d32-6d2e98a9221b.png)

![output-onlinepngtools (4)](https://user-images.githubusercontent.com/81877767/136473027-ca5a85c1-35cf-4f11-b314-7e19e406824a.png)
![output-onlinepngtools (5)](https://user-images.githubusercontent.com/81877767/136473038-6262eea6-3efa-4491-a4fb-5f07e5c144cd.png)
![output-onlinepngtools (6)](https://user-images.githubusercontent.com/81877767/136473046-03ff0596-df43-45e0-8e32-2f3d73e560d3.png)

link to the TinkerCAD circuit simulation: 
https://www.tinkercad.com/things/0JJsqN7cakL-trainingtask1
