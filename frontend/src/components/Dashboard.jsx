// src/components/Dashboard.jsx
import React, { useEffect, useState } from "react";
import io from "socket.io-client";

const Dashboard = () => {
  const [machines, setMachines] = useState([
    { id: 1, name: "Machine 1", status: false, img: "/machine1.jpg" },
    { id: 2, name: "Machine 2", status: false, img: "/machine2.jpg" },
    { id: 3, name: "Machine 3", status: true, img: "/machine3.jpg" },
    { id: 4, name: "Machine 4", status: false, img: "/machine4.jpg" },
  ]);
  
  useEffect(() => {
    const socket = io("http://localhost:3000");
  
    socket.on("statusUpdate", (data) => {
      console.log("Received status update:", data);
  
      // data.vibrationSensors = [1, 0, 1, 0]
      const updatedStatuses = data.vibrationSensors;
  
      // Update the machines state based on vibration array
      setMachines((prevMachines) =>
        prevMachines.map((machine, index) => ({
          ...machine,
          status: updatedStatuses[index] === 1,
        }))
      );
    });
  
    return () => socket.disconnect();
  }, []);
  

  return (
    <section id="home" className="flex-1 py-8">
      <div className="container mx-auto px-4">
        <h1 className="text-3xl font-bold text-center mb-6">
          Washing Machine Dashboard
        </h1>
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6 justify-items-center">
          {machines.map((machine) => (
            <div key={machine.id} className="card w-80 bg-base-100 shadow-xl">
              <figure>
                <img
                  src={machine.img}
                  alt={machine.name}
                  className="h-48 w-full object-cover"
                />
              </figure>
              <div className="card-body items-center text-center">
                <h2 className="card-title">{machine.name}</h2>
                <button
                  className={`btn ${
                    machine.status ? "btn-error" : "btn-success"
                  }`}
                >
                  {machine.status ? "Occupied" : "Available"}
                </button>
              </div>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
};

export default Dashboard;