# Advanced Computer Architecture Lab 2
##CS4342 Advanced Computer Architecture Take Home Lab 2

###Building the Project
Create a folder inside the project. eg : build. Then within the folder
run `cmake ..`, In linux this will usually create a Makefile to compile the project. 
You can run `make` within the folder to build the project.

###Command line arguments
After building it will create a executable named "BPAnalysis".
You can run it and get the help list for the command line arguments by,
`BPAnalysis -h`

eg :
`BPAnalysis -i ./traces/12queens.trace -1sb`
