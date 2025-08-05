import java.util.Scanner;
public class CCC03J3
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        int position = 1;
        while (position <= 100)
        {
            int number = input.nextInt();
            position = position + number;
            if (number == 0)
            {
                System.out.println("You Quit!");
                break;
            }
            if (position == 9)
            {
                position = 34;
            }
            else if (position == 40)
            {
                position = 64;
            }
            else if (position == 67)
            {
                position = 86;
            }
            else if (position == 54)
            {
                position = 19;
            }
            else if (position == 90)
            {
                position = 42;
            }
            else if (position == 99)
            {
                position = 77;
            }
            else if (position > 100)
            {
                position = position - number;
            }
            System.out.println("You are now on square " + position);
            if (position == 100)
            {
                System.out.println("You Win!");
                break;
            }
        }
    }
}