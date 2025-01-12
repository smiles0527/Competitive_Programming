import java.util.Scanner;

public class CCC11J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int h = input.nextInt();
        int M = input.nextInt();
        input.close();
        int t = 1;
        int A = Integer.MAX_VALUE;
        while (t <= M && A > 0)
        {
            A = -6 * t * t * t * t + h * t * t * t + 2 * t * t + t;
            t = t + 1;
        }

        if (A > 0)
        {
            System.out.println("The balloon does not touch ground in the given time.");
        }
        else
        {
            System.out.println("The balloon first touches ground at hour:\n" + (t - 1));

        }
    }
}
