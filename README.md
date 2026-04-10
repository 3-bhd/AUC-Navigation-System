# AUC Navigation System — TayehFeHuss

Indoor navigation system for AUC's HUSS building · A* pathfinding · interactive Qt GUI

---

## Overview

An interactive indoor navigation system for the Al-Waleed Ibn Talal (HUSS) building at AUC — a building intentionally designed as a maze. The system models the building's plaza floor as a graph, allows dynamic node and edge editing, and finds the shortest path between any two locations using the A* algorithm, visualized directly on the real building floor map.

Built as part of a Data Structures course at The American University in Cairo.

---

## Features

- 🗺️ **A* Pathfinding** — finds shortest path between any two rooms/offices on the plaza floor
- 🖱️ **Interactive Node Editing** — add nodes (rooms, corridors, offices) by clicking on the map
- 🔗 **Interactive Edge Editing** — connect nodes with edges representing walkable paths
- 💾 **Persistent Storage** — graph saved to and loaded from text files between sessions
- 🎨 **Real-time Visualization** — shortest path drawn directly on the actual building floor map
- 🏗️ **Extensible Design** — easily adaptable to new floors or building layouts

---

## Tech Stack

| Component | Technology |
|-----------|------------|
| Language | C++ |
| GUI | Qt Framework |
| Pathfinding | A* Algorithm |
| Data Structure | Graph (adjacency list, red-black tree via STL map) |

---

## Complexity

| Operation | Complexity |
|-----------|------------|
| Add/Delete node | O(log n) |
| Add edge | O(log n) |
| Save/Load graph | O(n log n) |
| A* pathfinding | O((E+V) log V) |

---

## How to Use

| Key | Action |
|-----|--------|
| `Space` | Add a new node at cursor position |
| `P` | Load and display saved nodes |
| `E` | Add an edge between two nodes |
| `S` | Save nodes and edges to file |
| `M` | Find and display shortest path between two locations |

---

## Repository Structure
```
├── main.cpp          # Entry point
├── graph.cpp/.h      # Graph data structure and A* algorithm
├── mapping.cpp/.h    # Qt map rendering and interaction
├── level.cpp/.h      # Floor level management
├── PlazaNodes.txt    # Saved node positions
├── PlazaEdges.txt    # Saved edge connections
├── EdgeNodes.txt     # Edge node data
├── files.qrc         # Qt resource file
├── TaheyFeHuss.pro   # Qt project file
└── README.md
```

---

## Authors

- **Omar Abdelhady** — [@3-bhd](https://github.com/3-bhd)
- **Ahmed Monir** — [@MonirCSauc](https://github.com/MonirCSauc)
- **Muhammad El-Ghazaly** — [@my612](https://github.com/my612)

The American University in Cairo — Data Structures Course
