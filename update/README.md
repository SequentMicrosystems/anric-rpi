# update

This is the Anric Controller firmware update tool.

## Usage

```bash 
~$ git clone https://github.com/SequentMicrosystems/anric-rpi.git
~$ cd anric-rpi/update/ 
~/anric-rpi/update$ ./update 0 
```

For the 64-bit OS, replace the last line with:
```bash
~/anric-rpi/update$ ./update64 0 
```

If you already cloned the repository, skip the first step.
The command will download the newest firmware version from our server and write it  to the board. 
The stack level of the board must be provided as a parameter.
Make sure there is no script or perogram that acces the I2C port during the update process.
