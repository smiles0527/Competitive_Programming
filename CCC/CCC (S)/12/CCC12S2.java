import java.util.*;

public class CCC12S2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String number = input.nextLine();
        int len = number.length();
        int total = 0;
        int oldr = Integer.MAX_VALUE;
        int olds = 0;
        for (int i = 0; i < len; i += 2)
        {
            char ach = number.charAt(i);
            char rch = number.charAt(i + 1);
            int r = roman(rch);
            int a = Character.getNumericValue(ach);
            int sum = a * r;
            total += sum;
            if (r > oldr)
            {
                total -= 2 * olds;
            }
            olds = sum;
            oldr = r;
        }
        System.out.println(total);
        input.close();
    }

    public static int roman(char ch)
    {
        if (ch == 'I')
        {
            return 1;
        }
        if (ch == 'V')
        {
            return 5;
        }
        if (ch == 'X')
        {
            return 10;
        }
        if (ch == 'L')
        {
            return 50;
        }
        if (ch == 'C')
        {
            return 100;
        }
        if (ch == 'D')
        {
            return 500;
        }
        return 1000;
    }
}

