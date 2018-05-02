# Setup

This document guides you through the setup procedure for Birds.

We'll do this in sections.

***(unless specified any terminal commands should be followed by the return key)***

## Raspberry Pi

To start we are using a Raspberry Pi 3 loaded with [Raspbian Jessie (2017-07-05)] (http://downloads.raspberrypi.org/raspbian/images/raspbian-2017-07-05/)

When the system has booted. 

Open Terminal.

`sudo raspi-config`

Change the Hostname

`birdsraspberrypi`

Enable the following Interfacing Options

```SSH 
SPI 
I2C 
VNC 
Serial 
VNC
```

Then

`Finish`

Once rebooted.

Open Terminal.

`sudo nano /boot/config.txt`

You need to find the line that looks like this.

```
#Enable audio (loads snd_bcm2835)
dtparam=audio=on
```
Add a `#` infront of the dtparam

```
#Enable audio (loads snd_bcm2835)
#dtparam=audio=on
```
This disables the Pi from using the jack for the microphone.

Add the following line above

`dtoverlay=audioinjector-wm8731-audio`

This forces the Pi to Recognise the Sound card.

`CTRL + x` the prompt will ask do you want to save changes press y and enter.

Now for some reason I had to go through the gui and enable the sound card options.

Open the **Start Menu** 

Go to **Preferences** Then to **Audio Settings**

Click the Switches Tab and click the Microphone radio button

In options Select Mic from the Input Mux options.

In Capture Boost the Volume.

Then Click **Make default**.

That should be the Soundcard and the Pi Setup.

## Arduino 

On your machine. Download Adafruit's Motor Shield Library. Or Like cool kids use the package manager inside the Arduino IDE.

Make sure you get the v2.

Open the Code inside the Arduino folder of this repository. 

Upload to the Arduino. 

Plug the shield into the Arduino, Connect the Motor and Leds. 

Power up.

To Test the code is working correctly.

Open the Serial Monitor

`CMD + SHIFT + m`

Set the Baud rate to `115200`

Then type the following commands.

`f,255;` Full Speed

`f,128;` Half Speed

`s;` Full Stop

