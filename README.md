# Recon Utility v1.4

A lightweight C++ reconnaissance utility built to understand how low-level network scanners work internally using socket programming, timeout handling, hostname resolution, structured scan logic, and banner collection.

---

## Overview

Recon Utility is a personal systems programming and cybersecurity learning project focused on manually building core reconnaissance logic to understand what happens internally in professional scanners.

The goal is not to replace scanners like Nmap, but to learn how network reconnaissance works at socket level.

---

## Features

### Target Validation

* Accepts valid IPv4 addresses
* Rejects malformed input
* Validates all 4 octets
* Ensures octet range is 0–255

---

### Hostname Resolution

Accepts hostnames such as:

```bash
google.com
scanme.nmap.org
```

Resolves hostname into IPv4 before scanning using DNS lookup.

Example:

```bash
Resolved IP: 142.x.x.x
```

---

### Port Validation

* Accepts numeric ports only
* Valid range: 1–65535

---

### Scan Modes

#### Single Port Scan

Scans one specific port.

Example:

```bash
Enter Port:22
```

---

#### Port Range Scan

Scans a port interval.

Example:

```bash
Start Port:20
End Port:30
```

---

### TCP Connect Scan

Uses POSIX socket APIs to attempt TCP connection against target ports.

---

### Timeout Handling

Socket timeout added to avoid hanging on slow or non-responsive services.

---

### Banner Grabbing

Reads service banners when available.

Example:

```bash
22   OPEN   Connected   SSH-2.0-OpenSSH...
25   OPEN   Connected   220 debian.localdomain
```

If no banner is returned:

```bash
No banner
```

---

### Output Formatting

Structured terminal output with aligned columns:

```bash
PORT      STATE       STATUS         BANNER
--------------------------------------------------------------
22        OPEN        Connected      SSH-2.0-OpenSSH...
23        CLOSED      -              -
25        OPEN        Connected      220 debian.localdomain
```

---

### Progress Indicator

A scan completion progress bar is shown after range scanning.

Example:

```bash
[==============================] 100%
```

---

### Basic Risk Classification

Static hints for common ports:

* 21 → FTP
* 22 → SSH
* 23 → Telnet
* 25 → SMTP
* 80 → HTTP
* 443 → HTTPS

---

## Project Structure

```bash
main.cpp
scanner.h
scanner.cpp
README.md
```

### File Roles

* **main.cpp** → program flow and mode handling
* **scanner.h** → function declarations
* **scanner.cpp** → scanning logic, validation, DNS resolution, timeout handling, banner grabbing, formatted output

---

## Build

```bash
g++ main.cpp scanner.cpp -o nscan
```

---

## Run

```bash
./nscan
```

---

## Example Usage

### Single Port Scan

```bash
Enter target:10.49.138.48
Choose Mode:1
Enter Port:22
```

---

### Range Scan

```bash
Enter target:10.49.138.48
Choose Mode:2
Enter Starting Port:20
Enter Ending Port:30
```

---

## Current Limitations

* Sequential scan only
* No multithreading yet
* Static service hints
* Limited protocol-specific probing
* No filtered-state accuracy for all services
* Banner grabbing depends on service response

---

## Planned Improvements (v1.5)

* Multithreaded scanning
* Filtered port refinement
* Service-specific probes
* Reverse DNS lookup
* Scan summary report
* Optional hidden closed ports

---

## Learning Focus

This project is built to strengthen:

* C++ systems programming
* Socket programming
* Linux networking concepts
* Practical reconnaissance understanding

---

## Version

**v1.4**
