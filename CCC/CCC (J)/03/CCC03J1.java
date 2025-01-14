import java.util.Scanner;

public class CCC03J1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        int t = input.nextInt();
        int s = input.nextInt();
        int h = input.nextInt();
        int line = 3 + (2 * s);
        int half = s + 1;
        for (int i = 0; i < t; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                System.out.print("*");
                for (int x = 0; x < s; x++)
                {
                    System.out.print(" ");
                }
            }
            System.out.print("*");
            System.out.println();
        }
        for (int i = 0; i < line; i++)
        {
            System.out.print("*");
        }
        System.out.println();
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < half; j++)
            {
                System.out.print(" ");
            }
            System.out.print("*");
            System.out.println();
        }
    }

}