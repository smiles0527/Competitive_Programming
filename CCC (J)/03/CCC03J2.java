import java.util.Scanner;

public class CCC03J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        while (true)
        {
            int c = input.nextInt();
            if (c==0){
                break;
            }
            getDimensions(c);
        }

    }

    //end of main
    public static void getDimensions(int c)
    {
        int minDiff = Integer.MAX_VALUE;
        int factor1 = 0;
        int factor2 = 0;
        for (int i = 1; i <= c; i++)
        {
            if (c%i == 0)
            {
                int b = c/i;
                int diff = b-i;
                if (minDiff>diff && diff>=0){
                    minDiff = diff;
                    factor1 = i;
                    factor2 = b;
                }
            }

        }
        int perimeter = 2*(factor1 + factor2);

        System.out.println("Minimum perimeter is " + perimeter + " with dimensions " + factor1 + " x " + factor2);
    }
}