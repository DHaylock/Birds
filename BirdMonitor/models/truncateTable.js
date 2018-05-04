const pg = require('pg');
const connectionString = connectionString || 'postgres://localhost:5432/david';

const client = new pg.Client(connectionString);
client.connect();
const query = client.query('TRUNCATE TABLE logs');
query.on('end', () => { console.log("Truncated Table"); client.end(); });
