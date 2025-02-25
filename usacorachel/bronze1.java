
import java.util.*;

public class bronze1 {


    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int u = input.nextInt();
        input.nextLine();



        char[][] grid = new char[n][n];
        int[][] cost = new int[n][n];

        for (int i = 0; i < n; i++) {
            String line = input.nextLine();
            for (int j = 0; j < n; j++) {
                grid[i][j] = line.charAt(j);
            }
        }

        int count = 0;

        for (int i = 0; i < n/2; i++) {
            for (int j = n/2; j < n; j++) {
                cost[i][j] = count(grid,i,j,n);
                count+=cost[i][j];
            }
        }

        System.out.println(count);

        for (int i = 0; i < u; i++)
        {
            int r = input.nextInt()-1;
            int c = input.nextInt()-1;


            if (grid[r][c] == '#')
            {
                grid[r][c] = '.';
            }
            else
            {
                grid[r][c] = '#';
            }

            int nr = Math.min(r, n - 1 - r);
            int nc = Math.max(c, n - 1 - c);

            int newCost = count(grid,nr,nc,n);


            count -= cost[nr][nc];
            cost[nr][nc] = newCost;
            count += newCost;

            System.out.println(count);
        }

        input.close();
    }

    public static int count(char[][] grid, int i, int j, int n) {
        int count = 0;
        if (grid[i][j] == '#') {
            count++;
        }
        if (grid[i][n-j-1] == '#') {
            count++;
        }
        if (grid[n-1-i][j] == '#') {
            count++;
        }
        if (grid[n-1-i][n-1-j] == '#') {
            count++;
        }
        return Math.min(count, 4-count);
    }
}
