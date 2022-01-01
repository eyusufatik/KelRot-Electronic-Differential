# KelRot-Electronic-Differential
Electronic differential codebase for KelRot 2020 Teknofest car.
The car has three encoders.
1. On the left wheel.
2. On the right wheel.
3. On the steering wheel.

Using the angle of rotation of the steering wheel, Differential object calculates the turning radius, which gives us the needed speed ratio between the left and right motors. Then we take the current wheel speeds and adjust them to the needed ratios using PID loops. Calculations are explained  [here](./Differential.h).


## main.ino
Here we used pin change interrupts to track incremental encoders. The rest is just for testing out the code.
The actual code for the car can be found in Kelrot's github. Although the repo is probably private.

## Differential.h
Using the physical dimensions of the car and the current steering angle, this class calculates the ratio needed between left and right wheels.

## DriveWheel.h
Speed calculations of the left and right wheels are done here.

## SteeringWheel.h
Steering wheel angle of rotation calculations are done here.
