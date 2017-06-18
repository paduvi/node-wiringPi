/**
 * Created by chotoxautinh on 6/18/17.
 */
const wpi = require('../index');

wpi.setup();

wpi.pinMode(7, wpi.mode.OUTPUT);
wpi.pinMode(1, wpi.mode.INPUT);

const {HIGH, LOW} = wpi.value;

console.log('Started!');

setInterval(function () {
    const isLedOn = wpi.digitalRead(1);
    wpi.digitalWrite(7, isLedOn);
    console.log('Ping', '-', isLedOn == HIGH ? 'HIGH' : 'LOW');
}, 125);
