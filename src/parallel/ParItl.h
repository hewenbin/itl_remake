// Copyright (c) 2014 Kewei Lu. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef _PARITL
#define _PARITL

#include "mpi.h"
#include "diy.h"

namespace itl {

/*
  Initialize Paritl
  dim: number of dimension
  num_threads: number of threads used, currently we are not using multiple threads
  comm: MPI communicator

  returns: error code
*/
int Paritl_Init(int dim, int num_threads, MPI_Comm comm);

/*
  Decomposes a discrete domain

  block_order: ROUND_ROBIN_ORDER or CONTIGUOUS_ORDER numbering of
  global block ids to processes (input)
  data_size: global data size (grid pts) in each dimension
  glo_num__blocks: total number of blocks in the global domain (input)
    pass 0 or anything for CONTIGUOUS_ORDER (unused)
  loc_num_blocks: local number of blocks on this process (output)
  share_face: whether neighboring blocks share a common face or are
  separated by a gap of one unit
  ghost: ghost layer for each dimension and side (min, max)
   each entry can be 0 (no ghost) or > 0 (this many ghost cells per side)
   {x min side ghost, x max side ghost, y min side ghost, y max side ghost...}
  given: constraints on the blocking entered as an array where
  0 implies no constraint in that direction and some value n > 0 is a given
  number of blocks in a given direction
  eg., {0, 0, 0, t} would result in t blocks in the 4th dimension
  wrap: whether wraparound neighbors are used

  returns: id of domain (< 0 if error)
*/
int Paritl_Decompose(int block_order, int *data_size, int glo_num_blocks, 
		  int *loc_num_blocks, int share_face, int *ghost, 
		  int *given, int wrap);

/*
  Parallel data read for all blocks using DIY, create a field object for each block
  
  did: domain id
  file_names: input file names
  var_type: input datatype
  tuple_size: how many values for each grid point
  with_header: has header in the beginning or not

  note: performs an MPI_Barrier afterwards to eliminate any process
  skew before proceeding

*/
int Paritl_Read_data_all(int did, char **file_names, int var_type, int tuple_size, bool with_header);

/*
  Parallel compute histogram for each block
  min: minimum value
  max: maximum value
*/
int Paritl_ComputeHistogram(double min, double max);

/*
  Parallel write the histogram to a single file
*/
int Paritl_WriteHistogram(char* filename);

/*
  Parallel write the histogram to different files
*/
int Paritl_DistributedWriteHistogram();

/*
  Finalize Paritl
*/
int Paritl_Finalize();

}  // namespace itl

#endif