/// This is the main header file, it contains all the prototypes and
/// describes the relations between classes.
#ifndef _ORCS_ORCS_HPP_
#define _ORCS_ORCS_HPP_

/// C Includes
#include <unistd.h>     /* for getopt */
#include <getopt.h>     /* for getopt_long; POSIX standard getopt is in unistd.h */
#include <inttypes.h>   /* for uint32_t */
#include <zlib.h>
#include <assert.h> //asserts
 #include <sys/time.h> //get time of day
/// C++ Includes
//facilities
#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <thread>
//original
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <map>
#include <cassert>
#include <libconfig.h++>

// ============================================================================
/// Classes
// ============================================================================

class orcs_engine_t;
class trace_reader_t;
class opcode_package_t;
class configure_t;

//  =========================================//
// Branch Predictor Classes
//  =========================================//

class btb_line_t;
class btb_t;
class twoBit_t;
class piecewise_t;
class predictor_t;
class branch_predictor_t;

//  =========================================//
// Out of order Execution classes
//  =========================================//
class disambiguation_t;
class disambiguation_perfect_t;
class disambiguation_hashed_t;
//  =========================================//
// Out of order Execution classes
//  =========================================//

class uop_package_t;
class reorder_buffer_line_t;
class memory_order_buffer_line_t;
class processor_t;

//  =========================================//
// Cache Classes
//  =========================================//

class linha_t;
class cacheSet_t;
class cache_t;
class cache_manager_t;
class mshr_entry_t;

//  =========================================//
// Directory Classes
//  =========================================//

class directory_line_t;
class directory_set_t;
class directory_t;
class directory_manager_t;
//  =========================================//
// Usefull Classes
//  =========================================//
template<class CB_TYPE> class circular_buffer_t;
class utils_t;
class priority_memory_access_t;
//  =========================================//
// Prefetcher Classes
//  =========================================//
class prefetcher_t;
class stride_table_t;
class stride_prefetcher_t;
//  =========================================//
// Memory Controller Classes
//  =========================================//
class memory_controller_t;
//  =========================================//
// HIVE Classes
//  =========================================//
class hive_controller_t;
class hive_register_t;
//  =========================================//
// DATA Types
// ====================================
typedef std::vector <reorder_buffer_line_t*> container_ptr_reorder_buffer_line_t;
// ============================================================================
/// Global SINUCA_ENGINE instantiation
// ============================================================================
extern orcs_engine_t orcs_engine;

// #define NUMBER_OF_PROCESSORS 1

//  =========================================//
// SDV Classes
//  =========================================//
class TL_t;
class VRMT_t;

#define SANITY_CHECK 0
#define HEARTBEAT 1
#define HEARTBEAT_CLOCKS 10000000

#define KILO 1024
#define MEGA KILO*KILO
// ============================================================================
/// Definitions for Log, Debug, Warning, Error and Statistics
// ============================================================================
#define POSITION_FAIL -1        /// FAIL when return is int32_t
#define FAIL 0                  /// FAIL when return is int32_t or uint32_t
#define OK 1                    /// OK when return is int32_t or uint32_t
#define NOT_ALL_REGS 2
#define TRACE_LINE_SIZE 512

// ========================
// Defines Simulators Caracteristics
// ========================
#define MAX_UOP_DECODED 5
#define MAX_REGISTERS 6         /// opcode_package_t uop_package_t  (Max number of register (read or write) for one opcode/uop)
#define MAX_ASSEMBLY_SIZE 32    /// In general 20 is enough
// ========================
// ==============================================================================
/// Enumerations
// ==============================================================================
#include "utils/enumerations.hpp"
// ============================================================================
// ==============================================================================
/// Macros
// ==============================================================================
#include "utils/macros.hpp"
// ============================================================================
// ============================================================================
/// Base Includes
// ============================================================================
#include "./simulator.hpp"
#include "./orcs_engine.hpp"
#include "./config/config.hpp"
#include "./trace_reader.hpp"
#include "./main_memory/memory_request_client.hpp"
#include "./package/opcode_package.hpp"



//  =========================================//
// Usefull Classes
//  =========================================//
#include "./utils/circular_buffer.hpp"
#include "./utils/utils.hpp"
//  =========================================//
// Core Includes
//  =========================================//
#include "./processor/memory_disambiguation/disambiguation.hpp"
#include "./processor/memory_disambiguation/disambiguation_hashed.hpp"

//  =========================================//
// Core Includes
//  =========================================//
#include "./package/uop_package.hpp"
#include "./package/memory_package.hpp"
#include "./processor/reorder_buffer_line.hpp"
#include "./processor/memory_order_buffer_line.hpp"
#include "./processor/processor.hpp"
//  =========================================//
// Branch Predictor includes
//  =========================================//
#include "./branch_predictor/btb_line.hpp"
#include "./branch_predictor/btb.hpp"
#include "./branch_predictor/predictor.hpp"
#include "./branch_predictor/piecewise.hpp"
#include "./branch_predictor/twoBit.hpp"
#include "./branch_predictor/branch_predictor.hpp"
//  =========================================//
// Cache Classes
//  =========================================//
// // CACHE INCLUDES
#include "./cache/linha.hpp"
#include "./cache/cacheSet.hpp"
#include "./cache/cache.hpp"
#include "./cache/cache_manager.hpp"
#include "./cache/mshr_entry.hpp"
//  =========================================//
// Directory Classes
//  =========================================//
// // DIRECTORY INCLUDES
#include "./directory/directory.hpp"
#include "./directory/directory_line.hpp"
#include "./directory/directory_set.hpp"
//  =========================================//
// // Prefetcher INCLUDES
#include "./prefetcher/prefetcher.hpp"
#include "./prefetcher/stride_table.hpp"
#include "./prefetcher/stride_prefetcher.hpp"
//  =========================================//
// // MemoryController INCLUDES
#include "./main_memory/memory_channel.hpp"
#include "./main_memory/memory_controller.hpp"
//  =========================================//
// // HIVE INCLUDES
#include "./hive/hive_controller.hpp"
#include "./hive/hive_register.hpp"
//  =========================================//
// // SDV INCLUDES
#include "./SDV/TL_line.hpp"
#include "./SDV/TL_set.hpp"
#include "./SDV/TL.hpp"
#include "./SDV/VRMT_line.hpp"
#include "./SDV/VRMT_set.hpp"
#include "./SDV/VRMT.hpp"
//  =========================================//
#endif  // _ORCS_ORCS_HPP_
