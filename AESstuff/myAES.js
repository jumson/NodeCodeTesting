// this little server will simply accept text, a key, and 
// output the encrypted/decrypted text and info
// based on crypto-js: https://github.com/brix/crypto-js
// also following https://primalcortex.wordpress.com/2016/06/17/esp8266-logging-data-in-a-backend-aes-and-crypto-js/
// npm install crypto-js

const c = require('crypto-js').AES;
const encodeing = require('crypto-js').enc.Utf8;

// plain text encrypt
var encpt = function(msg, pass) {
    var e = c.encrypt(msg, pass);
    return e.toString();
}

// plain text decrypt
var decpt = function(msg, pass) {
    var d = c.decrypt(msg, pass);
    return d.toString(encodeing);
}

/* usage example
    const c = require('./myAES.js');
    var msg = 'this is the test message'
    var pass = 'this is the password'
    e = c.encpt(msg,pass)
        //stdout: 'U2FsdGVkX1+3y+67WRaanmii9kY26Q5gViOjj0s91GOHa3/rn0pPcQy7srNkar3R'
    d = c.decpt(e,pass)
        //stdout: 'this is the test message'
*/

// export the module
module.exports = {
    encpt: encpt,
    decpt: decpt
};