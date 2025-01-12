import java.util.Scanner;

public class CCC07J4
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String text1 = input.nextLine().replace(" ", "");
        String text2 = input.nextLine().replace(" ", "");
        int len = text1.length();
        String temp = text2;

        if (text1.length() != text2.length())
        {
            System.out.println("Is not an anagram.");
            return;
        }
        for (int i = 0; i < len; i++)
        {
            char ch = text1.charAt(i);
            int index = temp.indexOf(ch);
            if (index == -1)
            {
                System.out.println("Is not an anagram.");
                return;
            }

            temp = temp.substring(0, index) + temp.substring(index + 1);
        }
        int lent = temp.length();

        if (lent == 0)
        {
            System.out.println("Is an anagram.");
        }
        else
        {
            System.out.println("Is not an anagram.");
        }
    }
}
