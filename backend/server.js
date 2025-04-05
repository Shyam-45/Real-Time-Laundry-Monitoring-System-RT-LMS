// server.js
const express = require('express');
const bodyParser = require('body-parser');
const http = require('http');
const socketIo = require('socket.io');
const cors = require('cors');

const app = express();

// Middleware for parsing JSON and enabling CORS
app.use(bodyParser.json());
app.use(cors());

// Create HTTP server and bind Socket.io
const server = http.createServer(app);
const io = socketIo(server, {
  cors: { origin: '*' }
});

// API endpoint to receive data from the ESP8266
app.post('/api/status', (req, res) => {
  const statusData = req.body;
  console.log("Received data:", statusData);
  
  // Immediately broadcast the data via WebSocket to connected clients
  io.emit('statusUpdate', statusData);
  
  // Respond with a success message
  res.status(200).json({ message: 'Status received' });
});

// Optional GET route for testing server availability
app.get('/', (req, res) => {
  res.send('Washing Machine Status Server is running');
});

// Start the server on port 3000
const PORT = 3000;
server.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
