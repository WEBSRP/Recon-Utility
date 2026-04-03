# Recon Utility v1.3

A lightweight C++ reconnaissance utility built to understand how low-level network scanners work internally using socket programming, timeout handling, hostname resolution, and structured scan logic.

## Overview

Recon Utility is a personal systems programming and cybersecurity learning project focused on manually building core reconnaissance logic to understand what happens behind professional tools.

Current learning areas covered:

* target validation
* hostname resolution
* port validation
* TCP connection testing
* timeout-based scanning
* banner grabbing
* single-port and range scanning

The objective is not to replace professional scanners like Nmap, but to understand how scanning logic is implemented internally.

---

## Features in v1.3

### Target Validation

* Accepts valid IPv4 addresses
* Rejects malformed IP input
* Validates 4 octets
* Checks each octet range (0–255)

### Hostname Resolution (New in v1.3)

* Accepts domain names such as:

```bash
google.com
scanme.nmap.org
```

* Resolves hostname into IPv4 before scanning using DNS lookup

Example:

```bash
Resolved IP: 142.250.x.x
```

### Port Validation

* Accepts numeric ports only
* Valid range: 1–65535

### Scan Modes

* Single Port Scan
* Port Range Scan

User selects scan mode before execution.

### TCP Connection Scan

* Uses POSIX socket APIs
* Attempts TCP handshake against target port
* Reports open ports accurately

### Timeout Handling

* Socket timeout added for faster and more stable scans
* Prevents hanging on slow/non-responsive ports

### Banner Grabbing

Reads service banner when available.

Example:

```bash
Port:21 -> Open
Banner: 220 (vsFTPd 3.0.5)
```

### Range Scanning

Scans port interval:

```bash
Start Port:20
End Port:25
```

Example output:

```bash
Port:21 -> Open
Port:22 -> Open
Port:23 -> Closed
```

### Basic Risk Classification

Static risk hints for common ports:

* 21 → FTP
* 22 → SSH
* 23 → Telnet
* 80 → HTTP
* 443 → HTTPS

---

## Project Structure

main.cpp
Program flow, target handling, mode selection

scanner.h
Function declarations

scanner.cpp
Validation logic, hostname resolution, socket connection, timeout handling, banner grabbing, range scan logic

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

### Scan with Hostname

```bash
Enter the target: google.com
Resolved IP: 142.x.x.x
```

### Single Port Scan

```bash
Choose Mode:
1.Single port Scan
2.Range of port Scan
```

### Range Scan

```bash
Enter Starting Port:20
Enter Ending Port:25
```

---

## Current Limitations

* Sequential scan only
* Static protocol hints
* HTTP banner handling limited
* No filtered state detection yet
* No hostname reverse lookup

---

## Planned Improvements (v1.4)

* Filtered / timeout port classification
* Scan summary report
* Progress indicator
* Better service detection
* Cleaner formatted output
* Reverse DNS support

---

## Purpose

This project is built as part of practical cybersecurity learning:

**Best way to understand recon tools is building one manually.**

Focus is on learning systems programming logic first, then improving technical depth step by step.

---

## Version

v1.3
