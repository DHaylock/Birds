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

### Manually running

If you want to manually start the program.

Open Terminal 

```
cd /home/pi/openFrameworks/apps/myApps/Birds/bin/
./Birds &
```