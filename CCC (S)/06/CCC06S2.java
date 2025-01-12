import java.util.*;

public class CCC06S2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String plain = input.nextLine();
        String c1 = input.nextLine();
        String c2 = input.nextLine();
        input.close();
        for (int i = 0; i < c2.length(); i++)
        {
            int index = c1.indexOf(c2.charAt(i));
            if (index == -1)
            {
                System.out.print(".");
            }
            else
            {
                System.out.print(plain.charAt(index));
            }
        }
        System.out.println();
    }
}
