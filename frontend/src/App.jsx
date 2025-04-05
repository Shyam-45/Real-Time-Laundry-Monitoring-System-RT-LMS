// src/App.jsx
import { useState, useEffect } from "react";
import NavBar from "./components/NavBar";
import Dashboard from "./components/Dashboard";
import Footer from "./components/Footer";

function App() {
  const [theme, setTheme] = useState("dark"); 
  // or "light" if you want the default to be light

  useEffect(() => {
    // When theme changes, set the data-theme on <html>
    document.documentElement.setAttribute("data-theme", theme);
  }, [theme]);

  const toggleTheme = () => {
    setTheme((prev) => (prev === "dark" ? "light" : "dark"));
  };

  return (
    <div className="min-h-screen flex flex-col">
      <NavBar theme={theme} toggleTheme={toggleTheme} />
      <Dashboard />
      <Footer />
    </div>
  );
}

export default App;
