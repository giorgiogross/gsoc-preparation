var express = require('express');
var router = express.Router();

/* GET second_page page. */
router.get('/', function(req, res, next) {
    res.render('second_page', { title: 'Second Page' });
});

module.exports = router;
