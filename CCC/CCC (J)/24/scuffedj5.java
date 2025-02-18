import java.util.*;
public class scuffedj5 {

    static char[] word;
    static int numRows;
    static int numCols;
    static char[][] grid;
~    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        word = input.next().toCharArray();
        numRows = input.nextInt();
        numCols = input.nextInt();
        grid = new char[numRows][numCols];
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                grid[i][j] = input.next().charAt(0);
            }
        }

        int count = 0;
        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < numCols; c++) {
                if (grid[r][c] == word[0]) {
                    for(int i = -1; i <= 1; i++){
                        for(int j = -1; j <= 1; j++){
                            if((i!= 0 || j!= 0) && inBounds(r+i, c+j) && grid[r+i][c+j] == word[1]){
                                count += recur(1, r+i, c+i, i, j, false);
                            }
                        }
                    }
                }
            }
        }
        System.out.println(count);
        input.close();
    }

    private static int recur(int index, int r, int c, int rShift, int cShift, boolean usedTurn){
        if(index == word.length-1){
            return 1;
        }
        int count = 0;
        if(inBounds(r+rShift, c+cShift) && grid[r+rShift][c+cShift] == word[index+1]){
            count += recur(index+1, r+rShift, c+cShift, rShift, cShift, usedTurn);
        }
        if(!usedTurn && inBounds(r-cShift, c+rShift) && grid[r-cShift][c+cShift] == word[index+1]){
            count += recur(index+1, r-cShift, c+rShift, -cShift, rShift, true);
        }
        if(!usedTurn && inBounds(r+cShift, c+-rShift) && grid[r+cShift][c+cShift] == word[index+1]){
            count += recur(index+1, r+cShift, c-rShift, cShift, -rShift, true);
        }
        return count;
    }

    private static boolean inBounds(int r, int c){
        return r >= 0 && r < numRows && c >= 0 && c < numCols;
    }
}

