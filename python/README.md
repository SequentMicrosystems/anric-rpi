# Welcome to anric’s documentation!

# Install

```bash
sudo pip install SManric
```

or

```bash
sudo pip3 install SManric
```

# Update

```bash
sudo pip install SManric -U
```

or

```bash
sudo pip3 install SManric -U
```

# Initiate class

```console
$ python
Python 3.11.8 (main, Feb 12 2024, 14:50:05) [GCC 13.2.1 20230801] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import anric
>>> c = anric.SManric()
>>> c.get_version()
'1.0'
>>>
```

# Documentation

<a id="module-anric"></a>

### *class* anric.SManric(stack=0, i2c=1)

Bases: `object`

Python class to control the Multiio Card for Raspberry Pi.

* **Parameters:**
  * **stack** (*int*) – Stack level/device number.
  * **i2c** (*int*) – i2c bus number


#### get_all_relays()

Get all relays state as bitmask.

* **Returns:**
  (int) Relays state bitmask
  
#### get_all_mosfets()

Get all mosfets state as bitmask.

* **Returns:**
  (int) Mosfets state bitmask


#### get_relay(relay)

Get relay state.

* **Parameters:**
  **relay** (*int*) – Relay number
* **Returns:**
  (int) Relay state
  
  
 #### get_mosfet(mosfet)

Get mosfet state.

* **Parameters:**
  **mosfet** (*int*) – Mosfet number
* **Returns:**
  (int) Mosfet state 


#### get_u_in()

Get 0-10V input  value in volts.

* **Returns:**
  (float) Input value in volts

#### get_u_out()

Get 0-10V output value in volts.

* **Returns:**
  (float) 0-10V output value

#### get_version()

Get firmware version.

Returns: (int) Firmware version number

#### set_all_relays(val)

Set all relays states as bitmask.

* **Parameters:**
  **val** (*int*) – Relay bitmask
  
#### set_all_mosfets(val)

Set all mosfets states as bitmask.

* **Parameters:**
  **val** (*int*) – Relay bitmask  


#### set_relay(relay, val)

Set relay state.

* **Parameters:**
  * **relay** (*int*) – Relay number
  * **val** – 0(OFF) or 1(ON)
  
#### set_mosfet(mosfet, val)

Set mosfet state.

* **Parameters:**
  * **mosfet** (*int*) – Mosfet number
  * **val** – 0(OFF) or 1(ON)  
  
  
#### set_mosfet_pwm(mosfet, val)

Set mosfet pwm fill factor.

* **Parameters:**
  * **mosfet** (*int*) – Mosfet number
  * **val** – (*float*) - Fill factor 0 - 100%    


#### set_u_out( value)

Set 0-10V output value in volts.

* **Parameters:**
  * **channel** (*int*) – Channel number
  * **value** (*float*) – Voltage value


<!-- vi:se ts=4 sw=4 et: -->
