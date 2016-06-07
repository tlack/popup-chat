# PopupChat 

PopupChat is an open anonymous instant chat room.

![Screenshot of PopupChat Arduino instant chat room](http://www.modernmethod.com/send/files/popupchatscreenshot.jpg)

PopupChat is an Arduino sketch that turns your ESP8266 into an open wifi access
point that connects users to an anonymous chat room.  The user is (usually)
sent directly into a popup web browser with the software open as soon as they
connect to the wireless AP, because it acts like a Captive Portal (think "hotel
wifi").

## Ethics

PopupChat features impermanence. All data is temporary, and PopupChat maintains
no logs. The entire system is reset to its default state when power is cycled. 

## Purpose

I wanted to explore the ESP8266 and I'm fascinated by the opportunities that
highly connected low cost devices like the ESP8266 (and hopefully ESP32)
engender.

Data points:

- It's conjectured that the ESP8266 can run for up to 17 days on merely a watch
	battery
- The chip costs $2 in bulk, or $10 for a deee-luxe development board
- Not much of an operating system to cause confusing behavior
- Single-purposes devices theoretically enable a smaller attack surface for
	security attacks (in practice vendor bugs probably mitigate the benefit here..
	note ESP8266 buggy TLS)

## Inspiration

I miss the hyper local and easy to operate bulletin board systems of my youth.
My favorite part was checking the Wall to see who's logged on and left a message.
Similar to the old fingerd protocol, it was way easier to communicate 

## Scenarios for usage

All kinds of adhoc communication and group chat systems could be assisted by
software like this running on low-cost boards like the ESP8266.

- Disaster relief/mountain rescue organization, triage, etc.
- On-premises customer chat
- Community bulletin board
- Public soapbox

## Current status

- *Pretty bare bones*. Just a proof of concept.
- I don't think I nailed the Android Captive Portal experience. Doesn't seem to
	pop up the browser. Some more useful info here:
	http://serverfault.com/questions/679393/captive-portal-popups-the-definitive-guide
- Needs great JS UI with autoupdate in order to feel like a finished product.
- Would be best rewritten under NodeMCU.
- Permanency is a valid goal for some situations. PopupChat would benefit from
	a version that can store things permanently. The ideal interface would be the
	NodeMCU `file` API.
- Needs a fine-grained control panel/sysop menu with a way to delete troll
	droppings.
- System should maintain some kind of history of its up times and down times so
	that the sysop can understand issues relating to installation/power/hardware
	etc. I've experienced a few surprise restarts.
- Needs dates, especially system reset dates.

## Installation

I used Arduino to make this, but I'd like to rebuild it with NodeMCU.

Edit the configuration at the top of the .ino file and upload it to your 8266. That's about all it should take.

## Building public PopupChat nodes

It would be cool to leave some nodes running this publicly, in a well known and
identified public place. This is just an idea so far. I'm waiting to receive
more ESP8266s before I can test out the idea more thoroughly.

You must design not just the experience of using your product (art piece or
whatever it ends up being), but also the way it interacts with the environment
around it. Please think carefully before starting.

### Bill of Materials

You don't need any outbound internet connectivity, so that's a nice time saver.

I used the [Elecrow ESP8266 IoT
board](http://www.amazon.com/Elecrow-ESP8266-Module-Battery-Charging/dp/B01DEQI4W2).
The difficult-to-source Wemos D1 Mini may be a better board to use because of
its smaller footprint and easier stacking with other boards/shields. I haven't
had a chance to use it yet.

Some ESP8266 boards allow you to connect an external wifi antenna, but not most
of them. Consider if you need this feature or not. I would suggest the range is
OK out of the box with the internal antenna. ESP-12F, a recent variant, is said
to have a better antenna.

I've had some good luck so far with this 20,000mAh USB solar battery charger. I need to put it through its paces more
intelligently. [ZeroLemon SolarJuice 20k mAh solar battery charger](http://www.amazon.com/ZeroLemon-SolarJuice-20000mAh-Portable-Technology/dp/B00NIOGKL8)

You'll want to find a way to shape it and install it in the installation space.
Do you need to worry about vandalism and abuse?

For the enclosure itself, I've had good luck with InstaMorph so far in terms of
shaping a tough box to mount things in. It dries pretty strong and you can
reheat and reshape bits as neededed. Plus it's cheap and nontoxic. 

To attach to its mounting point (where you decide it to be), I might consider
[CastTape](http://www.amazon.com/CASTtape-Strength-Automotive-Plumbing-Emergency/dp/B01A6DSVBU?ie=UTF8&psc=1&redirect=true&ref_=oh_aui_detailpage_o00_s01),
a carbon fiber product that works similar to Duct Tape - but far more messy, and of course stronger by weight than steel.
Be warned that CF can inhibit RF signals (wifi range!) and trap heat, so use with care, and avoid enclosing the antenna area.

For outdoor use you should consider products that inhibit moisture. Luckily this is a well known problem in electronics. My first thought would be 
some combination of:

- "Liquid electrical tape" compounds like [Gardner's](http://www.amazon.com/Gardner-Bender-LTB-400-4-Ounce-Electrical/dp/B000FPAN2K).
- a few coats of [PlastiDip](http://www.amazon.com/Performix-11218-Multi-Purpose-Coating-Aerosol/dp/B008PO6368). It's available in many colors, and a clear
  variant, but I suggest you make your product's presence known in the conscious environment of the public space where it lives because that's the right thing
	to do. PlastiDip also lends a nice, comfortable materiality to surfaces on which it's applied.
- Final top coat of [NeverWet](http://www.amazon.com/Oleum-274232-Never-Multi-Purpose/dp/B00DNQBFAW), which I confess to not having worked with.

### Concerns with public installations

I've had some random reboots using solar battery chargers. Even when it's just
slightly cloudy. More research required.

It would be best to have NodeMCU running on these public nodes so that you can
remotely connect and debug them. It will be almost impossible to re-connect a
serial terminal to these when problems develop.

Do not intrude on the privacy of others.

## Provenance/License

Much of the concepts behind this were hashed out with B. Lee (TX), whose blue
skies screed infected me in a heady manner. Thanks to Gil C. (FL) for help
understanding Arduino. 

MIT license. Based on Captive Portal by M. Ray Burnette 20150831. 

Built at [Building.co](http://building.co) in Miami, FL.

## Contact

@tlack on Twitter

