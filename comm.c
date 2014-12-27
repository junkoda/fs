//
// Taking care of MPI communications
//

#include <assert.h>
#include <mpi.h>

static int this_node= -1;
static int parallel_level= 0;
  // 1: MPI_THREAD_SINGLE, only one thread will execute.
  // 2: MPI_THREAD_FUNNELED, only the thread that called MPI_Init_thread will
  //    make MPI calls.

void comm_mpi_init(int* p_argc, char*** p_argv)
{
#ifdef _OPENMP
  int thread_level;
  MPI_Init_thread(p_argc, p_argv, MPI_THREAD_FUNNELED, &thread_level);
  if(thread_level >= MPI_THREAD_FUNNELED)
    parallel_level= 2;
  else
    parallel_level= 1;
#else
  int ret= MPI_Init(p_argc, p_argv); assert(ret == MPI_SUCCESS);
  parallel_level= 1;
#endif
  

  MPI_Comm_rank(MPI_COMM_WORLD, &this_node);
}

int comm_this_node(void)
{
  return this_node;
}
