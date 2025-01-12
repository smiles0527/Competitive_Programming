import java.util.*;

public class CCC13J3
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String something = input.nextLine();
        input.close();
        int year = Integer.parseInt(something) + 1;

        while (!distinct(year))
        {
            year++;
        }
        System.out.println(year);

    }

    public static boolean distinct(int year)
    {
        String years = Integer.toString(year);
        int len = years.length();
        for (int i = 0; i < len; i++)
        {
            char n = years.charAt(i);
            if (years.indexOf(n) != years.lastIndexOf(n))
            {
                return false;
            }
        }
        return true;
    }

}
