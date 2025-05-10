// import java.util.Random;

// public class SumOrSameGame {
//     private int[][] puzzle;

//     public SumOrSameGame(int numRows, int numCols) {
//         puzzle = new int[numRows][numCols];
//         Random rand = new Random();
//         for (int i = 0; i < numRows; i++) {
//             for (int j = 0; j < numCols; j++) {
//                 puzzle[i][j] = rand.nextInt(9) + 1;
//             }
//         }
//     }

//     public boolean clearPair(int row, int col) {
//         int val = puzzle[row][col];
//         int R = puzzle.length;
//         int C = puzzle[0].length;
//         for (int i = row; i < R; i++) {
//             for (int j = 0; j < C; j++) {
//                 if (i == row && j == col) continue;   // only skip the same cell
//                 int other = puzzle[i][j];
//                 if (other == val || other + val == 10) {
//                     puzzle[row][col] = 0;
//                     puzzle[i][j] = 0;
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
    
// }
