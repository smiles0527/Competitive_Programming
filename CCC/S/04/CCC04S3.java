import java.io.*;

public class CCC04S3 {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static String[][] grid = new String[10][10];
    static boolean[][] vis = new boolean[10][10];

    public static void main(String[] args) throws IOException {
        // Read the grid input
        for (int i = 0; i < 10; i++) {
            String[] cols = br.readLine().split(" ");
            for (int j = 0; j < 9; j++) {
                grid[i][j + 1] = cols[j]; 
            }
        }

        // Process each cell in the grid
        for (int i = 0; i < 10; i++) {
            for (int j = 1; j <= 9; j++) {
                // Reset the vis array for each new cell
                for (int k = 0; k < 10; k++) {
                    for (int l = 0; l < 10; l++) {
                        vis[k][l] = false;
                    }
                }
                dfs(i, j);
            }
        }

        // Print the resulting grid
        for (int i = 0; i < 10; i++) {
            for (int j = 1; j <= 9; j++) {
                System.out.print(grid[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static int dfs(int r, int c) {
        if (isNumeric(grid[r][c])) {
            return Integer.parseInt(grid[r][c]);
        }
        if (vis[r][c] || grid[r][c].equals("*")) {
            return -1;
        }

        vis[r][c] = true; 
        String[] depend = grid[r][c].split("\\+");
        int sum = 0;

        for (int i = 0; i < depend.length; i++) {
            int ret = dfs(depend[i].charAt(0) - 'A', depend[i].charAt(1) - '0');
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
        if (strNum == null) {
            return false;
        }
        for (int i = 0; i < strNum.length(); i++) {
            if (!Character.isDigit(strNum.charAt(i))) {
                return false;
            }
        }
        return true;
    }
}