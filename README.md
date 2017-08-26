# csaopt-model [![Build Status](https://travis-ci.org/d53dave/csaopt-model.svg?branch=master)](https://travis-ci.org/d53dave/csaopt-model)

This is the model used to perform Simulated Annealing for the CSAOpt project. It defines the interface, or contract, by which the optimization will be performed. The user is required to implement this intertface according to the domain they are performing the optimization for. 

## Interface
This describes the methods required to perform Simulated Annealing. On a high level, required are (1) a method to generate a start state, (2) a method to generate a new state from a given state (3) a way to evaluate the "goodness" of a state and (4) a method to decreate the temperature parameter. See [Optimization.h](src/Optimization.h) for more details.
```cpp
 __CUDA__ virtual State &            initialize    (State & state, double *const rands) const = 0;
 __CUDA__ virtual State &            generateNext  (State & state, double *const rands) const = 0;
 __CUDA__ virtual OPT_TYPE_RETURN    evaluate      (State & state) const  = 0;
 __CUDA__ virtual OPT_TYPE_RETURN    cool          (double oldtemp) const  = 0;
```
