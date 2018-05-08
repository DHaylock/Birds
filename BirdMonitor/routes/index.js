const express = require('express');
const router = express.Router();
const {Pool, Client} = require('pg');
const path = require('path');
const connectionString = connectionString || 'postgres://***REMOVED***:***REMOVED***@***REMOVED***:5432/***REMOVED***';
const nodemailer = require('nodemailer');
const dateTime = require('node-datetime');
var copyTo = require('pg-copy-streams').to;


const pool = new Pool({
    user: '***REMOVED***',
    host: '***REMOVED***',
    database: '***REMOVED***',
    password: '***REMOVED***',
    port: 5432,
    connectionString: connectionString
});

//----------------------------------------------------------------
// * Email the Log to the Owner
//----------------------------------------------------------------
function emailCsvToOwner(address) {
    console.log("Starting to Email");

    var dt = dateTime.create();
    var formatted = dt.format('Y-m-d');
    var directory = __dirname + "/"+formatted+".csv";

    var send = require('gmail-send') ({
        user: "***REMOVED***",
        pass: "***REMOVED***",
        to: "***REMOVED***",
        subject: "New Info",
        text:"Here is Yesterday's Data",
    });


    send({    
        files:[directory]
    },function(err,res) {
        console.log(err,res);
    });
}

//----------------------------------------------------------------
// * Check the Size of the Database
//----------------------------------------------------------------
function truncateTable() {
    console.log("Cleaning DB");

    pool.query('TRUNCATE TABLE logs', (err,result) => {
        if(err) {
            return console.log({failed: err});
        }

        return console.log({success: "Truncated Table"});
        pool.end()
    }); 
}

//----------------------------------------------------------------
// * Post Stuff to the Server
//----------------------------------------------------------------
router.post('/api/v1/downloaddata', (req,res,next) => {
    
    var dt = dateTime.create();
    var formatted = dt.format('Y-m-d');
    var directory = __dirname + "/"+formatted+".csv";
    
    pool.query( "\copy logs TO '"+directory+"' CSV HEADER", (err,result) => {
        if(err) {
            console.log(err);
            return res.json({failed: err})
        }
        
        console.log(result + " Downloaded File");
        setImmediate(emailCsvToOwner,1500,"");
        setTimeout(truncateTable,1500);
        return res.json({success: "Downloaded"});
        pool.end()
    });
});

//----------------------------------------------------------------
// * Post Stuff to the Server
//----------------------------------------------------------------
router.post('/api/v1/log', (req,res,next) => {
     
    const results = [];
    const data = { 
      where: req.body.where, 
      when: req.body.when,
      event: req.body.event, 
      volume: req.body.volume 
    };

    const query = {
        text: 'INSERT INTO logs("event","location","volume") values($1,$2,$3)',
        values: [data.event,data.where,data.volume]
    };

    pool.query(query,(err,result) => {
        if(err) {
            console.log(err);
            return res.json({failed: err});
        }

        return res.json({success: "Inserted"});
        pool.end();
    });
});

//----------------------------------------------------------------
// * Get the Numbers from the Server
//----------------------------------------------------------------
router.get('/api/v1/get', (req,res,next) => {
    const results = [];
    const data = { 
      where: req.query.where
    };

    const query = {
        text: "SELECT volume, to_char(created_at,'HH24:MI:SS') as created_at,event FROM logs WHERE location = $1 AND DATE(created_at) = DATE(NOW())",
        values: [data.where]
    };

    pool.query(query)
    .then(result => {
        return res.json(result.rows);
        pool.end()
    })
    .catch(e => console.log(e));
});

//----------------------------------------------------------------
// * Get the Homepage
//----------------------------------------------------------------
router.get('/',(req,res,next) => {
    res.sendFile("index.html");
});

module.exports = router;
