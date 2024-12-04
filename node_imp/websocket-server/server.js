const WebSocket = require('ws');

// Create a WebSocket server
const wss = new WebSocket.Server({ port: 8080 });

console.log('WebSocket server is running on ws://localhost:8080');

// Handle connection
wss.on('connection', (ws) => {
    console.log('Client connected');

    // Send a message to the client
    ws.send('Welcome to the WebSocket server!');

    // Listen for messages from the client
    ws.on('message', (message) => {
        console.log('Received:', message);

        // Echo the message back to the client
        ws.send(`Server received: ${message}`);
    });

    // Handle client disconnection
    ws.on('close', () => {
        console.log('Client disconnected');
    });
});
