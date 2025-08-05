import java.util.Scanner;

public class CCC15J5 {
    public static int pie(int n, int k, int min) {
        if (n == k) {
            return 1;
        }
        if (k == 1) {
            return 1;
        }

        int count = 0;
        int max = n / k;
        for (int i = min; i <= max; i++) {
            count += pie(n - i, k - 1, i);

        }

        return count;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int k = scanner.nextInt();

        System.out.println(pie(n, k, 1));

        scanner.close();
    }
}
