/**
 * Created by chotoxautinh on 6/17/17.
 */
var wpi = require('../index');

try {
    wpi.setup();
    console.log('OK');
} catch (err) {
    console.error('Err', err);
}