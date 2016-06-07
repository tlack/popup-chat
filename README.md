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

## Provenance/License

Much of the concepts behind this were hashed out with B. Lee (TX), whose blue
skies screed infected me in a heady manner. Thanks to Gil C. (FL) for help
understanding Arduino. 

MIT license. Based on Captive Portal by M. Ray Burnette 20150831. 

Built at [Building.co](http://building.co) in Miami, FL.

## Contact

@tlack on Twitter

