#ifndef PARAMETERS_H
#define PARAMETERS_H

/////////////////////////////////////////////////////////////
//
// Model parameters
//
// This file contains all parameters used throughout the
// transient synaptic memory model.
//
// Changing values here automatically updates the whole
// simulation.
//
/////////////////////////////////////////////////////////////

constexpr int N = 2000;

constexpr double p = 0.1;

constexpr double E = 0.8;

constexpr double W0E = 1.0;
constexpr double W0I = -4.0;

constexpr int TE = 5;
constexpr int TI = 7;

constexpr int D = 5;

constexpr int tmax = 80;

constexpr double eta = 0.02;

#endif
