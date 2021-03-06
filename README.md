# DoYouWantToCmyAlgorithms?

Collection of some algorithms implemented in C. <br>
Goal is high performance.

Implemented Algorithms:
- Maze Generator (Recursive Backtracking)
- Maze Solver

# Maze generator:

## Build

```bash
git clone https://github.com/itssme/DoYouWantToCmyAlgorithms_
cd DoYouWantToCmyAlgorithms_/mazeGeneration
mkdir build
cd build
cmake ..
make
```

## Example

Go to the build directory and run:
```bash
>> ./generator 10 10
```

Will create a 10 by 10 field Maze and print:

```bash
###########
#...#.....#
###.# ###.#
#.#...#...#
#.#####.###
#.#...#...#
#.#.#.###.#
#...#.#...#
#.###.#.###
#...#.....#
###########
```

For bigger mazes pipe output into a file:
```bash
>> ./generator 10000000 50 > maze.txt  
```

If the definition `BENCH` is set at compile time, additional output with the time will be printed.

Look at the output like:
```bash
>> tail maze.txt 
#.#.#.#.###.#.#.#.#.#.#.#.#.###.#.#.#############.#
#.#.#.#.#...#.#.#.#...#.#.#.#.....#.............#.#
###.#.#.#.#.#.#.#.#####.#.#.#####.#############.#.#
#...#.#.#.#.#.#.#.....#.#.#.#...#.#.....#...#...#.#
#.#.###.#.###.#.#####.#.#.#.#.#.###.###.#.#.#.###.#
#.#.#...#...#...#...#.#.#.#.#.#.#...#.#...#.#.#...#
#.###.#####.#####.#.###.#.#.#.#.#.###.#####.#.#.#.#
#.................#.....#.#...#...........#.....#.#
###################################################
generated (10000000x50) maze in 6.848794 seconds
```

# Maze solver:

This algorithm will solve a maze generated by the maze generator.

## Build

```bash
git clone https://github.com/itssme/DoYouWantToCmyAlgorithms_
cd DoYouWantToCmyAlgorithms_/mazeSolver
mkdir build
cd build
cmake ..
make
```

## Example

After generating a maze like `./generator 20 20 > maze.txt` with the generator, go to the build directory and run:
```bash
>> ./solver 20 20 < maze.txt
```
to solve the maze. This will use ansi colors to print the maze, so make sure to use a terminal which supports those.

It is also possible to pipe the output to a text file and look at the result late:
```bash
>> ./solver 20 20 < maze.txt > solved.txt
>> cat solved.txt
```

