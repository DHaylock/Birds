# Compiling 

This section will guide you through the compilation of the project. Unfortunately this will be code heavy.

## openFrameworks

We need to get and build openFrameworks, before we can start making our application.

I've added a script to this repository that should pull all the addons for you.

Open Terminal

First lets get oF 

Go to the Home Directory

`cd`

`curl -O http://openframeworks.cc/versions/v0.9.8/of_v0.9.8_linuxarmv6l_release.tar.gz`

Make a folder called openFrameworks

`mkdir openFrameworks`

Unzip the file. This will put the content into the folder we just made.

`tar vxfz of_v0.9.8_linuxarmv6l_release.tar.gz -C openFrameworks --strip-components 1`

Lets get some dependencies

`cd /home/pi/openFrameworks/scripts/linux/debian`
`sudo ./install_dependencies.sh`

This will take awhile, when prompted press y and enter.

Then you need to compile oF.

`make -j3 Release -C /home/pi/openFrameworks/libs/openFrameworksCompiled/project`

Again this will take awhile.

Yay! 

Cool now we need get the additional packages.

Run the following script

`./GetAddons.sh`

Cool

Lets make our Application.


## Making the Application

You should be able to copy the code across from the repo the apps folder.

`mkdir /home/pi/openFrameworks/apps/myApps/Birds`

Copy the content across

`cp -r BirdsRPi/* /home/pi/openFrameworks/apps/myApps/Birds`

Then 

`make -j3`

All being well once compiled

`make RunRelease`
