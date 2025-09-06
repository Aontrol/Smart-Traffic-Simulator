#  Smart Traffic Simulator

A terminal-based **traffic simulation** tool built using **C** and the **ncurses** library. The simulator allows users to dynamically add vehicles from all four directions and simulates smart traffic control based on traffic density.

---

##  Features

* Terminal UI with real-time updates using `ncurses`
* Add vehicles from **UP**, **DOWN**, **LEFT**, and **RIGHT** directions
* Smart traffic logic prioritizes the direction with **highest vehicle density**
* Real-time parameter panel showing:

  * Total vehicles
  * Per-route traffic density
* Visual simulation of vehicles moving through an intersection

---
##  Requirements

* GCC compiler (`gcc`)
* `ncurses` library

---
##  Installation

### On Debian/Ubuntu

```bash
sudo apt update
sudo apt install build-essential libncurses5-dev libncursesw5-dev
```

---

## Build and Run

### 1. Clone the repository

```bash
git clone https://github.com/your-username/smart-traffic-simulator.git
cd smart-traffic-simulator
```

### 2. Compile the program

```bash
gcc traffic_simulator.c -lncurses -o traffic_simulator
```

### 3. Run the simulator

```bash
./traffic_simulator
```

---
