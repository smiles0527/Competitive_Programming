import java.util.*;

public class j5v2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int R = scanner.nextInt(); // Number of rows
        int C = scanner.nextInt(); // Number of columns
        int M = scanner.nextInt(); // Modulo value for cost calculation
        scanner.close();
        
        int[] prev = new int[C]; // Previous row's minimum path cost
        int[] cur = new int[C]; // Current row's minimum path cost
        
        // Initializing the first row with cost values based on column indices
        for (int j = 0; j < C; j++) {
            prev[j] = (j % M) + 1;
        }
        
        // Iterating through the rows to compute the minimum path sum
        for (int i = 1; i < R; i++) {
            for (int j = 0; j < C; j++) {
                // Compute cost for the current cell based on row and column index
                int cost = (int) (((long) i * C + j) % M) + 1;
                
                // Find the minimum cost from the previous row (above, left-diagonal, and right-diagonal)
                int mn = prev[j];
                if (j > 0) mn = Math.min(mn, prev[j - 1]);
                if (j < C - 1) mn = Math.min(mn, prev[j + 1]);
                
                // Update current row's minimum path sum
                cur[j] = cost + mn;
            }
            
            // Swap current row with previous row for the next iteration
            int[] temp = prev;
            prev = cur;
            cur = temp;
        }
        
        // Find the minimum value in the last row which represents the minimum path sum
        int ans = prev[0];
        for (int j = 1; j < C; j++) {
            ans = Math.min(ans, prev[j]);
        }
        
        // Output the minimum path sum
        System.out.println(ans);
    }
}