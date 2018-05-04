const pg = require('pg');
const connectionString = connectionString || 'postgres://localhost:5432/david';

const client = new pg.Client(connectionString);
client.connect();
const query = client.query('CREATE TABLE logs("id" SERIAL PRIMARY KEY, "volume" VARCHAR(25) NULL, "location" VARCHAR(255) not null,"created_at" TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "event" VARCHAR(255) not null)');
query.on('end', () => { console.log("Hello World"); client.end(); });
