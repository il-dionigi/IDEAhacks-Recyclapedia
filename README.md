# IDEAhacks-Recyclopedia

Work done as part of IDEA Hacks 2018 hosted by the division of the Institute of Electrical and Electronics Engineers at UCLA during the Winter Quarter of the 2017-2018 school year.
****
**Our IDEA** 

Keeping our world clean and healthy is important, even more-so now that there are so many people who are seemingly treating it as if it was disposable. Our product would serve to both educate and incentivize people to recycle items as it is basically an encyclopedia for all things recyclable. The Recyclopedia works to revolutionize recycling by both keeping a counter of how many items have been recycled in a recycling bin as well as giving treats to people for properly recycling.

**Target Population**

Our product would be best for those who either don't know how recycling works in their area (i.e. your average person) or have never before recycled anything (i.e. primary school children). By using our Recyclopedia, they would gain the assistance they need to start helping keep our planet healthy and landfills cleaner.

**How It Works**

If the user is ever curious about whether or not something is recyclable, they simply walk up with their trash and scan their barcode. If the Recyclopedia has seen the barcode before and knows it is recyclable, it will pulse a green LED, increment the count of recycled items, and award the user if they reach for a Sugary Treat and Reward (STaR). If the system knows that the item is no recyclable, it will simply pulse the red LED. On the item not being known, the blue LED is pulsed and the Recyclopedia waits for the user to press a button corresponding to whether or not that item is recyclable. Once given a response, the Recyclopedia stores this to memory for future use and does the other corresponding actions.

**Hardware**
* [Arduino Uno](https://www.adafruit.com/product/50)
* [Alphanumeric Display](https://www.adafruit.com/product/1907)
* [PIR Sensor](https://www.adafruit.com/product/189)
* [Power HD Micro Servo](https://www.pololu.com/product/1049)
* [RaspberryPi Model 3](https://www.adafruit.com/product/3055)

**Software**

*Arduino*
* [ADA Fruit Backpack Library](https://github.com/adafruit/Adafruit_LED_Backpack) - LED  Display
* [ADA Fruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) - LED Graphics

*Raspberry Pi*
* [ADA Fruit MCR12](https://github.com/jacopo-j/mcr12_serial) - Barcode Scanner
* [Python Serial](https://pypi.python.org/pypi/pyserial) - Arduino Interface

**Demos**

Here is a link to a video

****
**Collaborators:**  
[Brian Raymond](https://github.com/il-dionigi) | [Jeff Lung](https://github.com/jlung20) | [Kevin Ke-En Sun](https://github.com/inherentlyMalicious)
