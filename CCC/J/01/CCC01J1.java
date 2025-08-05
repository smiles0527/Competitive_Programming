import java.util.Scanner;

public class CCC01J1
{
    public static void printSection(int half, int star, int space, boolean isUpper)
    {
        for (int i = 0; i < half; i++)
        {
            for (int s = 0; s < star; s++)
            {
                System.out.print("*");
            }
            for (int s = 0; s < space; s++)
            {
                System.out.print(" ");
            }
            for (int s = 0; s < star; s++)
            {
                System.out.print("*");
            }
            System.out.println();
            if (isUpper)
            {
                star += 2;
                space -= 4;
            }
            else
            {
                star -= 2;
                space += 4;
            }
        }
    }

    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int h = input.nextInt();
        input.close();
        int half = h / 2;
        int star = 1;
        int space = 2 * h - 2;
        printSection(half, star, space, true);
        printSection(half + 1, h, 0, false);
    }
}
