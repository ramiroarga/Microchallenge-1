# Water sensing for urban horticulture

Water explorations for Microchallenges

Hey!!
Welcome to our WATER REPO!

Here we will be updating our work for the Microchallenge´s...


to do: 
* add electronics steps and schematics
* add picture of final product under 'the system'
* add code and lasercut files to repo
* proof-read / final touches
* add this as README.md to the repo


#  SENS_HORT - WATER SENSING FOR URBAN HORTICULTURE 

This repository documents a water testing tube designed and built by [Josephine](https://josephinebourghardt.github.io/MDEF/), [Ramiro](https://ramiroarga.github.io/MDEF/), [Cagsun](https://cagsunacemoglu.github.io/MDEF/), and [Korbi](https://knr-at-iaac.github.io/MDEF/) during the first MDEF 22/23 microchallenge. It should also contain all relevant files (laser cutting patterns, code) and information you need to make it (or adapt it to your needs).

After brainstorming various ideas related to water and urban (domestic) horticulture, we landed on the idea of making a device that senses a few properties of water that are relevant for plants (temperature, electric conductivity, pH). 

Here is what we ended up with:


## THE SYSTEM

![](https://i.imgur.com/W4kveCg.png)

![](https://i.imgur.com/m2M4n5X.jpg)

Our system is composed of the following sensors:
1. Parrot (soil sensor that has onboard EC & Temperature sensors useful for water quality measurement) 
2. Ph Sensor 

To be able to measure the quality of the water,
3. We designed a custom tube (water container) which integrates the sensors and holds the water while a measurement is being carried out.

The intention was to make it possible to integrate this measurement unit into any water system, and measure the water as it's transferred through the pipe.

We have integrated a micro pump to push water into the measurement unit for demonstration purposes. In an existing water system, water might be pressured thus no pumping might be required.

### HOW IT WORKS

To be able to use the Parrot soil sensor, we had to use a Raspberry Pi, because the only open library we could use was developed for linux, written in node.js

The Ph sensor and the pump are driven by the Arduino, due to the simple low level connections and programming required.

The pumping and measuring starts when the user of the system presses a button. 

And in essense, Arduino functions as a multi-sensor communicating the information it gathers to the Raspberry Pi through serial communication over USB.
It sends a continous Ph signal as well as a trigger everytime it recognises a press of a button.

These signals are then picked up by the RaspberryPi, the Ph value is continously shown and when the button is pressed, the pump procedure starts and the measurement unit is filled with water. After that the sensors for EC (electro conducitivity) also run and displayed in the Raspberry terminal.




## THE PROCESS

Here's how we arrived at the outcome described above. This section hopefully also contains all you need to know to replicate the project. *Note on personal contributions: Ramiro and Cagsun focused on the electronics, Josephine and Korbi focused on the casing, tube, etc.*

### MATERIALS 

#### WHAT WE ACTUALLY USED

* 8mm diameter plastic tubing ('level tube'). We used Bossram Ref:626201. This is not ideal because it is quite rigid and making a water-tight connection is difficult. Using flexible tubing everywhere is probably better.
* 10mm flexible tubing (came with the water pump)\
* Solar / DC water pump. We used a JAVTOP JT-280T (6-18V / 0.8-20W, Hmax:60-400cm, Qmax: 280-600 l/h). It works fine (controlled via Arduino)
* Parrot Flower Power (CMMIIT ID: 2013DJ1931). We used this because they were around in the FabLab and we were able to use custom code to integrate it with the Raspberry Pi / Arduino setup. This could be replaced by an elctric conductivity sensor and a thermometer (that's the two metrics we used it for), or whatever sensor you are interested in.
* Silicone hot glue (for sealing purposes)
* Arduino Uno (to control the pump. LED, and sensors)
* Raspberry Pi 3 (to connect to the Parrot). This could either be left out if you use other sensors connected to the Arduino instead. If you want to keep the Raspberry (e.g. because you want to use the Parrot), another option would likely be to connect everything to that - requires different code, though.)
* pH meter (compatible with Arduino). We used the [DFRobot SEN0161] (https://www.application-datasheet.com/pdf/dfrobot/sen0161.pdf0). A disadvantage this has is that it needs to be cleaned between measurements. 
* color changing LED (like [this one] (https://educarparaelcambio.com/arduino/reto-10-led-rgb-jugando-con-los-colores-primarios-de-la-luz/))
* a breadboard (e.g. the one included in most Arduino kits)
* breadboard jumper wires
* soldering metal (to solder the the cables to the LED)
* 3mm and 5mm thick acrylic boards (for the laser cut parts)
* solutions of various acidities (to calibrate the pH sensor). We used lemon juice, bleach, and distilled water.
* acrylic tube (63 mm diameter)
* rubber ring (53mm diameter, 5 mm thick)




#### WHAT WE THOUGHT WE'D USE BUT DIDN'T
* pre-made caps for the tube. We didn't use these because we wanted to have removable caps, so that one might create different caps for different purposes that can be used modularly. 
* thinner tubing. Wed din't use it because we wanted water to flow faster.

#### TOOLS WE USED
* laser cutter (needs to be able to cut through 5mm acrylic)
* hot glue gun
* laptops to code, document, and design
* pen and paper

### WHAT WE DID / WHAT YOU COULD DO

#### THE ELECTRONICS

#### THE TUBE AND CASING

STEP 1 · BRAINSTORMING & initial idea
Sketch and illustrate what we want to do and how it could be done.
![](https://i.imgur.com/eGDcpei.jpg)


STEP 2 · SKETCHING
Look at what materials we could use. Here we have a PH Sensor, a Temperature Sensor and a Parrot Flower Power Sensor that measures conductivity and .., a transparent 63mm pipe and a cap as well as tubes in different dimensions. 
![](https://i.imgur.com/yBM4OoN.jpg)
We bought this cap in a hardware store to be able to close the tube, yet when attached it is hard to remove, as well as hard to manipulate if we want to add sensors or tubes for water supply from the ends.
![](https://i.imgur.com/JzkRZnu.jpg)
Therefor we chose to make caps that could be lasercut to create possibilities of adding other sensors, being modular and reusable.

STEP 3 · LASERCUT A TESTCAP
Measure the outside and inside radius of the tube to create a part that to fit the top as a handle and a part to fit the inside which will be part of making it watertight. Draw a test file in Illustrator to lasercut and test the radius for fitting the pieces for the cap in the tube/pipe. Outline is Red for cutting. We cut 5mm Transparent Acrylic using the settings:
P 90
S 0.5
Hz 20000

![](https://i.imgur.com/Z7Dcrn5.png)

The thickness of the tube can vary, making the inside radius uneven, therfor it was important to test small variables in size. They should be easy to put inside the tube while fitting snug. We had to test different dimensions by decreasing the radius by 1-2 mms at a time before the pieces fit inside this tube. It can vary by tubes and is therefor good to test small pieces before cutting the final ones.

![](https://i.imgur.com/KG1KyOu.jpg)


STEP 4 · TEST WATER SEALING
Assemble the pieces and put the cap on the tube to test how water tight it is. Even with the screw the piece was tight without leaking. 



STEP 4 · LASERCUT PIECES 

Make an illustrator file with the different pieces and the outcuts for the sensors and tubes. For each cap we made two top pieces, two pieces with the tubes inside radius and one piece 4mm smaller than the inside radius.

Here we cut the outscuts first (Red) and therafter the outlines (Blue) again in 5mm Transparent Acrylic with the Settings to cut:
P 90
S 0.5
Hz 20000



![](https://i.imgur.com/HFD9TfT.png)

![](https://i.imgur.com/QouzTha.jpg)

![](https://i.imgur.com/fMebl7U.jpg)



STEP 5 · ASSEMBLE
Assemble the pieces in the correct order, being aware of the outcuts for sensors and tubes aligning. Fasten with a bolt and put the rubber band in place.
![](https://i.imgur.com/mdasktm.jpg)
![](https://i.imgur.com/WtcPhf1.jpg)
![](https://i.imgur.com/W4eailq.jpg)
STEP 6 · ASSEMBLE PARTS & SEAL
When the caps are assembled and water tight, assemble the tubes and sensors inside the precut holes and seal with Silicone Hot Glue. Let dry for at least 1 hour.
![](https://i.imgur.com/NLP59fv.png)

![](https://i.imgur.com/NG7tyA3.jpg)


STEP 7 · TEST WATER SEALING & PUMPING WATER
Assemble the caps and tube and test if water tight. Then test the pump and release fo water inside. The water should enter the tube and stay there when clamping the release tube and should reach the top where the sensors are. When undoing the clamp the water should flow out of the tube. 
![](https://i.imgur.com/F625k6U.jpg)


STEP 8 · TEST SENSORS & SOFTWARE
Test if the sensors are reacting and measuring water quality. 

STEP 9 · DEVELOPMENT
As this is just a prototype to understand what kind of sensors exist, how they work and how they could be used, the tool we worked on to hold the sensors and extract and hold water for testing is simply made. The important things we learned were how we could water seal with caps and how the system could work. To improve this we would work on the size, where it could be a lot smaller. Using other ways of sealing the tubes and how it would work in a system, how would it be held if modular, and how it would be attached in a water system




## RESOURCES 

### Pump Circuitry
https://docs.arduino.cc/learn/electronics/transistor-motor-control

```
/*
 Motor Control with a Transistor

 This example shows you how to control a motor's using a transistor.
 When a pushbutton on pin 2 is pressed, the Arduino will control a transistor
 via PWM, which will slowly ramp up the motor's speed, then slow it down.

 The circuit :
 * momentary switch with one end connected to 5V, the other end connected
   to GND through a 10-kilohm resistor, and digital pin 2.
 * TIP120 tranistor, with the Base connected to digital pin 9, the Emitter to ground,
   and the Collector to one lead from a 9V DC motor
 * a 9V battery, with the ground connected to the Arduino's ground, and the power
   connected to the motor
 * 1N4001 diode across the motor's leads, with the striped side connected to the 9V

 The Arduino can only provide 40mA at 5V on its pins. Most motors require
 more current and/or voltage to overcome inertia and run. A transistor
 can act as a digital switch, enabling the Arduino to control loads with
 higher electrical requirements.

 Created on 03 January 2013
 by Scott Fitzgerald

 https://docs.arduino.cc/learn/electronics/transistor-motor-control

 This example code is in the public domain.
 */

// give a name to digital pin 2, which has a pushbutton attached
int pushButton = 2;

// the transistor which controls the motor will be attached to digital pin 9
int motorControl = 9;

// the setup routine runs once when you press reset:
void setup() {
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);

  // make the transistor's pin an output:
  pinMode(motorControl, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {

  // read the state of the button and check if it is pressed
  if(digitalRead(pushButton) == HIGH){
    // ramp up the motor speed
    for(int x = 0; x <= 255; x++){
      analogWrite(motorControl, x);
      delay(50);
    }

    // ramp down the motor speed
    for(int x = 255; x >= 0; x--){
      analogWrite(motorControl, x);
      delay(50);
    }    
  }

  delay(1);        // delay in between reads for stability
}
