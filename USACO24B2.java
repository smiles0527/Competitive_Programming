import java.util.*;

public class USACO24B2 {
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);

        int n = input.nextInt();
        int[] nums = new int[n];

        for (int i = 0; i < n; i++) {
            nums[i] = input.nextInt();
        }

        int[] numcount = new int[n+1];
        int[] index2 = new int[n+1];
        boolean[] visited = new boolean[n+1];


        for (int i = n - 1; i >= 0; i--) {
            int num = nums[i];
            numcount[num]++;
            if (numcount[num] == 2) {
                index2[num] = i;
            }
        }


        int count = 0;
        int unique = 0;

        for (int i = 0; i < n; i++) {
            int num = nums[i];

            if (numcount[num] > 1 && i == index2[num]) {
                count += unique;

                if (numcount[num] > 2) {
                    count--;
                }
            }

            if (!visited[num]) {
                visited[num] = true;
                unique++;
            }
        }

        System.out.println(count);
    }
}
