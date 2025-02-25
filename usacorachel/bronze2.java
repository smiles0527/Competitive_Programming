import java.util.*;

public class bronze2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int[] arr = new int[n];
        int[] freq = new int[n+1];


        for(int i = 0; i < n; i++) {
            arr[i] = input.nextInt();
            freq[arr[i]]++;
        }

        int count = 0;
        for (int i = 0; i <= n; i++) {
            if (i > 0 && freq[i - 1] == 0) {
                count++;
            }

            int ans = Math.max(freq[i], count);

            System.out.println(ans);
        }

        input.close();
    }

}
