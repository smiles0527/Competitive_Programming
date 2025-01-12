import java.util.Scanner;

public class CCC11J3
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int a = input.nextInt();
        int b = input.nextInt();
        int c = 0;
        int count = 2;
        while ((a - b) <= b)
        {
            count++;
            c = a - b;
            a = b;
            b = c;
        }
        System.out.println(count);
    }
}