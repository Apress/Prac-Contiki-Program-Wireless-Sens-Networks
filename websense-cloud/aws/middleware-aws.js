var awsIot = require('aws-iot-device-sdk');
var express = require('express');
var request = require('request');
var app = express();
var http = require('http').Server(app);

var device = awsIot.device({
  keyPath: 'certs/private.pem.key',
  certPath: 'certs/certificate.pem.crt',
    caPath: 'certs/root-CA.pem',
      host: '<host>.iot.<region>.amazonaws.com',
  clientId: 'contiki-ng',
    region: '<region>'
 });

var isSubscribe = true;

app.get('/', function(req, res){
    res.send('WebSense Azure Cloud');
});

http.listen(3000, function(){
    console.log('listening on *:3000');
    console.log('websense aws cloud was started');
});

device
.on('connect', function() {
  console.log('connected to AWS IoT.');  
  
  // optional to subscribe
  if(isSubscribe)
    device.subscribe('contiki-ng-sensor');
  
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
        mydeviceId = 'fd00::212:4b00:797:6083';      
        var data = JSON.stringify({ deviceId: mydeviceId, temperature: temperature, humidity: humidity });
        device.publish('contiki-ng-sensor', data);
        console.log('sent: ', JSON.stringify(data));

    });            
  }, 3000);


});

// optional to subscribe
device
   .on('message', function(topic, payload) {
     console.log('recv: ', topic, payload.toString());
});

console.log('Contiki-NG AWS Middleware started.');