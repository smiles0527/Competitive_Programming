package contest3;
import java.util.Scanner;

public class B_sequences {
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);

        int t = input.nextInt();

        while (t-- > 0) {

            int n = input.nextInt();
            int k = input.nextInt();


            int[] arr = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = input.nextInt();
            }

            int parts = 1;
            int prev = arr[0];


            for (int i = 1; i < n; i++) {

                if (arr[i] != prev) {
                    parts++;
                    prev = arr[i];
                }
            }

            if (parts <= k) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }

        input.close();
    }
}
