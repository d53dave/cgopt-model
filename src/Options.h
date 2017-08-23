//
// Created by David Sere on 14/09/15.
//

//! @file
//! @brief some brief lol
//!
//! Longer description of the file, whatever, Lorem IPSUM
//!

#pragma once

#include <cstddef>
#include <limits>
#include <ostream>

//! @def OPT_TYPE_TABLE
//!
//! @brief Macro definitions that will define the Options#CSAOptimizationType enum and the corresponding
//! labels for printing.
//!

//! @var Options::SINGLEPRECISION
//! Uses single precision floating point values (IEEE 754 Standard rev. 2008) for internal
//! computation. This should be the preferred setting for most application as double precision performance will be,
//! sometimes significantly, reduced, depending on the actual GPU in use.
//!

//! @var Options::DOUBLEPRECISION
//! Uses double precision floating point values for internal computation. This should only be used
//! if there are problems with the single precision computation (e.g. doesn't converge) as GPUs usually exhibit a
//! greatly reduced double precision performance. At the time of this writing, the target architecture is Nvidia's GK104
//! which should perform about over 2 TFLOPS for single point and about 100 GFLOPS for double precision.

#define OPT_TYPE_TABLE \
X(SINGLEPRECISION, "Single Precision")       \
X(DOUBLEPRECISION, "Double Precision")

//! @def PAR_TYPE_TABLE
//! @brief Macro definitions that will define the Options#CGParallelizationType enum and the corresponding
//! labels for printing.
//!

//! @var Options::SIMPLE
//! This is the 'standard' parallelization type. The gpu will spawn a configurable number of threads and
//! each of those threads will perform a simulated annealing optimization. At the end of the run, each thread has a
//! all of those results are communicated back to the client.
//!

//! @var Options::GENETIC
//! This algorithm is inspired by the genetic algorithms class of optimizations. After a configurable number
//! of rounds (see syncAfterRounds) all GPU threads pause and communicate their intermediate results. All threads
//! continue their operation using the best value that was found so far. TODO: explain similarity to GA
//!

//! @var Options::GENETIC_DISTRIBUTED
//! Same as 'Genetic' with the addition that the communication will not only happen between
//! the threads on a GPU but between all threads among all GPUs that are part of the run.
//!

#define PAR_TYPE_TABLE  \
X(SIMPLE, "Simple")     \
X(GENETIC,"Genetic")    \
X(GENETIC_DISTRIBUTED, "Genetic (Distributed)")

namespace CSAOpt{
    //! @class Options
    //!
    //! @brief This struct contains the parameters that CSAOpt will use for an optimization.
    //!
    //! The parameters here will be used for both setup and invocation of an optimization run. Please refer to the
    //! documentation of TODO: fix here
    //! for further information about the runtime behaviour of CSAOpt. This struct is intended to be
    struct Options {
    public:

#define X(a, b) a,
        //! @enum CSAOptimizationType
        //!
        //! @brief Macro defined enum for the Optimization Type. See #OPT_TYPE_TABLE
        enum CSAOptimizationType {
            OPT_TYPE_TABLE
        };
#undef X


#define X(a, b) a,
        //! @enum CGParallelizationType
        //!
        //! @brief Macro defined enum for the Optimization Type. See #PAR_TYPE_TABLE
        enum CSAParallelizationType {
            PAR_TYPE_TABLE
        };
#undef X


        //! @brief This method will create an Options object with default values.
        //!
        //! This factory method will create an object of class Options and populate it with these
        //! default values:
        //! - Optimization Type: Single Precision
        //! - Parallelization Type: Simple
        //! - Max. number of rounds per run: 500
        //! - Max. runtime for the optimization: unlimited
        //! - Number of threads on GPU: 200
        //! - Sync after rounds: 0 (value is extraneous for parallelization type 'Simple')
        //! - Trace mode: no
        //!
        //! @return The initialized State
        //!
        static Options defaultOptions() {
            Options opt;
            opt.optimizationType = SINGLEPRECISION;
            opt.parallelizationType = SIMPLE;
            opt.maxRounds = 500;
            opt.maxTimeMs = 0;
            opt.nThreads = 200;
            opt.syncAfterRounds = 0;
            opt.tracing = false;
            return opt;
        }

        size_t nThreads;        //!< Number of Threads that are used for computation
        size_t maxRounds;       //!< Maximum number of rounds that the optimization is allowed to run
        size_t syncAfterRounds; //!< Number of rounds after which threads will communicate intermediate results (see TODO: fill in)
        size_t maxTimeMs;       //!< Maximum amount of time (ms) that the optimization is allowed to take
        CSAParallelizationType parallelizationType;  //!< Parallelization Type that the Optimization will use
        CSAOptimizationType optimizationType;        //!< Optimization Type that the Optimization will use
        bool tracing;           //!< Tracing modes returns all intermediate results and can be used for analysis

        friend std::ostream& operator<<(std::ostream& os, const Options& opt);

    private:
#define X(a, b) b,
        //! @brief This will be expanded to hold the enum string for the optimization type.
        std::string OPT_LABELS[2] = {
                OPT_TYPE_TABLE
        };
#undef X

#define X(a, b) b,
        //! @brief This will be expanded to hold the enum string for the parallelization type.
        std::string PAR_LABELS[3] = {
                PAR_TYPE_TABLE
        };
#undef X

    };

    std::ostream& operator<<(std::ostream& os, const Options& opt)
    {
        os << "CSAOpt::Options = {";
        os << "\n\t Optimization Type:\t\t" << opt.OPT_LABELS[opt.optimizationType];
        os << "\n\t Parallelization Type:\t" << opt.PAR_LABELS[opt.parallelizationType];
        os << "\n\t # of Threads:\t\t\t" << opt.nThreads;
        os << "\n\t Max # of Rounds:\t\t" << opt.maxRounds;
        os << "\n\t Max Time (ms):\t\t\t" << opt.maxTimeMs;
        os << "\n\t Sync after # Rounds:\t" << opt.syncAfterRounds;
        os << "\n\t Trace mode: \t\t\t" << (opt.tracing ? "YES":"NO");
        os << "\n}" << std::endl;
        return os;
    }


}

