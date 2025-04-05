// src/components/Footer.jsx
import React from "react";

const Footer = () => {
  return (
    <footer id="contact" className="footer bg-base-200 text-base-content p-8">
      <div className="container mx-auto px-4 flex flex-col items-center gap-8">
        {/* Contact Us Section */}
        <div className="w-full text-center">
          <h2 className="text-5xl font-bold mt-8 mb-6 bg-gradient-to-r from-red-400 via-orange-400 via-yellow-400 via-green-400 via-blue-400 via-indigo-400 to-violet-400 bg-clip-text text-transparent">
            Contact Us
          </h2>
          <div className="flex flex-col md:flex-row justify-center items-center gap-40"> {/* Increased gap to 32 (8rem) */}
            {/* Person 1 */}
            <div className="flex flex-col items-center p-6"> {/* Added padding */}
              <span className="font-semibold text-lg">Shyam</span>
              <span className="text-sm">shyam14027@gmail.com</span>
              <span className="text-sm">7004995201</span>
            </div>
            {/* Person 2 */}
            <div className="flex flex-col items-center p-6"> {/* Added padding */}
              <span className="font-semibold text-lg">Chetan</span>
              <span className="text-sm">chetansharma777555@gmail.com</span>
              <span className="text-sm">7668751288</span>
            </div>
            {/* Person 3 */}
            <div className="flex flex-col items-center p-6"> {/* Added padding */}
              <span className="font-semibold text-lg">Alok</span>
              <span className="text-sm">aloksingh15122004@gmail.com</span>
              <span className="text-sm">7905780360</span>
            </div>
          </div>
        </div>

        {/* Copyright Section */}
        <div className="w-full text-center border-t border-base-300 pt-6">
          <p className="text-sm">
            © {new Date().getFullYear()} MyWashing. All rights reserved.
          </p>
        </div>
      </div>
    </footer>
  );
};

export default Footer;