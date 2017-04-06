var express = require('express');
var router = express.Router();

var vd = require('../videodata.json');

/* GET second_page page. */
router.get('/', function(req, res, next) {
    res.render('second_page', {
        title: 'Second Page',
        base: 'http://www.thenewboston.com/videos_food.php?=cat',
        videodata: vd
    });
});

module.exports = router;
