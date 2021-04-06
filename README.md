# Longest simple path algorithm using DFS.
## Description
Finds the longest simple path of holes in a labyrinth formed by `#` \(walls\) and `.` \(holes\).

## Requirements
C++11 compiler.

## Build
Execute in terminal:
```
make -k
```

## Quick start
To run the examples, run in terminal:
```sh
./labyrinth ./examples/input.txt ./results/output.txt
./labyrinth ./examples/input_1.txt ./results/output_1.txt
./labyrinth ./examples/edge_input.txt ./results/edge_output.txt
# Really slow due to the problem being NP-hard [2]
./labyrinth ./examples/edge_input_1.txt ./results/edge_output_1.txt
./labyrinth ./examples/edge_input_2.txt ./results/edge_output_2.txt
./labyrinth ./examples/edge_input_3.txt ./results/edge_output_3.txt
./labyrinth ./examples/edge_input_4.txt ./results/edge_output_4.txt
```

## References
1. Base code from: https://gist.github.com/clarkngo/eb3132769df2ca28919ab8e6054716a5
2. Cormen, Thomas H.; Leiserson, Charles E.; Rivest, Ronald L.; Stein, Clifford \(2001\), Introduction To Algorithms \(2nd ed.\), MIT Press, p. 978, ISBN 9780262032933.
