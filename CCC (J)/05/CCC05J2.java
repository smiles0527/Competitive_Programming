import java.util.Scanner;

public class CCC05J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int s = input.nextInt();
        int f = input.nextInt();
        int rsaCount = 0;
        for (int i = s; i <= f; i++)
        {
            int factorCount = 0;
            for (int x = 1; x <= i; x++)
            {
                if (i % x == 0)
                {
                    factorCount++;
                }
            }
            if (factorCount == 4)
            {
                rsaCount++;
            }
        }
        System.out.println("The number of RSA numbers between " + s + " and " + f + " is " + rsaCount);


    }
}