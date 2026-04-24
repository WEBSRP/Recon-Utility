# 🔍 Recon Utility (N-SCAN)

A lightweight C++ network reconnaissance utility built to understand how real scanners work internally — from raw socket connections to service fingerprinting.

This project is being developed as a personal low-level networking learning project, with the goal of manually building features that tools like Nmap perform automatically.

---

# ⚙️ Current Features

## ✅ Port Scanning
- Single port scan
- Range-based port scan
- Open / Closed / Filtered state detection

## ✅ Risk Level Classification
- Basic risk categorization based on port type

## ✅ HTTP Banner Grabbing (v1.5)
- Sends manual HTTP HEAD request
- Reads server response headers
- Extracts server banner information

Example:

Server: Apache/2.4.41 (Ubuntu)

---

# 🧠 What This Project Is Teaching

This project is focused on understanding:

- TCP socket creation
- Manual connect() handling
- Timeout tuning
- recv() / send() behavior
- Service response parsing
- Application-layer protocol interaction

Instead of using libraries that hide networking internals, the logic is built manually to understand every stage.

---

# 🛠 Project Structure

main.cpp        → UI + execution flow  
scanner.cpp     → Port scanning logic  
scanner.h       → Scanner declarations  
banner.cpp      → HTTP banner grabbing logic  
banner.h        → Banner function declarations  

---

# 🚀 Current Working Flow

1. Target input  
2. Port selection  
3. TCP connection attempt  
4. Port state detection  
5. HTTP banner extraction (for HTTP services)

---

# 📌 Sample Output

80    OPEN    Connected    Server: Apache/2.4.41 (Ubuntu)

---

# ⚡ Build & Run

## Compile

g++ main.cpp scanner.cpp banner.cpp -o nscan

## Run

./nscan

---

# 🧪 Current Focus

Fine-tuning service detection logic and improving banner extraction reliability.

Upcoming improvements:

- HTTPS banner grabbing 🔐  
- Better service-based banner detection 🌐  
- Smarter port classification 📊  
- Cleaner modular architecture 🧩  

---

# 📂 GitHub

If you check the project, feedback is welcome ⭐

---

# 🧰 Built With

- C++
- Linux sockets
- POSIX networking APIs

---

# 📖 Purpose

This is not being built as a college submission or internship project.

It is a hands-on learning project to deeply understand how scanners actually work internally.

---

# ⭐ Feedback Welcome

If you test it, suggest improvements, or spot design issues, feel free to share feedback.
