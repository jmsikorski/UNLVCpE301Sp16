/*jslint node:true, vars:true, bitwise:true, unparam:true */
/*jshint unused:true */

/*
The Web Sockets Node.js sample application distributed within Intel® XDK IoT Edition under the IoT with Node.js Projects project creation option showcases how to use the socket.io NodeJS module to enable real time communication between clients and the development board via a web browser to toggle the state of the onboard LED.

MRAA - Low Level Skeleton Library for Communication on GNU/Linux platforms
Library in C/C++ to interface with Galileo & other Intel platforms, in a structured and sane API with port nanmes/numbering that match boards & with bindings to javascript & python.

Steps for installing/updating MRAA & UPM Library on Intel IoT Platforms with IoTDevKit Linux* image
Using a ssh client:
1. echo "src maa-upm http://iotdk.intel.com/repos/1.1/intelgalactic" > /etc/opkg/intel-iotdk.conf
2. opkg update
3. opkg upgrade

OR
In Intel XDK IoT Edition under the Develop Tab (for Internet of Things Embedded Application)
Develop Tab
1. Connect to board via the IoT Device Drop down (Add Manual Connection or pick device in list)
2. Press the "Settings" button
3. Click the "Update libraries on board" option

Review README.md file for in-depth information about web sockets communication

*/
var mraa = require('mraa'); //require mraa
console.log('MRAA Version: ' + mraa.getVersion()); //write the mraa version to the Intel XDK console
//var myOnboardLed = new mraa.Gpio(3, false, true); //LED hooked up to digital pin (or built in pin on Galileo Gen1)
var myOnboardLed = new mraa.Gpio(13); //LED hooked up to digital pin 13 (or built in pin on Intel Galileo Gen2 as well as Intel Edison)
myOnboardLed.dir(mraa.DIR_OUT); //set the gpio direction to output
var ledState = true; //Boolean to hold the state of Led

var express = require('express');
var app = express();
var path = require('path');
var http = require('http').Server(app);
var io = require('socket.io')(http);

var userId;
var data;
var users = 0;

app.get('/', function(req, res) {
    //Join all arguments together and normalize the resulting path.
    res.sendFile(path.join(__dirname + '/client', 'index.html'));
});

//Allow use of files in client folder
app.use(express.static(__dirname + '/client'));
app.use('/client', express.static(__dirname + '/client'));

//Socket.io Event handlers
io.on('connection', function(socket) {

    socket.on('chat message', function(msg) {
        io.emit('chat message', msg);
        console.log(msg.userId + ': ' + msg.value);
    });

    if(users === 0) {
        setInterval(function(){
            if(sensor_dat !== undefined && sensor_dat.length === 13) {
                io.emit('sensor data', {Lat: sensor_dat[1], Lat_m: (sensor_dat[2]/60).toPrecision(6).toString(), Lon: sensor_dat[3], Lon_m: (sensor_dat[4]/60).toPrecision(6).toString(), Alt: sensor_dat[5], Sm: sensor_dat[6], Lg: sensor_dat[7], Temp: sensor_dat[8], C3H8: sensor_dat[9], CH4: sensor_dat[10], CO: sensor_dat[11], H2S: sensor_dat[12]});
                new_dat = 0;
            }
            else {
                io.emit('null data', 0);
            }
        },1000);
    }
    users++;
});


http.listen(3000, function(){
    console.log('Web server Active listening on *:3000');
});

var ORG = 'h22mg7';
var TYPE = 'Air_POD_v2';
var ID = '03';
var AUTHTOKEN = 'w14DV!h7JpGCalAB2e';

//Uses mqtt.js, see package.json. More info at:
//https://www.npmjs.com/package/mqtt
var mqtt    = require('mqtt');

var PROTOCOL = 'mqtt';
var BROKER = ORG + '.messaging.internetofthings.ibmcloud.com';
var PORT = 1883;

//Create the url string
var URL = PROTOCOL + '://' + BROKER;
URL += ':' + PORT;
//URL is e.g. 'mqtt://xrxlila.messaging.internetofthings.ibmcloud.com:1883'

var CLIENTID= 'd:' + ORG;
CLIENTID += ':' + TYPE;
CLIENTID += ':' + ID;
//CLIENTID -s e.g. d:xrxila:edison-air:784b87a801e9

var AUTHMETHOD = 'use-token-auth';

var client  = mqtt.connect(URL, { clientId: CLIENTID, username: AUTHMETHOD, password: AUTHTOKEN });

var TOPIC = 'iot-2/evt/status/fmt/json';
var message;

client.on('connect', function () {
    setInterval(function(){
        if(sensor_dat !== undefined && sensor_dat.length === 13)
        {
            message = { "sensor data" : { "Time" : sensor_dat[0], "Lat" : sensor_dat[1], "Lat_m" : sensor_dat[2], "Lon" : sensor_dat[3], "Lon_m" : sensor_dat[4], "Alt" : sensor_dat[5], "Sm" : sensor_dat[6], "Lg" : sensor_dat[7], "Temp" : sensor_dat[8], "C3H8" : sensor_dat[9], "CH4" : sensor_dat[10], "CO" : sensor_dat[11], "H2S" : sensor_dat[12]}};//Payload is JSON}};
            client.publish(TOPIC, JSON.stringify(message));
        }
    }, 2000);//Keeps publishing every 2000 milliseconds.
});


u = new mraa.Uart(0); //Default
//Name:     UART1, the general-purpose TTL-level port (Arduino shield compatibility)
//Location: Pins 0 (RX) and 1 (TX) on the Arduino shield interface headers or the UART slot on the Grove Starter Kit Base Shield
var serialPath = u.getDevicePath(); //Default general purpose port "/dev/ttyMFD1" - Intel(R) Edison; "/dev/ttyS0" - Intel(R) Galileo

//Name:     “Multi-gadget” or “Firmware Programming” or "Arduino Serial console" or "OTG" port
//Location: USB-micro connector near center of Arduino board.  - Intel(R) Edison
//var serialPath = "/dev/ttyGS0";

//Name:     UART2
//Location: USB-micro connector near edge of Arduino board. - Intel(R) Edison
//var serialPath = "/dev/ttyMFD2";


//Serialport NodeJS module declared in package.json
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;
var sensor_dat;
var new_dat = 0;

var port = new SerialPort(serialPath, {
    baudrate: 9600,
    parser: serialport.parsers.readline('\n')
});
port.on("open",function() {
    setInterval(function(){
        if (new_dat === 0)
        {
            sensor_dat = undefined;
        }
    },3000);
    port.on("data", function(data) { //Read available data from serial port
        sensor_dat = data.split(",");
        new_dat = 1;
    });
});
