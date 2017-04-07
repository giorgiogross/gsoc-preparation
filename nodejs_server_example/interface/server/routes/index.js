var express = require('express');
var router = express.Router();

// require our custom cpp addon
var myAddon = require('../../build/Release/myaddon');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', {
      title: 'Express',
      addon: myAddon
  });
});

console.log(myAddon.hello());

module.exports = router;
