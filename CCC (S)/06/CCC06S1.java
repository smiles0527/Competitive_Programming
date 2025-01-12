import java.util.Scanner;

public class CCC06S1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String mom = input.next();
        String dad = input.next();
        int n = input.nextInt();
        for (int i = 0; i < n; i++)
        {
            String baby = input.next();
            check(mom, dad, baby);
        }
    }

    public static void check(String mom, String dad, String baby)
    {
        for (int i = 0; i < 5; i++)
        {
            char b = baby.charAt(i);
            if (Character.isUpperCase(b))
            {
                if (!mom.contains(String.valueOf(b)) && !dad.contains(String.valueOf(b)))
                {
                    System.out.println("Not their baby!");
                    return;
                }
            }
            if (Character.isLowerCase(b))
            {
                if (!mom.contains(String.valueOf(b)) || !dad.contains(String.valueOf(b)))
                {
                    System.out.println("Not their baby!");
                    return;
                }
            }
        }
        System.out.println("Possible baby.");
    }
}
