import java.util.Scanner;
public class CCC07J3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int[] array = {100, 500, 1000, 5000, 10000, 25000, 50000, 100000, 500000, 1000000};
        int cases = input.nextInt();

        for (int i = 0; i < cases; i++) {
            int n = input.nextInt();
            array[n-1] = 0;
        }

        int sum = 0;
        for(int i = 0; i < 10; i++) sum +=array[i];
        int avg = sum/(10-cases);
        int offer = input.nextInt();
        System.out.println(offer > avg ? "deal" : "no deal");
    }
}
