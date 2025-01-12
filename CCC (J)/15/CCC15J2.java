import java.util.*;

public class CCC15J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int hcount = 0;
        int scount = 0;
        String question = input.nextLine();
        int len = question.length();
        for (int i = 0; i + 3 <= len; i++)
        {
            String sub = question.substring(i, i + 3);
            if (sub.equals(":-)"))
            {
                hcount++;
            }
            else if (sub.equals(":-("))
            {
                scount++;
            }
        }
        if (scount == 0 && hcount == 0)
        {
            System.out.println("none");
        }
        else if (scount == hcount)
        {
            System.out.println("unsure");
        }
        else if (hcount > scount)
        {
            System.out.println("happy");
        }
        else if (hcount < scount)
        {
            System.out.println("sad");
        }
    }
}
