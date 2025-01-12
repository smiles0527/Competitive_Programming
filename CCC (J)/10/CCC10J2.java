import java.util.Scanner;

public class CCC10J2
{
    public static int steps(int a, int b, int s)
    {
        int d = a - b;
        int t = a + b;
        int forward = (s / t) * d;
        int r = s % t;
        if (r <= a)
        {
            forward = forward + r;
        }
        else
        {
            forward = forward + 2 * a - r;
        }

        return forward;
    }

    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int a = input.nextInt();
        int b = input.nextInt();
        int c = input.nextInt();
        int d = input.nextInt();
        int s = input.nextInt();
        int nicky = steps(a, b, s);
        int byron = steps(c, d, s);
        if (nicky > byron)
        {
            System.out.println("Nicky");
        }
        else if (byron > nicky)
        {
            System.out.println("Byron");
        }
        else
        {
            System.out.println("Tied");
        }

    }
}
