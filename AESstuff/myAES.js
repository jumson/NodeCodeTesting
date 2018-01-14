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
    var d = c.decrypt(msg, pass)
    return d.toString
}

// export the module
module.exports = {
    encpt: encpt,
    decpt: decpt
};