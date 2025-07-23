# ⚡ Electric Circuit Simulator

A modern C++/Qt6-based desktop application that allows users to **build, visualize, and simulate DC electric circuits**.  
This simulator supports **Modified Nodal Analysis (MNA)** to analyze the circuit behavior and solve for voltages and currents.

---

## ✨ Features

- 🧮 **Accurate DC Simulation** using Modified Nodal Analysis (MNA)
- ⚡ **Supports All DC Sources**
  - Independent and dependent sources (VCVS, CCCS, VCCS, CCVS)
- 🔩 **Passive Component Support**
  - Resistors (more components planned)
- 🧱 **Object-Oriented Component Design**
  - Each component encapsulates its drawing, simulation behavior, and interaction
- 🖼️ **Graphical Circuit Builder** using Qt6 and `QPainter`
- 🖱️ **Interactive Result Viewing**
  - Click on any component to see its computed current, voltage, or power
- 🔄 **Wiring System with Pathfinding**
  - Wire drawing leverages graph algorithms to automatically find the shortest and cleanest path between nodes
- 🚀 **Powered by Modern C++**
  - STL containers, enum classes
- ⚙️ **Matrix Solver using Eigen**
  - Efficient solving of large linear systems representing the circuit

---

## 📐 Simulation Methodology

This simulator uses **Modified Nodal Analysis (MNA)** to model and solve DC electrical networks. The process includes:

1. Stamping each component into the global conductance matrix \( G \) and source vector \( I \)
2. Handling dependent sources with auxiliary variables and control coefficients
3. Solving the matrix using the [Eigen](https://eigen.tuxfamily.org/) library to compute node voltages
4. Displaying results interactively when components are selected

> 🔍 Simulation core is implemented in [`items.cpp`](./items.cpp)

---

## 🧱 Software Architecture & Design Patterns

The simulator is built with **scalability and reusability** in mind:

### 🧩 Component-Based Architecture
Each element (resistor, source, wire) is derived from a common `Component` base class:
- Promotes **polymorphism** for stamping and rendering
- Enables easy addition of new components (e.g., capacitors, inductors)

### 🔁 Factory / Dynamic Creation
Components can be dynamically created via input selection or future file parsing.

### 💡 Benefits:
- Clean separation of concerns: UI, simulation, rendering, data
- Easily extensible: add a new class, implement its stamping logic, and register it
- Scalable to support complex behaviors (transient analysis, nonlinear components)

---

## 📍 Wiring System & Graph Algorithms

The wiring tool internally models connections as a **graph** of nodes and edges.  
We use **shortest path algorithms** to draw minimal and non-overlapping wire paths between pins:

- Reduces user effort
- Enhances visual clarity
- Enables future electrical rule checks like floating nodes or cycles

---

## 📷 Screenshots

![image alt](https://github.com/Thunder-BoLT1/Electric-Circuit-Simulator/blob/d9874c56e58d5a6c3c06fc6019caf7f1b6c406bb/C1Sim.png)

---

## 🛠️ Build Instructions

### 🧾 Requirements

- Qt6 (Qt Creator recommended)
- Eigen (header-only, place in `include/` or system path)
- C++17 or later compiler

Pull requests are welcome!
If you're interested in adding new components, improving the UI, or implementing transient simulation, feel free to fork and contribute.

**Author**  
Mazen Ahmed Abd Elkawy (Thunder-BoLT1)

### 🧰 Steps

```bash
git clone https://github.com/Thunder-BoLT1/Electric-Circuit-Simulator.git
cd Electric-Circuit-Simulator
```

📋 Example Use
Launch the application.

Use the interface to place resistors, wires, and DC sources. (Keep IN Mind Wires only Short circuits the starting and ending nodes)

Connect components by dragging endpoints.

Click each component to set it's value

Run the simulation.

Click on any component after simulation to view its voltage or current.

All Icons are From https://www.flaticon.com/

