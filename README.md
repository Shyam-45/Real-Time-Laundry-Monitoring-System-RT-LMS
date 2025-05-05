# Real‑Time‑Laundry‑Monitoring‑System


## Project Overview

This project monitors and displays the availability of washing machines in real time. The system receives live status updates from an ESP8266‑based microcontroller, which sends data to the backend. The frontend dynamically updates the UI based on the received data.

---

## Tech Stack

**Frontend (React.js)**  
- **React.js** – For building the user interface  
- **Tailwind CSS** – For styling and responsiveness  
- **Socket.io‑client** – For real‑time WebSocket communication  

**Backend (Node.js & Express.js)**  
- **Express.js** – For handling API requests  
- **Socket.io** – For real‑time communication  

**Hardware**  
- **ESP8266** – Sends machine status updates to the server via HTTP POST requests.

---

## Features

- **Real‑Time Updates:** Instantaneous machine status updates using WebSockets  
- **Interactive Dashboard:** Easily view available and occupied machines  
- **Responsive Design:** Works seamlessly across desktop and mobile devices  

---

## Installation & Setup

Follow these steps to run the project locally.

1. **Clone the Repository**  
   ```bash
   git clone https://github.com/Shyam-45/Real-Time-Laundry-Monitoring-System-RT-LMS.git
   cd Real-Time-Laundry-Monitoring-System-RT-LMS

2. **Backend Setup**  
   ```bash
   cd backend
   npm install           # Install dependencies
   nodemon server.js     # Start the backend server

3. **Frontend Setup**  
   ```bash
   cd frontend
   npm install           # Install dependencies
   npm run dev           # Start the React app

## Real‑Time Communication Workflow

1. The ESP8266 sends HTTP POST requests with machine status to the backend.  
2. The Node.js server receives this data and broadcasts it via WebSockets to connected frontend clients.  
3. The React frontend listens for statusUpdate events and updates the UI instantly.
