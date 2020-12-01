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
#.................#.....#.#...#...........#.......#
###################################################
generated (10000000x50) maze in 6.848794 seconds
```