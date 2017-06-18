/**
 * Created by chotoxautinh on 6/17/17.
 */
const wpi = require('../index');

wpi.setup();

wpi.pinMode(7, wpi.mode.OUTPUT);

const {HIGH, LOW} = wpi.value;

var isLedOn = 0;

console.log('Started!');

setInterval(function () {
    wpi.digitalWrite(7, isLedOn ? HIGH : LOW);
    console.log('Ping', '-', isLedOn ? 'HIGH' : 'LOW');
    isLedOn = ( isLedOn + 1 ) % 2;
}, 125);
