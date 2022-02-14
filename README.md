# Introduction To Robotics 2021-2022
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. In the next section you can see the solved homeworks, detailed, with images or videos depending on the complexity of the homework. Also this repo contains courses, useful links, tips for coding style and other useful materials.

<details>
  <summary>Homework 1</summary>
<br>

For this homework I must fading a RGB led with 3 potentiometers, each potentiometer for red, green, blue. Theoretically, in the end I can create 255 * 255 * 255 different colors combining the intensities of the 3 primary colors. 255 * 255 * 255 because a led take values from 0 to 255.

Video demo: https://youtu.be/Z4e0uCh_60U

Materials required:
* Arduino Uno - 1pcs
* Cable USB Type A to Arduino Uno - 1pcs
* BreadBoard - 1pcs
* RGB Led - 1 pcs
* Resistor 220 Ohm - 3pcs
* Potentiometer - 3pcs
* Black cable for GND - 5 pcs
* Non-Black cable for Signal/5V - 10pcs

How to connect the elements:
- 5V and GND to + and - on breadboard
- GND to cathode RGB Led
- Red branch of Led to Rezistor to Pin ~11
- Green branch of Led to Rezistor to Pin ~10
- Blue branch of Led to Rezistor to Pin ~9
- each left side of Potentimeter to - (breadboard)
- each right side of Potentiometer to + (bradboard)
- each middle side of Potentimeter to A0, A1, A2

<img src="https://user-images.githubusercontent.com/61587939/139099823-e6045fef-3381-4f29-a7d6-73aa7da760fc.jpg" width=650 height=700>
  
</details>
<details>
  <summary>Homework 2</summary>
<br>

For this homework I must simulate a pedestrian crossing with traffic lights for pedestrian and traffic lights for cars. For this we have 4 situations:
1. The traffic light for cars is green and the traffic light for pedestrians is red
2. The traffic light for cars is yellow and the traffic light for pedestrians is red if a pedestrian wants to cross and has pressed the button before
3. The traffic light for cars is red and the traffic light for pedestrians is green and there is a additional buzzer that makes a slow sound
4. The traffic light for cars is red and the traffic light for pedestrians is green and blinking and there is a additional buzzer that makes a fast sound

  After these steps the traffic lights reset and will be back in step 1.

Video demo: https://youtu.be/p1_FeLFnayE

Materials required:
* Arduino Uno - 1pcs
* Cable USB Type A to Arduino Uno - 1pcs
* BreadBoard - 2pcs
* Red Led - 2pcs
* Green Led - 2pcs
* Yellow Led - 1pcs
* Rezistor 330 Ohm - 5pcs
* Buzzer - 1pcs
* Button - 1pcs
* a lot of conectivity cables

How to connect the elements:
* plus of button to pin 2 and - to GND (I used INPUT_PULLUP)
* plus of green / yellow / red led (for cars) to pin 13 / 12 / 11 and - to GND
* plus of green / red led (for pedestrian) to pin 6 / 7
* plus of buzzer to pin 8 and - to gnd

<img src="https://user-images.githubusercontent.com/61587939/140090225-ce7c5268-4a10-425a-95f9-7812b4ce6dc2.jpg" width=650 height=700>

</details>
<details>
  <summary>Homework 3</summary>
<br>
  For this homework I had to make an EMF detector like this: with the help of an improvised antenna from a cable I have to discover the surrounding electromagnetic fields. I will represent the intensity of the electromagnetic field through a 7 segment display with numbers from 0 to 9.
  
Video demo: https://youtu.be/iLIU5k5-5co

  Materials required:
* Arduino Uno - 1pcs
* Cable USB Type A to Arduino Uno - 1pcs
* BreadBoard - 2pcs
* 7 segment display - 1pcs
* buzzer - 1pcs
* resistor 220 Ohm - 2pcs
* resistor 1M Ohm - 3pcs
* a lot of conectivity cables

<img src="https://user-images.githubusercontent.com/61587939/141143308-789f9542-8534-49d7-94f3-39000b169815.jpg" width=650 height=700>

</details>  

<details>
  <summary>Homework 4</summary>
<br>
  For this homework I had to control a 4 digit 7 segment display with the help of a joystick as follows:
  <br><br>
  First state: moving the joystick on the Ox axis can switch from one digit to another, from left to right or from right to left. We can know on which digit we are with the help of the corresponding DP that will blink.
  <br><br>
  Second state: after pressing the joystick button DP remains locked in the current position and by moving the joystick on the Oy axis we can increase or decrease the number displayed in the range 0 - 9. To return to state 1 we must press again on joystick button.
  <br><br>
  Extra: I used interrupts for push button and EEPROM library for loading the last values before shutting down arduino.
  <br><br>
  
Video demo: https://youtu.be/PXJRAQGvKgA
  
Materials required:
  * Arduino Uno - 1pcs
  * Cable USB Type A to Arduino Uno - 1pcs
  * BreadBoard - 2pcs
  * resistor 220 Ohm - 4pcs
  * joystick - 1pcs
  * 4 digit 7 segment display - 1pcs
  * Shift Register: 74HC595 - 1pcs
  * a lot of conectivity cables

<img src="https://user-images.githubusercontent.com/61587939/142218971-82a0daaa-a3c3-4a3f-9d3a-54ec219b53d1.jpg" width=650 height=700>

</details>
