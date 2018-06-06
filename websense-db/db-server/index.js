var express = require('express');
var request = require('request');
var app = express();
var http = require('http').Server(app);

var mysql      = require('mysql');
var connection = mysql.createConnection({
  host     : 'localhost',
  user     : '<user>',
  password : '<db-password>',
  database : 'contiki-ng-db'
});

connection.connect();
app.use(express.static('public'));

app.get('/', function(req, res){
    res.send('WebSense DB');
});

http.listen(3000, function(){
    console.log('listening on *:3000');
    console.log('websense db was started');
});

var dataPusher = setInterval(function () {

    request.get('http://[fd00::212:4b00:797:6083]/',function(err,res,body){
        if(err){
            console.log(err);
            return;
        }
        var obj = JSON.parse(body);
        console.log(obj);

        connection.query({
            sql: 'INSERT INTO sensor(sensor_name,sensor_val,created) values(?,?,now())',
            timeout: 40000, // 40s
            values: [obj.temp,obj.hum]
        }, function (error, results, fields) {
            if(error){
                console.log(err);
                return;
            }
            console.log('inserted data to MySQL');
        });
    });

    
}, 5000);