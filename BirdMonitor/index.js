const express = require('express');
const router = express.Router();
const pg = require('pg');
const path = requre('path');
const connectionString = connectionString || 'postgres://localhost:5432/david';

router.post('/api/v1/log', (req,res,next) => {
    const results = [];
    const data = { where: req.body.where, when: req.body.when, event: req.body.event, volume: req.body.volume };

    pg.connect(connectionString, (err, client, done) => {
        if(err) {
            done();
            console.log(err);
            return res.status(500).json({success: false, data: err});
        }

        client.query('INSERT INTO logs(event,when,where,volume) values($1,$2,$3,$4)',
        [data.event,data.when,data.where,data.volume]);

        const query = client.query('SELECT * FROM logs ORDER BY id ASC');

        query.on('row',(row) => {
            results.push(row);
        });
        
        query.on('end', () => {
            done();
            return res.json(results);
        });
    });
});

