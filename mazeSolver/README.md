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
