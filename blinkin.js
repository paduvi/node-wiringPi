/**
 * Created by chotoxautinh on 6/17/17.
 */
var wiringpi = require('./index');

wiringpi.wiring_pi_setup();

wiringpi.pin_mode(7, wiringpi.OUTPUT);

var HIGH = wiringpi.HIGH;
var LOW = wiringpi.LOW;

var isLedOn = 0;

setInterval(function () {
    wiringpi.digital_write(7, isLedOn ? HIGH : LOW);
    isLedOn = ( isLedOn + 1 ) % 2;
}, 125);
