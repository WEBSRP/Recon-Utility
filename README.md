# Recon Utility v1.0

A lightweight C++ reconnaissance utility built as an early systems programming and networking project.

## Overview

Recon Utility performs basic target validation and TCP connectivity checks against a given IPv4 address and port.
It is designed to demonstrate:

* Input sanitization
* IPv4 validation
* Port validation
* Socket programming in C++
* Banner grabbing
* Basic service awareness

## Features

### Input Validation

* Accepts only valid IPv4 format
* Rejects alphabetic input
* Rejects special characters
* Verifies exactly 4 octets
* Checks each octet is within 0–255

### Port Validation

* Accepts only valid numeric ports
* Rejects invalid characters
* Valid range: 1–65535

### TCP Connection

* Creates TCP socket using POSIX socket APIs
* Attempts connection to target host and port
* Detects success or failure

### Banner Grabbing

* Reads available banner after successful connection
* Example:
  SSH-2.0-OpenSSH_10.0

### Risk Classification

Currently basic static classification for common ports:

* 21 → FTP
* 22 → SSH
* 23 → Telnet
* 80 → HTTP
* 443 → HTTPS

## Project Structure

main.cpp
Program flow and control logic

scanner.h
Function declarations

scanner.cpp
Input handling, validation, socket connection, banner grabbing

## Build

```bash
g++ main.cpp scanner.cpp -o recon
```

## Run

```bash
./recon
```

## Example

```bash
Enter the target: 127.0.0.1
Enter Port :22

Target:127.0.0.1
Port:22
Connection successful
Banner: SSH-2.0-OpenSSH_10.0
```

## Current Limitations

* Single port scan only
* No timeout control
* No DNS resolution
* No parallel scanning
* Basic service detection only

## Planned Improvements (v1.1)

* Connection timeout handling
* Dynamic banner-based protocol detection
* Multi-port scanning
* Better error handling
* Modular scanner class

## Purpose

This project is part of my systems programming and cybersecurity learning journey, focused on understanding low-level networking rather than replacing professional tools.

## Version

v1.0
