import java.util.Scanner;

public class j5 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int R = input.nextInt();
        int C = input.nextInt();
        int M = input.nextInt();

        int[] prev = new int[C];
        int[] cur = new int[C];
        
        for (int j = 0; j < C; j++) {
            prev[j] = (j % M) + 1;
        }
        
        //DSA !!! !! ! !  ! ! !
        for (int i = 1; i < R; i++) {
            for (int j = 0; j < C; j++) {
                int cost = (int)(((long)i * C + j) % M) + 1;
                int mn = prev[j];
                if (j > 0) {
                    mn = Math.min(mn, prev[j-1]);
                }
                if (j < C - 1) {
                    mn = Math.min(mn, prev[j+1]);
                }
                cur[j] = cost + mn;
            }
            int[] temp = prev;
            prev = cur;
            cur = temp;
        }
        
        int ans = prev[0];
        for (int j = 1; j < C; j++) {
            ans = Math.min(ans, prev[j]);
        }
        
        System.out.println(ans);
        input.close();
    }
}