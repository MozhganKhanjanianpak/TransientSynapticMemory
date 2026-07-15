# Memory Analysis

This directory contains the code used to perform the **ensemble analysis** presented in the manuscript.

Unlike the `basic_dynamics` directory, which focuses on a single realization, this part analyzes the statistics obtained from many independent realizations of the same network.

The complete workflow is

```
C++ ensemble simulation
          ↓
Simulation outputs
          ↓
Extract summary statistics
          ↓
Statistical analysis
          ↓
Reproduce Figures 3-5
```

---

## Directory structure

```
memory_analysis/

├── cpp/
│
├── python/
│
├── sample_output/
│
├── sample_snapshot_data/
│
└── README.md
```

---

## cpp/

The C++ implementation performs ensemble simulations of the transient synaptic memory model.

For each realization, the program generates

- activity time series,
- active neurons,
- snapshot data after the first extinction eventو
- potential reactivation currents,
- ghost neurons,
- active neurons after the extinction snapshot.

The number of realizations is controlled by

```
ens
```

defined in

```
parameters.h
```

---

## python/

The notebooks are intended to be executed sequentially.

### 1. build_summary_tables.ipynb

Processes the raw simulation outputs and generates

```
Results.txt
ResultsTau.txt
```

These summary tables are subsequently used by the remaining notebooks.

---

### 2. analyze_ensemble.ipynb

Uses

```
Results.txt
ResultsTau.txt
```

to reproduce the ensemble statistics shown in **Figure 5 (panels a–d)** of the manuscript.

---

### 3. figure6_panels_ej.ipynb

Reproduces the snapshot-current analysis shown in **Figure 6 (panels e–j)**.

This notebook uses the example snapshot datasets contained in

```
sample_snapshot_data/
```

---

## sample_output/

Contains a sample ensemble simulation.

These files allow the user to execute all notebooks immediately without running the C++ simulations.

Users may replace these files with outputs generated using their own ensemble simulations.

---

## sample_snapshot_data/

The snapshot-current analysis shown in Figure 6 requires storing the full potential reactivation current of every neuron.

Since these files are considerably larger than the summary statistics, representative datasets are provided here as examples.

Two examples are included:

```
one_cycle/
```

A realization producing a single activity cycle.

```
multi_cycle/
```

A realization producing sustained multi-cycle activity.

These datasets are used exclusively for reproducing the snapshot analyses presented in Figure 6.

---

## Typical workflow

```
Compile C++ code

↓

Run ensemble simulation

↓

Generate Results.txt
and ResultsTau.txt

↓

Run analyze_ensemble.ipynb

↓

(Optional)

Run figure6_panels_ej.ipynb
```
