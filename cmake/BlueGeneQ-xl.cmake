set(CMAKE_SYSTEM_NAME BlueGeneQ-dynamic)
set(_CMAKE_TOOLCHAIN_LOCATION /bgsys/drivers/ppcfloor/gnu-linux/bin)
set(_CMAKE_TOOLCHAIN_PREFIX   powerpc64-bgq-linux-)

set(CMAKE_C_COMPILER       /opt/ibmcmp/vac/bg/12.1/bin/bgxlc)
set(CMAKE_CXX_COMPILER     /opt/ibmcmp/vacpp/bg/12.1/bin/bgxlc++)
set(CMAKE_Fortran_COMPILER /opt/ibmcmp/vac/bg/14.1/bin/bgxlf90)

# Make sure MPI_COMPILER wrapper matches the gnu compilers.                                                                         
# Prefer local machine wrappers to driver wrappers here too.                                                                        
find_program(MPI_COMPILER NAMES mpixlcxx
  PATHS
  /usr/local/bin
  /usr/bin
  /bgsys/drivers/ppcfloor/comm/gcc/bin)