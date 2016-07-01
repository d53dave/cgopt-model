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
    //! @brief A short description of the class
    //!
    //! A more detailed class description
    //! goes here.
    //!
    class Optimization {
    public:

        //!
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



