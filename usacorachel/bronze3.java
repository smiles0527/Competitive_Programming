import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // Scanner to take input
        Scanner sc = new Scanner(System.in);
        
        // Read number of test cases
        int T = sc.nextInt();
        
        // Loop through all test cases
        while (T-- > 0) {
            // Read N (size of array) and K (maximum allowed segments)
            int N = sc.nextInt();
            int K = sc.nextInt();
            
            // Create an array to store the sequence
            int[] S = new int[N];
            for (int i = 0; i < N; i++) {
                S[i] = sc.nextInt();
            }

            // We'll count how many parts we can divide the array into
            int parts = 1;  // We start with one part
            int lastPart = S[0];  // The first element is the starting part
            
            // Loop through the array to find splits
            for (int i = 1; i < N; i++) {
                // If current element is different from the last part, split into a new part
                if (S[i] != lastPart) {
                    parts++;
                    lastPart = S[i];  // Start new part
                }
            }

            // Output the result: If the number of parts is less than or equal to K, print YES
            if (parts <= K) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }

        // Close the scanner
        sc.close();
    }
}
r