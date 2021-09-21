# Teensy YRPXYZ "Pad"

"YRPXYZ SPACE PAD MIDI CONTROLLER"

This is kind of an evolution of an a midi "XY Pad" but instead of being limited to a puny 2 dimensions you can now work in 3D, controlling up to 6 midi CC values (YPRXYZ) instead of the traditional 2. 

## Components
Teensy
Accelerometer/Gyro
2 Buttons
	Btn 1 - Change mode (gyro/accel/all)
	Btn 2 - Send

## Gyro Mode
Yaw, Pitch and Roll are normalized into midi range and each control a different midi CC value. 

## Accel Mode
Acceleration on the X, Y and Z axes each control a different midi CC value.

## All Mode
This is a combination of gyro and accel mode. It will send 6 midi CC values for each variable. 

## Send Button
Midi CC values are only sent when the send button is held down. This allows the user to readjust the position of the device without messing up their set values. 

This could also be a toggle or could be inverted (where pressing stops the send) but I think "press for send" makes the most sense at least as a default.

## Sensitivity

When dealing with gyro readings, there are natural limits (180 degrees on each axis). However, when dealing with accelerometer readings there are no natural limits. 

Acceleration will require some kind of artificial limit that will also determine the sensitivity. Ideally this value should be user tunable but for a proof of concept I will just try to find a good default (Maybe the average human arm span = 127). 


///

yaw
pitch
roll
worldX
worldY
worldZ
realX
realY
realZ

//
Toggle sends
Solo sends
Change CC
Recalibrate

///

4 light sensors on corner of grid
