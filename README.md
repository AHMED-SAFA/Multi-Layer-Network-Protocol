# Multi-Layer Network Protocol Simulation (ARP, UDP-DNS, ICMP)

[![OMNeT++](https://img.shields.io/badge/Framework-OMNeT++-blue)](https://omnetpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![C++](https://img.shields.io/badge/Language-C++-orange)](https://isocpp.org/)

## 📖 Overview

This project simulates a multi-protocol network environment using **OMNeT++**, demonstrating the intricate interdependencies between protocols 
operating at different layers of the OSI model. It replicates a real-world web browsing workflow, from initial MAC address resolution to 
domain name lookup and connectivity testing.

The simulation highlights how higher-layer protocols (DNS, HTTP concepts) rely on lower-layer services (ARP, IP, UDP) to function correctly, 
providing a visual and logical representation of network traffic flow.

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/a4e07466-f623-4349-ba39-6e0b5446e1fd" />

## 🎯 Objectives

- Design and implement a multi-protocol network simulation.
- Demonstrate protocol interactions across OSI Layers 2, 3, 4, and 7.
- Implement **ARP** for dynamic MAC address discovery.
- Implement **DNS** query functionality using **UDP** as the transport mechanism.
- Incorporate **ICMP** echo reply (ping) for network diagnostics.

## 🏗️ Architecture & Components

The simulation consists of four main modules connected via a central router:

| Component | Role | Key Features |
| :--- | :--- | :--- |
| **PC (Client)** | Initiator | Maintains ARP cache, schedules periodic Pings, triggers DNS queries. |
| **Router** | Traffic Director | Protocol-aware forwarding; broadcasts ARP, routes UDP port 53 to DNS, others to HTTP. |
| **DNS Server** | Name Resolver | Listens on UDP port 53, resolves `example.com` to `192.168.0.20`. |
| **HTTP Server** | Web Host | Responds to ARP requests and ICMP pings (foundation for future HTTP logic). |

### Protocol Stack Implementation

*   **Layer 2 (Data Link):** ARP for IP-to-MAC resolution.
*   **Layer 3 (Network):** IP addressing and ICMP for diagnostics.
*   **Layer 4 (Transport):** UDP for connectionless, low-latency DNS transport.
*   **Layer 7 (Application):** DNS for name resolution.

## ⚙️ How It Works

### 1. Initialization Phase
At `t=0`, all modules initialize with predefined IP/MAC addresses. The PC schedules its first Ping at `t=0.5s` and its first DNS query at `t=1.0s`.

### 2. ARP Resolution (First Ping)
1.  PC attempts to ping the DNS Server (`192.168.0.10`).
2.  PC checks its ARP table → **Miss**.
3.  PC broadcasts an **ARP Request**.
4.  Router broadcasts the request to all subnets.
5.  DNS Server recognizes its IP and sends a unicast **ARP Reply**.
6.  PC updates its ARP table with the DNS Server's MAC address.

### 3. DNS Resolution
1.  PC initiates a DNS query for `web.com`.
2.  PC encapsulates the DNS query in a **UDP Packet** (Source Port: 10053, Dest Port: 53).
3.  Router inspects the destination port (53) and routes the packet to the DNS Server.
4.  DNS Server resolves `web.com` → `192.168.0.20`.
5.  DNS Server sends a UDP response back to the PC.
6.  PC logs: `"DNS resolved web.com → 192.168.0.20"`.

## 🛠️ Installation & Setup

### Prerequisites
- [OMNeT++](https://omnetpp.org/download/) installed (Recommended version: 6.x+)
- C++ Compiler (GCC/Clang/MSVC)

### Running the Simulation
1.  Clone the repository:
    ```bash
    git clone https://github.com/AHMED-SAFA/Multi-Layer-Network-Protocol
    cd Multi-Layer-Network-Protocol
    ```
2.  Open the project in the OMNeT++ IDE.
3.  Build the project (`Project > Build All`).
4.  Run the simulation configuration (`Run As > OMNeT++ Simulation`).


## 🌍 Real-World Applications

This simulation models critical scenarios found in:
*   **Corporate Networks:** Internal service discovery and continuous health monitoring via ICMP.
*   **ISP Infrastructure:** Scalable DNS resolution and traffic segmentation via port-based routing.
*   **Data Centers:** Low-latency UDP communication for service discovery and load balancer health checks.

## 📚 References

*   **RFC 826:** Address Resolution Protocol (ARP)
*   **RFC 768:** User Datagram Protocol (UDP)
*   **RFC 792:** Internet Control Message Protocol (ICMP)
*   **RFC 1035:** Domain Names - Implementation and Specification (DNS)
*   **OMNeT++ Documentation:** [omnetpp.org](https://omnetpp.org/)

## 👤 Author

**Ahmed Nur E Safa**
*   Department of Computer Science and Engineering
*   Khulna University of Engineering & Technology (KUET)
