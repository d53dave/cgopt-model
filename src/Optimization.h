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
#include "Target.h"


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
    class Optimization : BASE {
    public:

        //! This enum is used to define from what distribution the random values
        //! that are passed to the various methods will be drawn from.
        enum RandomDistr {
            normal,     //!< Normal Distribution
            uniform     //!< Uniform Distribution
        };

        //! @brief A short function descriptions
        //!
        //! The longer version goes here
        //! even on multiple lines
        //!
        //! @param state This usually would be
        //! @param rands This is random
        //! @return The initialized Target
        //!
        __CUDA__ virtual Target &           initialize   (Target & state, double *const rands) const = 0;

        //! @brief A short function descriptions
        //!
        //! The longer version goes here
        //! even on multiple lines
        //!
        //! @param state This usually would be
        //! @param rands This is random
        //! @return The initialized Target
        //!
        __CUDA__ virtual Target &           generateNext   (Target & state, double *const rands) const = 0;

        //! @brief A short function descriptions
        //!
        //! The longer version goes here
        //! even on multiple lines
        //!
        //! @param state This usually would be
        //! @param rands This is random
        //! @return The initialized Target
        //!
        __CUDA__ virtual OPT_TYPE_RETURN    evaluate (Target & state) const  = 0;

        //! @brief A short function descriptions
        //!
        //! The longer version goes here
        //! even on multiple lines
        //!
        //! @param state This usually would be
        //! @param rands This is random
        //! @return The initialized Target
        //!
        __CUDA__ virtual OPT_TYPE_RETURN    cool   (double oldtemp) const  = 0;
    protected:
        ~Optimization(){};
    };
}



