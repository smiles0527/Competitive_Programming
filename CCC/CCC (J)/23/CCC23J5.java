import java.util.*;

public class CCC23J5 {
    static final int MAX = 105;
    static int row;
    static int col;
    static char[][] map = new char[MAX][MAX];
    static String word;
    static int count;

    public static void backtrack(int r, int c, int index, int dr, int dc) {
        if (index == word.length()) {
            count++;
            return;
        }
        if (r < 0 || r >= row || c < 0 || c >= col || map[r][c] != word.charAt(index)) {
            return;
        }
        backtrack(r + dr, c + dc, index + 1, dr, dc);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        word = scanner.next();
        row = scanner.nextInt();
        col = scanner.nextInt();

        map = new char[row][col];
        for (int r = 0; r < row; r++) {
            String row = scanner.next();
            for (int c = 0; c < col; c++) {
                map[r][c] = row.charAt(c);
            }
        }

        count = 0;
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                backtrack(r, c, 0, 1, 0); // horizontal (left to right)
                backtrack(r, c, 0, -1, 0); // horizontal (right to left)
                backtrack(r, c, 0, 0, 1); // vertical (top to bottom)
                backtrack(r, c, 0, 0, -1); // vertical (bottom to top)
                backtrack(r, c, 0, 1, 1); // diagonal (top-left to bottom-right)
                backtrack(r, c, 0, -1, -1); // diagonal (bottom-right to top-left)
                backtrack(r, c, 0, 1, -1); // diagonal (bottom-left to top-right)
                backtrack(r, c, 0, -1, 1); // diagonal (top-right to bottom-left)
            }
        }

        System.out.println(count);
        scanner.close();
    }
}
