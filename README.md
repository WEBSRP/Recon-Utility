# Recon Utility v1.1

A lightweight C++ reconnaissance utility built to understand how low-level network scanners work internally using socket programming and structured input handling.

## Overview

Recon Utility is a personal systems programming and cybersecurity learning project focused on understanding how reconnaissance tools perform:

* target validation
* port validation
* TCP connection testing
* banner grabbing
* basic multi-port scanning logic

The objective is not to replace professional scanners, but to build core networking logic manually and understand what happens behind tools like Nmap.

---

## Features in v1.1

### Target Validation

* Accepts IPv4 input only
* Rejects alphabetic characters
* Rejects special characters
* Validates 4 octets
* Checks octet range (0–255)

### Port Validation

* Accepts valid numeric ports only
* Rejects invalid input
* Range: 1–65535

### Scan Modes

* Single Port Scan
* Port Range Scan

User can now choose scan mode before scanning.

### TCP Connection Check

* Creates socket using POSIX socket APIs
* Attempts connection to target host and selected port
* Reports connection success/failure

### Banner Grabbing

On successful connection, reads available service banner.

Example:

SSH-2.0-OpenSSH_10.0
---

## Project Structure

main.cpp
Program flow, mode selection, scan routing

scanner.h
Function declarations

scanner.cpp
Validation logic, socket handling, banner grabbing, range scanning

---

## Build

```bash
g++ main.cpp scanner.cpp -o recon
```

---

## Run

```bash
./recon
```

---

## Example Usage

### Single Port Scan

```bash
Enter the target: 127.0.0.1
Choose Mode
1.Single port Scan
2.Range of port Scan

Enter Port :22
```

### Range Scan

```bash
Enter the target: 127.0.0.1
Choose Mode
1.Single port Scan
2.Range of port Scan

Enter Starting Port:
20
Enter Ending Port:
30
```

---

## Current Limitations

* Sequential scanning only
* No timeout handling
* No DNS resolution
* Static protocol hints
* Banner depends on open service response

---

## Planned Improvements (v1.2)

* Connection timeout control
* Better service detection
* Protocol inference from banner
* Faster scan loop
* Cleaner output formatting
* Modular scanner class design

---

## Purpose

This project is built as part of practical cybersecurity learning:

**Best way to understand recon tools is building one.**

The project focuses on coding logic first, then improving technical depth step by step.

---

## Version

v1.1
