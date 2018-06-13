# Running

### Auto Run

By Default the unit should automatically run the application.

But if not to make it auto run.

`sudo nano /etc/rc.local`

Add the following lines

```
cd /home/pi/openFrameworks/apps/myApps/Birds/bin/
./Birds & # Non Blocking
```

<<<<<<< HEAD
### Stopping the Program

To Stop the program you'll need to do it via the command line.

Open Terminal

Run the following commands.

```
ps -ax | grep AngelaDavies
```

Make a note of the Number to the left of the Screen. This is its PROCESS_ID.

``` 
sudo kill -9 PROCESS_ID
```

That should kill the program.

Alternatively, open the raspberry pi start button. Go to Shutdown and click reboot this will reboot the Pi and relaunch the application.

=======
>>>>>>> 4537477758fbc738055e2b0a2b82e8e5447b6915
### Manually running

If you want to manually start the program.

Open Terminal 

```
cd /home/pi/openFrameworks/apps/myApps/Birds/bin/
./Birds &
```
