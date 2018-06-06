'use strict';

var express = require('express');
var request = require('request');
var app = express();
var http = require('http').Server(app);

var clientFromConnectionString = require('azure-iot-device-mqtt').clientFromConnectionString;
var Message = require('azure-iot-device').Message;

var connectionString = 'HostName={youriothostname};DeviceId=myFirstNodeDevice;SharedAccessKey={yourdevicekey}';
var mydeviceId = 'contiki-ng-01';
var client = clientFromConnectionString(connectionString);

app.get('/', function(req, res){
    res.send('WebSense Azure Cloud');
});

http.listen(3000, function(){
    console.log('listening on *:3000');
    console.log('websense azure cloud was started');
});


function printResultFor(op) {
    return function printResult(err, res) {
      if (err) console.log(op + ' error: ' + err.toString());
      if (res) console.log(op + ' status: ' + res.constructor.name);
    };
  }

var connectCallback = function (err) {
    if (err) {
        console.log('Could not connect: ' + err);
    } else {
        console.log('Client connected');

        // Create a message and send it to the IoT Hub every second
        setInterval(function(){

            request.get('http://[fd00::212:4b00:797:6083]/',function(err,res,body){
                if(err){
                    console.log(err);
                    return;
                }
                var obj = JSON.parse(body);
                console.log(obj);

                var temperature = obj.temp;
                var humidity = obj.hum;            
                var data = JSON.stringify({ deviceId: mydeviceId, temperature: temperature, humidity: humidity });
                var message = new Message(data);
                message.properties.add('temperatureAlert', (temperature > 30) ? 'true' : 'false');
                console.log("Sending message: " + message.getData());
                client.sendEvent(message, printResultFor('send'));

            });            
        }, 3000);
    }
};

client.open(connectCallback);
console.log('Contiki-NG Azure Middleware started.');