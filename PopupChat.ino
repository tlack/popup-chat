// PopupChat - a one-screen system to share things locally with your friends via WIFI
// based on: Captive Portal by: M. Ray Burnette 20150831
// homo est bulae
#include <ESP8266WiFi.h>
#include "./DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>

// config
#define CHATNAME "Instant Anonymous Chatroom"
#define BLURB "Experimental local area chat"
#define COMPLAINTSTO "tlack"
#define INDEXTITLE "Howdy friend!"
#define INDEXBANNER "This is a local-only, non-cloud chat room, that you use through your phone's web browser. Messages are deleted every now and then. Have fun and be nice to each other! <a href=/faq>See frequently asked questions..</a>"
#define POSTEDTITLE "Message posted!"
#define POSTEDBANNER "OK, you should be good to go. Your message will stay live for a short time - perhaps a couple of days at most, until the wee server is rebooted. Here it is again:"
const String FAQ = "this is an experiment at making a chat room that only works within the wifi range of a small physical device with no hard drive (called an Arduino)<br/>"
"you can't use the web on this wifi access point, but you can use this message board.<br/>"
"it's completely anonymous and only the last few messages are kept. nothing is saved permanently.<br/>"
"this software is very new. please be patient with bugs. and don't be a jerk.<br/>";

// boring
#define VER "@tlack/popup R0"
const byte HTTP_CODE = 200; // nyi? 511; // rfc6585
const byte DNS_PORT = 53;  // Capture DNS requests on port 53
const byte TICK_TIMER = 1000;
const byte ACTIVITY_DURATION = 60 * TICK_TIMER; // how many seconds should the LED stay on after last visit?
const byte ACTIVITY_LED = 2;
const byte ACTIVITY_REVERSE = 1; // turn off when active, not on.. needed for me
IPAddress APIP(10, 10, 10, 1);    // Private network for server
// state:
String allMsgs="<i>*system restarted*</i>";
unsigned long bootTime=0, lastActivity=0, lastTick=0, tickCtr=0; // timers
DNSServer dnsServer; ESP8266WebServer webServer(80); // standard api servers
void em(String s){ Serial.print(s); } 
void emit(String s){ Serial.println(s); } // debugging
String input(String argName) {
  String a=webServer.arg(argName);
  a.replace("<","&lt;");a.replace(">","&gt;");
  a.substring(0,200); return a; }
String quote() { 
  const byte nquotes=3;
  String quotes[nquotes]={
    "Blushing is the color of virtue -Diogenes of Synope", 
    "A bear can run as fast as a horse",
    "Homo homini lupus est - man is a wolf to fellow man",
  };
  return quotes[millis() / 1000 / 60 / 60 % nquotes];
}
String footer() { return 
  "</div><div class=q><label>Quote of the hour:</label>"+quote()+"</div>"
  "<div class=com>Complaints to: " COMPLAINTSTO "</div>"
  "<div class=by>" VER "</div></body></html>"; }
String header(String t) {
  String a = String(CHATNAME);
  String CSS = "article { background: #f2f2f2; padding: 1em; }" 
    "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
    "div { padding: 0.5em; }"
    "h1 { margin: 0.5em 0 0 0; padding: 0; }"
    "input { border-radius: 0; }"
    "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
    "nav { background: #eb3570; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
    "nav b { display: block; font-size: 1.2em; margin-bottom: 0.5em; } "
    "textarea { width: 100%; }";
  String h = "<!DOCTYPE html><html>"
    "<head><title>"+a+" :: "+t+"</title>"
    "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
    "<style>"+CSS+"</style></head>"
    "<body><nav><b>"+a+"</b> "+BLURB+"</nav><div><h1>"+t+"</h1></div><div>";
  emit("header - "+t);
  emit(h);
  return h; }
String faq() {
  return header("frequently asked questions") + FAQ + footer();
}
String index() {
  return header(INDEXTITLE) + "<div>" + INDEXBANNER + "</div><div><label>Last few messages:</label><ol>"+allMsgs+
    "</ol></div><div><form action=/post method=post><label>Post new message:</label><br/>"+
    "<i>remember:</i> include your name or something like it</i><br/>"+
    "<textarea name=m></textarea><br/><input type=submit value=send></form>" + footer();
}
String posted() {
  String msg=input("m"); allMsgs="<li>"+msg+"</li>"+allMsgs;
  emit("posted: "+msg); 
  return header(POSTEDTITLE) + POSTEDBANNER + "<article>"+msg+"</article><a href=/>Back to index</a>" + footer();
}
void setup() {
  Serial.begin(115200); 
  emit("setup"); 
  bootTime = lastActivity = millis();
  pinMode(ACTIVITY_LED, OUTPUT); led(1);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(CHATNAME);
  dnsServer.start(DNS_PORT, "*", APIP);
  webServer.on("/post",[]() { webServer.send(HTTP_CODE, "text/html", posted()); });
  webServer.on("/faq",[]() { webServer.send(HTTP_CODE, "text/html", faq()); });
  webServer.onNotFound([]() { lastActivity=millis(); webServer.send(HTTP_CODE, "text/html", index()); });
  webServer.begin();
}
void led(byte p){
  byte on=p^ACTIVITY_REVERSE; emit("led"+String(on));
  digitalWrite(ACTIVITY_LED, on ? HIGH : LOW);
}
void tick() {
  String tickCs=String(tickCtr++); // emit("tick #"+tickCs+" @"+String(millis()));
  if ((millis() - lastActivity) < ACTIVITY_DURATION) {
    em("+"); led(1);
  } else {
    em("-"); lastActivity = 0; led(0);
  }
}
void loop() { 
  if ((millis()-lastTick)>TICK_TIMER) {lastTick=millis(); tick();} 
  dnsServer.processNextRequest(); webServer.handleClient(); }
