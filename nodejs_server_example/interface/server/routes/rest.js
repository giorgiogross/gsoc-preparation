var express = require('express');
var fs = require('fs');
var router = express.Router();

/* executed on all requests */
router.use(function(req, res, next) {
    console.log("There was a new request");

    // pass request on to our api
    next();
});

/* GET intro */
router.get('/', function(req, res, next) {
    res.send('This is a rest api');
});

/* GET all serial information data */
router.get('/getOverview', function(req, res, next) {
    fs.readFile( "../" + "data.json", 'utf8', function (err, data) {
        console.log( data );
        res.end( data );
    });
});

/* GET one item */
router.get('/getOverview/:port_name', function (req, res, next) {
    fs.readFile( "../data.json", 'utf8', function (err, data) {
        data = JSON.parse(data);
        console.log(req.params.port_name);
        res.json(data[req.params.port_name]);
    });
});

/* PUT payload */
router.post('/putPayload', function(req, res, next) {

    fs.readFile( "../data.json", 'utf8', function (err, data) {
        data = JSON.parse(data);
        data[req.body.name].payload = req.body.payload;
        console.log( req.body.name );
        console.log( req.body.payload );
        res.write( JSON.stringify(data) );
        res.write( "#suffix_to_demonstrate_how_cool_this_is" );
        res.end();
        // res.json({result: "OK"});
        if(!req.body.override) return;

        // save modifications
        fs.writeFile("../data_written.json", JSON.stringify(data), function(err) {
            if(err) throw err;
            console.log("File written");
        })
    });
});

module.exports = router;