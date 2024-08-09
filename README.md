# anric-rpi
Drivers for Anric controller


## Setup

Enable I2C communication first:
```bash
sudo raspi-config
```
A good article about I2C on Raspberry can be found [here](https://www.raspberrypi-spy.co.uk/2014/11/enabling-the-i2c-interface-on-the-raspberry-pi/).

If you use Ubuntu you need to install `raspi-config` first:
```bash
sudo apt update
sudo apt install raspi-config
```

Make sure you have all tools you need:
```bash
sudo apt update
sudo apt-get install git build-essential
```

## Usage

Install the command:
```bash
git clone https://github.com/SequentMicrosystems/anric-rpi.git
cd anric-rpi/
sudo make install
```

Now you can access all the functions of the Anric controller through the command "anric". Use -h option for help:
```bash
anric -h
```

If you clone the repository any update can be made with the following commands:
```bash
cd anric-rpi/  
git pull
sudo make install
```
