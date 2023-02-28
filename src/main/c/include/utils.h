#pragma once

#include <stdexcept>

// This hack is needed because this is a C++ program.
// Without this, the polymorphic GxB_set, GrB_wait, etc. functions would not load
#define __STDC_VERSION__ 201112L

extern "C" {
#include <LAGraphX.h>
}

/*
 * ARGUMENT PARSING FUNCTIONS
 */
typedef struct {
  std::string input_dir;
  std::string output_file;
  bool directed = false;
  unsigned long source_vertex = 0;
  double damping_factor = 0.0;
  unsigned long max_iteration = 0;
  unsigned long thread_num = 1;
  bool binary = false;
} BenchmarkParameters;

BenchmarkParameters ParseBenchmarkParameters(int argc, char **argv);

typedef struct {
  std::string vertex_file;
  std::string edge_file;
  std::string matrix_file;
  std::string mapping_file;
  bool weighted = false;
  bool directed = false;
  bool binary = false;
} ConverterParameters;

ConverterParameters ParseConverterParameters(int argc, char **argv);

time_t GetCurrentMilliseconds();

void SerializeDebugMatrix(const char *title, GrB_Matrix result);

/*
 * GRAPHBLAS HELPER MACROS
 */

//------------------------------------------------------------------------------
// OK: call a GraphBLAS method and check the result
//------------------------------------------------------------------------------

// OK(method) is a macro that calls a GraphBLAS method and checks the status;
// if a failure occurs, it handles the error via the CHECK macro above, and
// returns the error status to the caller.

#define OK(method)                                         \
{                                                          \
    info = method;                                         \
    if (info != GrB_SUCCESS)                               \
    {                                                      \
        throw std::runtime_error{                          \
            std::string{"GraphBLAS error [" +              \
              std::to_string(info) + "]  "}                \
        };                                                 \
    }                                                      \
}
