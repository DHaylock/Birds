const express = require('express');
const router = express.Router();
const {Pool, Client} = require('pg');
const path = require('path');
const connectionString = connectionString || 'postgres://localhost:5432/david';
const nodemailer = require('nodemailer');
const dateTime = require('node-datetime');
var copyTo = require('pg-copy-streams').to;


const pool = new Pool({
    // user: '',
    // host: '',
    // database: '',
    // password: '',
    // port: 0,
    connectionString: connectionString
});

//----------------------------------------------------------------
// * Email the Log to the Owner
//----------------------------------------------------------------
function emailCsvToOwner(address) {
    console.log("Starting to Email");

    nodemailer.createTestAccount((err,account) => {

        if(err) {
            console.error('Failed to create a testing account. ' + err.message);
            return process.exit(1);
        }

        console.log('Credentials obtained, sending message...');

        var dt = dateTime.create();
        var formatted = dt.format('Y-m-d H:M:S');

        let transporter = nodemailer.createTransport( {
            host: account.smtp.host,
            port: account.smtp.port,
            secure: account.smtp.secure,
            auth: {
                user: account.user,
                pass: account.pass
            }
        });

        var dt = dateTime.create();
        var formatted = dt.format('Y-m-d');
        var directory = __dirname + "/"+formatted+".csv";

        let message = {
            from: 'Monitorer <me@davidhaylock.co.uk>',
            to: 'David  <***REMOVED***>',
            //to: 'Angela <angeladaviesartist@gmail.com>',
            subject: formatted + " Data",
            text: "Here is yesterday's data.",
            attachments: [{
                path: directory
            }]
        };
        
        transporter.sendMail(message, (err, info) => {
            if(err) {
                console.log('Error occurred. ' + err.message);
                return process.exit(1);
            }
            console.log('Message sent: %s', info.messageId);
            console.log('Preview URL: %s', nodemailer.getTestMessageUrl(info));
        });
    });
}

//----------------------------------------------------------------
// * Check the Size of the Database
//----------------------------------------------------------------
function truncateTable() {

    console.log("Cleaning DB");

    const truncate = pool.query('TRUNCATE TABLE logs')
    .then( res => {
        console.log("Success");
        return "Cleaned";
    })
    .catch(e => console.log(e.stack))
    pool.end()
}

//----------------------------------------------------------------
// * Post Stuff to the Server
//----------------------------------------------------------------
router.post('/api/v1/downloaddata', (req,res,next) => {
    
    var dt = dateTime.create();
    var formatted = dt.format('Y-m-d');
    var directory = __dirname + "/"+formatted+".csv";
    
    pool.query( "\copy logs TO '"+directory+"' CSV HEADER" )
    .then( res => {
        console.log("Downloaded File");
        setImmediate(emailCsvToOwner,1500,"");
        setTimeout(truncateTable,1500);
        pool.end()
    })
    .catch( e => console.log(e) ); 
    
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

    pool.query(query, (err,res) => {
        if(err) {
            console.log(err);
            return err;
        }
        
        pool.end();
        console.log(res);
        return res;
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
        console.log(result.rows);
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
