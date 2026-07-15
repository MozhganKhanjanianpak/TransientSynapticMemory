# Transient Synaptic Memory Generates Self-Sustained Activity

This repository contains the simulation code and analysis scripts accompanying the paper

> **Transient Synaptic Memory Generates Self-Sustained Activity from Random Initial Activation**
> *(under review / accepted in ...)*

The project provides an implementation of the transient synaptic memory model introduced in the manuscript together with the Python notebooks required to reproduce the main figures.

---

The repository is organized as a step-by-step workflow rather than a collection of scripts. Each directory corresponds to one stage of the analysis pipeline described in the manuscript.

---

## Repository structure

```
Repository
│
├── basic_dynamics/
│   ├── cpp/
│   ├── python/
│   ├── sample_output/
│   └── README.md
│
├── memory_analysis/
│   ├── cpp/
│   ├── python/
│   ├── sample_output/
│   └── README.md
│
└── README.md
```

---

## Overview

The repository is divided into two independent parts.

### 1. Basic dynamics

This part reproduces the deterministic dynamics of a **single realization** of the model.

It allows the user to

- generate a random directed Erdős–Rényi network,
- simulate the transient synaptic dynamics,
- save the activity and snapshot data,
- reproduce the figures illustrating single realizations (Figure 2 of the manuscript).

---

### 2. Memory analysis

This part performs ensemble simulations and statistical analyses.

It allows the user to

- run multiple realizations,
- extract summary statistics,
- quantify fresh and ghost neurons,
- reproduce the figures illustrating single realizations (Figures 3-4 of the manuscript).
- reproduce the ensemble statistics presented in Figure 5.

---

## Software requirements

### C++

- C++17 (or newer)
- Tested with
  - GCC
  - MSVC (Visual Studio)

### Python

The analysis notebooks use

- numpy
- scipy
- matplotlib
- jupyter

They may be installed using

```bash
pip install numpy scipy matplotlib notebook
```

---

## Running the simulations

Each part of the repository contains

- C++ source code for generating simulation data,
- Python notebooks for reproducing the figures.

The recommended workflow is

```
Compile C++ code
        ↓
Generate simulation data
        ↓
Run Jupyter notebook
        ↓
Reproduce figures
```

---

## Reproducibility

All parameters used in the manuscript are defined in

```
parameters.h
```

Changing these parameters allows the model to be simulated under different conditions.

Sample datasets are included whenever generating the original data would require long simulation times.

---

## Citation

If you use this code, please cite

```
Paper information will be added after publication.
```

---

## Contact

Mozhgan Khanjanianpak

Institute for Advanced Studies in Basic Sciences (IASBS)

Email: <your email>
