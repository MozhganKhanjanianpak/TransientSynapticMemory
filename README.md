# Transient Synaptic Memory in Random Neuronal Networks

This repository contains the reference implementation accompanying the manuscript

> **Transient Synaptic Memory Determines the Future Evolution of Random Neuronal Networks**
> *(under review)*

The repository includes the C++ implementation of the neuronal network model, Python scripts used for analysis and visualization, and sample simulation outputs.

---

## Overview

This work investigates how transient synaptic memory influences the future evolution of neuronal activity in homogeneous random networks.

Although all simulations are performed on structurally identical Erdős–Rényi networks, different realizations of the initial activity may evolve toward either

- one-cycle dynamics
- multi-cycle dynamics

The central finding is that this difference is not determined by network topology, but by the latent synaptic-memory state remaining after the first activity cycle.

---

## Repository Structure
TransientSynapticMemory/
│
├── cpp/ # C++ implementation of the model
│ ├── examples/
│ ├── include/
│ └── src/
│
├── python/ # Analysis and plotting scripts
│
├── sample_data/ # Example simulation outputs
│
├── figures/ # Figures generated from sample data
│
├── docs/ # Additional documentation
│
└── README.md


---

## Model

The model implements a directed excitatory–inhibitory random neuronal network with finite-lifetime synapses.

Main characteristics:

- Directed Erdős–Rényi network
- 80% excitatory neurons
- 20% inhibitory neurons
- Discrete-time dynamics
- Finite synaptic lifetimes
- External input applied only at the initial time step

All model parameters are defined in
cpp/include/parameters.h


---

## Compilation

The C++ code was tested using

- GCC 9+
- Embarcadero Dev-C++ 6.3

Compile all source files together.

---

## Running the simulation

The main executable is
cpp/examples/main.cpp


Running the program generates
ActivityInTime.txt
ActiveNodesInTime.txt


which are subsequently analyzed using the Python scripts.

---

## Python analysis

The Python scripts reproduce the figures presented in the manuscript.

Typical dependencies include

- NumPy
- Matplotlib
- SciPy

---

## Citation

If you use this code, please cite


---

## Contact

Mozhgan Khanjanianpak

Postdoctoral Researcher

Institute for Advanced Studies in Basic Sciences (IASBS)

Email:
<your email>
