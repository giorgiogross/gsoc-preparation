var express = require('express');
var router = express.Router();

// require our custom cpp addons
var myAddon = require('../../build/Release/myaddon');
var c_wrapper = require('../../build/Release/c_wrapper_addon');

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
/*c_wrapper.makeCallback(function(msg){
    console.log(msg);
});*/


module.exports = router;
