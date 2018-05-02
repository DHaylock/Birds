const pg = require('pg');
const connectionString = connectionString || 'postgres://localhost:5432/david';

const client = new pg.Client(connectionString);
client.connect();
const query = client.query('CREATE TABLE logs("id" SERIAL PRIMARY KEY, "volume" VARCHAR(25) NULL, "where" VARCHAR(255) not null,"when" VARCHAR(255) not null, "event" VARCHAR(255) not null)');
query.on('end', () => { console.log("Hello World"); client.end(); });
