//
// Created by David Sere on 09/09/15.
//
#pragma once
#include "ModelSettings.h"

namespace CSAOpt{
    //! @class State
    //!
    //! @brief The State class is used to model units of the search space in the Simulated Annealing optimization.
    //!
    //! A core concept of Simulated Annealing is the `state`. Starting from an initial state, the algorithm
    //! will select better states probabilistically based on their score. This class is therefore used
    //! to model the actual search space entities that the optimization operates upon. The result of an
    //! optimization run is a single state object and it's respective energy, in case that number is 
    //! interpretable.
    //! 
    //! The state is unique to each domain, which is why you are looking at an empty class.
    //!
    //! As a technical detail, this class needs to be serialized and deserialized when being sent over the
    //! network. All fields of this class therefore need to be `registered` with the serializer library, 
    //! which is done using the `REGISTER` macro. See test/SerializationTest.cpp for a detailed example of
    //! a somewhat complex State object, containing a nested object. See Options.h for details on the REGISTER
    //! macro and it's invocation.
    //! 
    //! Note that several restrictions apply to the State that is handled within CSAOpt
    //! (1) do not allocate memory on the stack, i.e. the `new` operator is forbidden.
    //! (2) TODO: there certainly are more limitations. Find and document.
    class State : BASE {
    public:

    };

}




