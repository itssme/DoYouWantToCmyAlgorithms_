# DoYouWantToCmyAlgorithms?

Collection of some algorithms implemented in C. <br>
Goal is high performance.

## Build

```bash
git clone https://github.com/itssme/DoYouWantToCmyAlgorithms_
cd DoYouWantToCmyAlgorithms_
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
#S  #     #
### # ### #
# #   #   #
# ##### ###
# #   #   #
# # # ### #
#   # #   #
# ### # ###
#   #    E#
###########
generated 1 (10x10) mazes in 0.000432 seconds
```

For bigger mazes pipe output into a file:
```bash
>> ./generator 10000000 50 > maze.txt  
```

Look at the output like:
```bash
>> tail maze.txt 
# # # # ### # # # # # # # # ### # # ############# #
# # # # #   # # # #   # # # #     #             # #
### # # # # # # # ##### # # ##### ############# # #
#   # # # # # # #     # # # #   # #     #   #   # #
# # ### # ### # ##### # # # # # ### ### # # # ### #
# # #   #   #   #   # # # # # # #   # #   # # #   #
# ### ##### ##### # ### # # # # # ### ##### # # # #
#                 #     # #   #           #     #E#
###################################################
generated 1 (10000000x50) mazes in 6.848794 seconds
```
