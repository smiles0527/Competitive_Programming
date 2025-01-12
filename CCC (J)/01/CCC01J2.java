import java.util.Scanner;

public class CCC01J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        int x = input.nextInt();
        int m = input.nextInt();
        boolean hasN = false;
        for (int n = 1; n < m; n++)
        {
            if ((x * n) % m == 1)
            {
                System.out.println(n);
                hasN = true;
            }
        }
        if (!hasN)
        {
            System.out.println("No such integer exists.");
        }
    }
}