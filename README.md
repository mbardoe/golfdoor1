# golfdoor1

Golf Party in a box that when it senses a ball in the box
 the lid of the box comes down. 
 
 There parts for this project are:
 
 * photoresistor
 * 3 yellow LED's
 * 1 red LED
 * 1 green LED
 * 2 mini Servo motors
 * 2 220 ohm resistor
 * 1 megaohm resistor
 * 1 push button
 * 10k ohm resistor
 
 The circuit has the photo resistor with the 1 mega ohm resistor
 The yellow lights are wired in parallel with no resistor.
 The red and green lights are wired to the arduino pins and a 220 ohm resistor to ground
 The push button has a 10k ohm resistor to ground and a listening pin on the arduino.
 
 The goal of this code is to set up the level of the light in the box. If your readings 
 are too high use a smaller resistor.
 
 Then once the baseline for the photoresistor readings is found the box goes into wait mode.
 
 When the button is pressed the inside lights turn on. There is a delay to make sure the 
 photoresistor comes up to full power. Then the green light comes on to show that it is ready.
 
 When the ball comes in, it sets off the door. The green light goes off, and we return to wait
 mode. When the button is pressed the user has 5 seconds to retrieve the ball and reset. Then
 the green light comes on, and we are ready again.
 
 Matthew K. Bardoe 7/2/17
 
 
 This example code is part of the public domain 
