# the name of the target operating system                                                                                           
set(CMAKE_SYSTEM_NAME BlueGeneQ-dynamic)
set(_CMAKE_TOOLCHAIN_LOCATION /bgsys/drivers/ppcfloor/gnu-linux/bin)
set(_CMAKE_TOOLCHAIN_PREFIX   powerpc64-bgq-linux-)

# Make sure MPI_COMPILER wrapper matches the gnu compilers.                                                                         
# Prefer local machine wrappers to driver wrappers here too.                                                                        
find_program(MPI_COMPILER NAMES mpicxx mpic++ mpiCC mpicc
  PATHS
  /usr/local/bin
  /usr/bin
  /bgsys/drivers/ppcfloor/comm/gcc/bin)