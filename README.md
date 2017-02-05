# Advanced Computer Architecture Lab 2
##CS4342 Advanced Computer Architecture Take Home Lab 2
##Attribution
Framework of the code is taken from "Lab Assignment 2: Branch Prediction - Advances in Computer Architecture 2014", Computer Systems Architecture, Institute of Informatics, University Of Amsterdam. Original name list of the assignment Dr Andy Pimentel, Roy Bakker, Roeland Douma - September 29, 2014.
###Building the Project
Create a folder inside the project. eg : build. Then within the folder
run `cmake ..`, In linux this will usually create a Makefile to compile the project. 
You can run `make` within the folder to build the project.

###Command line arguments
After building it will create a executable named "BPAnalysis".
You can run it and get the help list for the command line arguments by,
`BPAnalysis -h`

+ 1 – 8,192 BHT
+ 2 – 2-bit 4,096 BHT
+ 3 – (2, 2) 1024 BHT
+ 4 – Custom

eg : Example argument to run 12queens.trace with all the implemented algorithms
 
    >> ./BPAnalysis -1 -i ./traces/12queens.trace
    >> ./BPAnalysis -2 -i ./traces/12queens.trace
    >> ./BPAnalysis -3 -i ./traces/12queens.trace
    >> ./BPAnalysis -4 -i ./traces/12queens.trace`

### Trace Files
+ N-Queens : A chessboard pf N x N tiles and N queens. The queens must be positioned in such a way that no two queens are on the same horizontal, vertical or diagonal line.
+ Fibonacci : Calculate the N-th Fibonacci number recursively.
+ Matmul : Do a series of matrix multiplications in different ways.
+ Ray Tracing : A simple ray tracer.
        
### Tested Benchmark Trace Files Details
        
|   Benchmark   | Total Branches    | Unique Branches   |
|---------------|------------------ | ------------------|
| 12-queens     |   2,727,424       |   768             |
| fib(30)       |   4,241,389       |   491             |
| matmul        |   838,802         |   1001            |
| ray tracing   |   42,422,131      |   797             |

