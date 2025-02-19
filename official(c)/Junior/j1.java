import java.util.Scanner;

public class j1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int c = input.nextInt();
        int p = input.nextInt();
        int total = c * p;
        System.out.println(n <= total ? "yes" : "no");
        input.close();
    }
}