# Communication Architecture for an Autonomous Mobile Robot

## 🧭 Project Overview

This project aims to design and simulate a robust **communication architecture** for an **exploration mobile robot** operating in constrained environments such as tunnels.  
The approach relies on a **mobile ad hoc network (MANET)** using the **OLSR routing protocol** and modern **Wi-Fi communication technologies**.

---

## 🎯 Objectives

- Address communication challenges in infrastructure-less environments (tunnels, mines, disaster zones).  
- Propose a MANET-based solution ensuring reliable and adaptive robot-to-robot communication.  
- Leverage network simulation to analyze performance under realistic mobility and propagation conditions.

---

## 🧰 Technologies Used

- **ns-3** — Network simulator for MANET modeling and testing.  
- **Wireshark + Pcap** — Packet capture and network analysis.  
- **Wi-Fi (802.11n)** — High-throughput wireless standard suitable for underground communications.

### Propagation Models
- **Friis model** — Free-space propagation.
- **LogDistance model** — Signal attenuation with distance and obstacles.

### Mobility Model
- **RandomWaypointMobilityModel** — Realistic simulation of mobile robots in tunnels.

### Routing Protocol
- **OLSR (Optimized Link State Routing)** — Efficient routing for mobile ad hoc networks.

---

## 🧩 Implementation Process

1. Preliminary study of communication architectures for mobile robotics.  
2. Selection of technologies: MANET + Wi-Fi 802.11n + OLSR.  
3. ns-3 setup and configuration (mobility, propagation, routing).  
4. Simulation, data capture (Wireshark), and performance analysis.  
5. Evaluation of throughput, latency, and packet loss.

---

## ⚙️ ns-3 Simulation Optimization

To improve realism and performance:

- **Wi-Fi 802.11n**: increased range and throughput.  
- **Friis + LogDistance models**: combined propagation effects.  
- **RandomWaypointMobilityModel**: variable speeds and pauses.  
- **OLSR**: quick route discovery and adaptive reconvergence.

---

## 📊 Results

- Operational MANET communication in simulated tunnel conditions.  
- Demonstrated stability of Wi-Fi 802.11n under constrained environments.  
- OLSR protocol provided robust routing with minimal latency.  
- Optimized parameters reduced packet loss and improved throughput.

---

## 🧠 Context & Motivation

The project addresses the need for **reliable communication systems** in **robotic exploration of underground environments**.  
In the absence of traditional infrastructure, **MANET networks** provide flexibility, scalability, and resilience.

---

## ⚠️ Limitations & Challenges

**Limitations:**
- Random mobility cannot fully represent physical tunnel constraints.  
- Complex multi-path interferences not modeled.

**Challenges:**
- Fine-tuning mobility parameters to avoid unrealistic clustering.  
- Managing energy consumption from frequent OLSR messaging.

---

## 🚀 Potential Applications

- Robotic exploration in tunnels, mines, and caves.  
- Rapid deployment of emergency communication networks.  
- Research on routing protocols in dynamic and constrained environments.

---
