import java.io.*;
import java.util.*;

public class CCC04S3 {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static String[][] grid = new String[10][10];
    static boolean[][] vis = new boolean[10][10];

    public static void main(String[] args) throws IOException {
        for (int i = 0; i < 10; i++) {
            String[] cols = br.readLine().split(" ");
            System.arraycopy(cols, 0, grid[i], 1, 9);
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 1; j <= 9; j++) {
                vis = new boolean[10][10];
                dfs(i, j);
            }
        }
        for (int i = 0; i < 10; i++) {
            System.out.println(String.join(" ", Arrays.copyOfRange(grid[i], 1, 10)));
        }
    }

    public static int dfs(int r, int c) {
        if (isNumeric(grid[r][c])) return Integer.parseInt(grid[r][c]);
        if (vis[r][c] || grid[r][c].equals("*")) return -1;
        vis[r][c] = true;
        String[] depend = grid[r][c].split("\\+");
        int sum = 0;
        for (String cell : depend) {
            int ret = dfs(cell.charAt(0) - 'A', cell.charAt(1) - '0');
            if (ret == -1) {
                grid[r][c] = "*";
                return -1;
            }
            sum += ret;
        }
        grid[r][c] = String.valueOf(sum);
        return sum;
    }

    public static boolean isNumeric(String strNum) {
        return strNum != null && strNum.matches("\\d+");
    }
}