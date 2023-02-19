// This script is a simplified version of the test.js in the flower power library below.
// The script is not standalone, it requires the libraries to talk to the Parrot device.
// Original repository link: https://github.com/sandeepmistry/node-flower-power

var async = require('async');

var FlowerPower = require('./index');

var hasCalibratedData = false;

FlowerPower.discover(function(flowerPower) {
  async.series([
    //console.log('Process started');
    function(callback) {
      flowerPower.on('disconnect', function() {
        console.log('disconnected!');
        process.exit(0);
      });

      flowerPower.on('soilElectricalConductivityChange', function(soilElectricalConductivity) {
         console.log('soil electrical conductivity = ' + soilElectricalConductivity.toFixed(2));
      });

      flowerPower.on('soilTemperatureChange', function(temperature) {
        console.log('soil temperature = ' + temperature.toFixed(2) + '°C');
      });

      flowerPower.on('calibratedAirTemperatureChange', function(temperature) {
        console.log('calibrated air temperature = ' + temperature.toFixed(2) + '°C');
      });

      flowerPower.on('calibratedEcbChange', function(ecb) {
        console.log('calibrated ECB = ' + ecb.toFixed(2) + ' dS/m');
      });

      flowerPower.on('calibratedEcPorousChange', function(ecPorous) {
        console.log('calibrated EC porous = ' + ecPorous.toFixed(2)+ ' dS/m');
      });

      console.log('connectAndSetup');
      flowerPower.connectAndSetup(callback); //Connecting to the flower power
    },
    function(callback) {
        flowerPower.readFirmwareRevision(function(error, firmwareRevision) {
          var version = firmwareRevision.split('_')[1].split('-')[1];
          hasCalibratedData = (version >= '1.1.0');
          callback();
        }); 
    },
    function(callback) {
      flowerPower.readSoilTemperature(function(error, temperature) {
        console.log('water temperature = ' + temperature.toFixed(2) + '°C');

        callback();
      });
    },
    function(callback) {
      if (hasCalibratedData) {
        async.series([
          function(callback) {
            flowerPower.readCalibratedAirTemperature(function(error, temperature) {
              console.log('calibrated air temperature = ' + temperature.toFixed(2) + '°C');
              callback();
            });
          },
          function(callback) {
            //console.log('readCalibratedEcb');
            flowerPower.readCalibratedEcb(function(error, ecb) {
              console.log('calibrated ECB = ' + ecb.toFixed(2) + ' dS/m');
              callback();
            });
          },
          function(callback) {
            //console.log('readCalibratedEcPorous');
            flowerPower.readCalibratedEcPorous(function(error, ecPorous) {
              console.log('calibrated EC porous = ' + ecPorous.toFixed(2) + ' dS/m');
              callback();
            });
          },
          function() {
            callback();
          }
        ]);
      } else {
        callback();
      }
    },
    function(callback) {
      //console.log('ledPulse');
      flowerPower.ledPulse(callback);
    },
    //function(callback) {
      //console.log('delay');
      //setTimeout(callback, 1000);
    //},
    function(callback) {
      //console.log('ledOff');
      flowerPower.ledOff(callback);
    },
    function(callback) {
      //console.log('disconnect');
      flowerPower.disconnect(callback);
    }
  ]);
});
