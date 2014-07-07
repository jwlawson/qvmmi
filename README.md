#qvmmi

MPI code to find minimally mutation infinite quivers


I have tested the code with OpemMPI. The code is provided with a Makefile, to
compile run `make`. This will compile an executable called `qvmmi`.

Compilation assumes that `mpic++` is on the PATH. If not, then either set the
PATH to include the MPI binaries, or change `CXX` in the Makefile to specify
the path to the `mpic++` binary.

##Usage
```
qvmmi [ -s | -f ] [ -d dynkin | -i input | -m matrix ]

-d
    Specify a dynkin diagram to extend to find minimally mutation-infinite
    matrices. Possible options are as follows: 
        A2, A3, A4, A5, A6, A7, A8, A9, D4, D5, D6, D7, D8, D9, E6, E7, E8

-m
    Specify a matrix to extend to find minimally mutation-infinite
    matrices. The matrix should be in a form similar to the following
        { { 0 1 2 } { -1 0 1 } { -2 -1 0 } }
    and should be enclosed within quotes. The spacing in the matrix is
    important for the parser.
    
-i
    Specify a file containing a number of matrices as above. These matrices
    are read from the file and used as input.
    
-f
    Read matrices from the input source. To each add a vertex in every
    possible way and check if the resulting matrix is minimally
    mutation-infinite. The checking used is a fast approximation, which
    cannot prove that a matrix is mutation-finite, but can prove that it
    is mutation-infinite. Matrices which are thought to be mutation-finite
    are output with the prefix "Finite: " to enable them to be filtered out
    of the output easily. Any matrices output without this prefix are
    probably minimally mutation-infinite, but should be checked using
    'qvmmi -s'.
    
    If a single matrix or a dynkin diagram is provided as input, then the
    whole mutation class of the provided matrix is calculated and used as
    the input for the above procedure.
    
-s
    Read matrices from the input source and check whether each is minimally
    mutation-infinite. The checking used is a slow check which will
    definitively prove whether the matrix is mutation-infinite or not.
    Do not use with '-f'. Only input option compatible with '-s' is '-i'.
```

##Running
To run the code use either `mpirun` or `mpiexec` to start the program across a
number of nodes. This requires that either the `mpirun` is called using its full
path or that the MPI libraries are correctly referenced in `LD_LIBRARY_PATH`.

###Example
- `mpirun -np 4 qvmmi -f -d A3` runs the code on 4 cores and outputs all
(probably) MMI matrices which are formed by adding a vertex to a matrix in the 
mutation-class of A3.
- `mpiexec -np 8 qvmmi -s -i file` runs the slow checker on all matrices 
contained in the input file using 8 cores.

##License
```
Copyright 2014 John Lawson

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
