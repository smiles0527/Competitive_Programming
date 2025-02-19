import java.util.Scanner;

public class j4 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        int N = input.nextInt();
        char[] days = new char[N];
        for (int i = 0; i < N; i++) {
            days[i] = input.next().charAt(0);
        }
        
        
        int[] left = new int[N];
        left[0] = (days[0] == 'S' ? 1 : 0);
        for (int i = 1; i < N; i++) {
            left[i] = (days[i] == 'S' ? left[i-1] + 1 : 0);
        }
        
        
        int[] right = new int[N];
        right[N-1] = (days[N-1] == 'S' ? 1 : 0);
        for (int i = N-2; i >= 0; i--) {
            right[i] = (days[i] == 'S' ? right[i+1] + 1 : 0);
        }
        
        
        int ans = 0;
        boolean hasP = false;
        for (int i = 0; i < N; i++) {
            if (days[i] == 'P') {
                hasP = true;
                int leftCount = (i > 0 ? left[i-1] : 0);
                int rightCount = (i < N-1 ? right[i+1] : 0);
                ans = Math.max(ans, leftCount + 1 + rightCount);
            }
        }
        
        if (!hasP) {
            ans = N - 1;
        }
        
        System.out.println(ans);
        input.close();
    }
}