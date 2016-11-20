//
// Created by David Sere on 09/09/15.
//
// This header contains settings for the model classes and allows the framework to inject some definitions before
#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>

#include <cereal/types/array.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/bitset.hpp>
#include <cereal/types/chrono.hpp>
#include <cereal/types/common.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/forward_list.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/queue.hpp>
#include <cereal/types/set.hpp>
#include <cereal/types/stack.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/valarray.hpp>
#include <cereal/types/vector.hpp>

#define __CUDA__
#define OPT_TYPE_RETURN double
// this is probably gcc specific
#define REGISTER( args... ) template<class Archive> \
                        void serialize(Archive & a){ a( args );}

#ifdef ENABLE_CUDAMANAGED
#define BASE CudaManaged
#include "internal/CudaManaged.h"
#else
#define BASE EmptyBase
#include "internal/EmptyBase.h"
#endif
