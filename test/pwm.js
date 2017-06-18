/**
 * Created by chotoxautinh on 6/18/17.
 */
const wpi = require('../index');

wpi.setup();

wpi.pinMode(33, wpi.mode.PWM_OUTPUT);
wpi.pinMode(1, wpi.mode.INPUT);

const {HIGH} = wpi.value;

console.log('Started!');

var value = 0;

setInterval(function () {
    const isLedOn = wpi.digitalRead(1);
    if (isLedOn == HIGH) {
        value = (value + 1024 / 128) % 1024;
    }
    wpi.pwmWrite(33, value);
    console.log('Value', value);
}, 125);