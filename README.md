ECE 5504: COMPUTER ARCHITECTURE

Team Members:
Saurabh Jacob Kuruvila
Shubham Jogprakash Ghosh

Project Title:
Analysis of cache hierarchy in IBM POWER architectures

Directory Structure:
ECE_5504_PROJECT.zip
                        -> GEM5 - Contains phyton scripts to simulate IBM POWER systems
                        -> SRC  - Contains Source Code for Breadth-First Search, Bucket Sort, and MD5 workloads and their associated precompiled object files for varied sizes (1MB, 4Mb, and 8MB)
                        -> Logs - Contains the Stat files of all simulation results run
                        -> ECE_5504_FINAL_PROJECT_REPORT.pdf

<cache_level> : L2, L3, L4
<workload> : BFS, MD5, Bucket
<size> : 1MB, 4MB, 8MB

GEM5
    - Copy contents of the GEM5 folder into "/gem5/config/tutorial/" 
    - Modify "SimulationTest_<cache_level>.py" to select the desired workload and size

Workloads
    - Copy <workload>_<size>.out files of desired workload into "/gem5/test/test-progs/"

Run GEM5 simulation:
    - Return to the "/gem5" directory and run the following command to build the simulation:

            build/POWER/gem5.opt -d <STATS_DIRECTORY> configs/tutorial/SimulationTest_<cache_level>.py

Workload Cross Compilation
    - Within each workload directory in the SRC folder run the following command to cross-compile the C program for POWER ISA:

            powerpc64-linux-gnu-gcc -O0 -ggdb3 -std=c99 -static <workload>.c -o <workload>_<size>.out  