# Editing

No doubt at some point you will need to edit something. This guide will help you make those changes.

### WiFi

At some point you might want to put the Raspberry Pi on the Internet. You can either plug in a monitor, keyboard and mouse and do it through the GUI. Or with a little trick.

Open Terminal

`cd Desktop`

Make a file called 

`touch wpa_supplicant.conf`

Double click the file.

Add the Following to the File.

```
update_config=1
ctrl_interface=/var/run/wpa_supplicant

network={
 ssid="WiFi Name"
 psk="Password"
}
```

Plug the SD card from the Raspberry Pi in to your Laptop.

When the image appears. 

Drag and Drop the wpa_supplicant.conf file onto the SD card.

Plug it back into the Raspberry Pi and Power on. This should add the credentials to the system.

### Configuration

The application has some variables that can be altered via a json file

`/home/pi/openFrameworks/apps/myApps/Birds/bin/data/config.json`

The following Variables are available:

Variable Name | Default | Meaning
--- | --- | ---
**where** | ***Development*** | where is the unit currently
**serialname** | ***/dev/tty.misc*** | what serial device are you trying to connect to.
**baudrate** | ***115200*** | communication speed between the computer and the Arduino
**threshold** | ***25*** | the audio level that will trigger the sculpture to stop
**log** | ***false*** | do you want the unit to log events to a csv file
**post** | ***false*** | do you want the unit to post events to a online server
**url** | ***localhost:8888*** | the route which we should send the events
**secret** | ***randomstring*** | unused currently
**statictimerlength** | ***60*** | length of time the unit stays still for (in seconds)
**ramptimerlength** | ***90*** | length of time the unit ramps in and out (in seconds)
**logtimerlength** | ***60*** | time between logging data (in seconds)


### Serial Port
If you are having trouble with finding the correct device.

Open Terminal

`ls -l /dev/tty.*`

This will show you all the serial devices available.

On the Raspberry Pi it should be 

`/dev/ttyACM0`
