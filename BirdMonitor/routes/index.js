const express = require('express');
const router = express.Router();
const pg = require('pg');
const path = require('path');
const connectionString = connectionString || 'postgres://localhost:5432/david';

router.post('/api/v1/log', (req,res,next) => {
    const results = [];
    const data = { 
      where: req.body.where, 
      when: req.body.when,
      event: req.body.event, 
      volume: req.body.volume 
    };

    pg.connect(connectionString, (err, client, done) => {
        if(err) {
            done();
            console.log(err);
            return res.status(500).json({success: false, data: err});
        }

        const query = client.query('INSERT INTO logs("event","location","volume") values($1,$2,$3)',
        [data.event,data.where,data.volume]);

        query.on('end', () => {
          done();
          return res.json({ success: "Inserted" });
        });
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

    console.log(data);

    pg.connect(connectionString, (err, client, done) => {
        if(err) {
            done();
            console.log(err);
            return res.status(500).json({success: false, data: err});
        }

        const query = client.query("SELECT volume, to_char(created_at,'HH24:MI:SS') as created_at,event FROM logs WHERE location = $1 AND DATE(created_at) = DATE(NOW())",[data.where]);
    
        query.on('row', (row) => {
            results.push(row);
        });

        // After all data is returned, close connection and return results
        query.on('end', function() {
            done();
            return res.json(results);
        });
    });
});

router.get('/',(req,res,next) => {
    res.sendFile("index.html");
});

module.exports = router;
