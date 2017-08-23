//! @mainpage Example program
//!
//! Description of the project
//! You can force new lines in the HTML documentation with <br>
//!
//! With the <img-keyword you can add own pictures
//! <img src="../images/application_screenshot.jpg" alt="Screenshot">
//!
//! @author David Sere
//!

//! @file Optimization.h
//! @brief A short description of the file - what does it contain, what is it's purpose, ...
//!

/**
 *
 */

#pragma once
#include "ModelSettings.h"
#include "State.h"


namespace CSAOpt{
    //! @class Optimization
    //!
    //! @brief This class defines the interface for the Simulated Annealing optimization.
    //!
    //! This is the *core* class of CSAOpt. It defines the interface that a user must implement
    //! in order ot be able to actually do optimization computations. 
    //! 
    //! This defines the methods that the Simulated Annealing algorithm will call. Those are
    //! (1) `intialize`, a method to generate an initial state
    //! (2) `generateNext`, a method to generate a new state from an existing state
    //! (3) `evaluate`, a method to assign a score (or energy) to a given state
    //! (4) `cool`, a method to calculate the new SA temperature after an iteration
    //!
    //! The Optimization Runner will call the mentioned methods according to this pseudocode:
    //! def simulated_annealing(k_max, initial_temp):
    //!     state = initialize(empty_state, random_values)
    //!     old_temp = initial_temp
    //!     for 0 to k_max:
    //!         t = cool(old_temp)
    //!         new_state = generateNext(state, random_values)
    //!         if acceptance_func(evaluate(state), evaluate(new_state), t) >= rand(0, 1):
    //!             state = new_state
    //!
    //!     return state
    //!
    //! Where the acceptance_func is, classically, defined as
    //! def acceptance_func(e1, e2, temp):
    //!     return exp(-(e2 - e1) / temp)
    //!
    //! In the following interface, the return type is OPT_TYPE_RETURN, which will correspond to 
    //! either float or double, based on the chosen configuration. This token will be substuted
    //! by the preprocessor when the model is compiled in preparation of the optimization run
    class Optimization : BASE {
    public:

        //! This enum is used to define from what distribution the random values
        //! that are passed to the various methods will be drawn from.
        enum RandomDistr {
            normal,     //!< Normal Distribution
            uniform     //!< Uniform Distribution
        };

        //! @brief Method to get an initial state for Simulated Annealing
        //!
        //! This method will be called by during the initialization of the simulated
        //! annealing run. A new state object (i.e. target) will be created and passed to
        //! the method, along with a vector of random numbers according to the problem size. 
        //! The method is therefore expected to compute an initial state based on the passed
        //! random values and mutate the state object.
        //!
        //! @param state a newly instantiated State object
        //! @param rands a vector of random values according to the chosen random distribution
        //! @return The initialized State (i.e. mutated 'empty' state)
        //!
        __CUDA__ virtual State &           initialize   (State & state, double *const rands) const = 0;

        //! @brief Method to generate a random neighbor state based on a previous state
        //!
        //! For each iteration of the algorithm, a new state will be generated based on the previous 
        //! state. The alrogithm will therefore pass the previous state and a vector of random values
        //! to this method. The method is expected to create a new state and return it.
        //!
        //! @param state the previous state (initial state for first iteration, potentially other states later)
        //! @param rands vector of random values according to the configured problem size.
        //! @return A new state, based on the previous state and the passed in random values
        //!
        __CUDA__ virtual State &           generateNext   (State & state, double *const rands) const = 0;

        //! @brief Map a state to an energy (or score)
        //!
        //! In order to determine that a state is better than another, the algorithmn needs to derive
        //! a value based on a given state. 
        //!
        //! @param state state to be evaluated
        //! @return a 
        //!
        __CUDA__ virtual OPT_TYPE_RETURN    evaluate (State & state) const  = 0;

        //! @brief Determines the new temperature after an iteration of the algorithm
        //!
        //! This method is expected to calculate a new temperature based on the previous one.
        //! The new temperature should be lower than the previous one and the overall temprature
        //! should move towards 0 across the iterations of the optimization.
        //!
        //! @param oldtemp previous temperature
        //! @return new temperature (which should be lower than the old one)
        //!
        __CUDA__ virtual OPT_TYPE_RETURN    cool   (double oldtemp) const  = 0;
    protected:
        ~Optimization(){};
    };
}



