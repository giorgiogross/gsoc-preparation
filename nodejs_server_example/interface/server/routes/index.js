var express = require('express');
var router = express.Router();

// require our custom cpp addons    todo uncomment the proper folder!
var myAddon = require('../../gyp_linux/build/Release/myaddon');
var c_wrapper = require('../../gyp_linux/build/Release/c_wrapper_addon');
/*var myAddon = require('../../gyp_mac/build/Release/myaddon');
var c_wrapper = require('../../gyp_mac/build/Release/c_wrapper_addon');*/

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', {
      title: 'Express',
      addon: myAddon
  });
});

// call hello.cc functions written in C++
console.log(myAddon.hello());

// call c_wrapper.cc functions which in turn are delegated to C functions
c_wrapper.printHello();
console.log(c_wrapper.add(3, 2));
console.log(c_wrapper.mul2(2));
console.log(c_wrapper.makeCallback()); // C++ function is the callback function
c_wrapper.makeAsyncCallback(function(msg){ // this is the callback function
    console.log(msg);
});


module.exports = router;
