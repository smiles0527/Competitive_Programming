import java.util.*;
public class s1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();

        int[] arr1 = new int[n/2];
        int[] arr2 = new int[n/2];

        for (int i = 0; i < n/2; i++) {
            arr1[i] = input.nextInt();
        }
        for (int i = 0; i < n/2; i++) {
            arr2[i] = input.nextInt();
        }

        int count = 0;

        for (int i = 0; i < n/2; i++) {
            if (arr1[i] == arr2[i]) {
                count+=2;
            }
        }

        System.out.println(count);

        input.close();
    }
}
