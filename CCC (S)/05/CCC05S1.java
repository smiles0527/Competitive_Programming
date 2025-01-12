import java.util.*;

public class CCC05S1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int cases = input.nextInt();
        for (int i = 0; i < cases; i++)
        {
            String number = input.next();
            System.out.println(convert(number));


        }
    }


    public static String convert(String s)
    {
        String result = "";
        String noDash = s.replace("-", "");
        for (int i = 0; i < 10; i++)
        {
            char c = noDash.charAt(i);
            if (c == '1')
            {
                result += "1";
            }
            else if (c == '2' || c == 'A' || c == 'B' || c == 'C')
            {
                result += "2";
            }
            else if (c == '3' || c == 'D' || c == 'E' || c == 'F')
            {
                result += "3";
            }
            else if (c == '4' || c == 'G' || c == 'H' || c == 'I')
            {
                result += "4";
            }
            else if (c == '5' || c == 'J' || c == 'K' || c == 'L')
            {
                result += "5";
            }
            else if (c == '6' || c == 'M' || c == 'N' || c == 'O')
            {
                result += "6";
            }
            else if (c == '7' || c == 'P' || c == 'Q' || c == 'R' || c == 'S')
            {
                result += "7";
            }
            else if (c == '8' || c == 'T' || c == 'U' || c == 'V')
            {
                result += "8";
            }
            else if (c == '9' || c == 'W' || c == 'X' || c == 'Y' || c == 'Z')
            {
                result += "9";
            }
            else if (c == '0')
            {
                result += "0";
            }
        }
        String uwu = result;
        result = uwu.substring(0, 3) + "-" + uwu.substring(3, 6) + "-" + uwu.substring(6);
        return result;

    }
}
