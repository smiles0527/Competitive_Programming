import java.util.*;

public class CCC06J3
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        while (true)
        {
            String s = input.next();
            if (s.equals("halt"))
            {
                break;
            }
            int t = 0;
            int len = s.length();
            for (int i = 0; i < len; i++)
            {
                char ch = s.charAt(i);
                if (ch == 'a' || ch == 'd' || ch == 'g' ||
                        ch == 'j' || ch == 'm' || ch == 'p' || ch == 't' ||
                        ch == 'w')
                {
                    t++;
                }
                else if (ch == 'b' || ch == 'e' || ch == 'h' || ch == 'k' ||
                        ch == 'n' || ch == 'q' || ch == 'u' || ch == 'x')
                {
                    t += 2;
                }
                else if (ch == 'c' || ch == 'f' || ch == 'i' || ch == 'l' ||
                        ch == 'o' || ch == 'r' || ch == 'v' || ch == 'y')
                {
                    t += 3;
                }
                else if (ch == 's' || ch == 'z')
                {
                    t += 4;
                }
                if (i > 0)
                {
                    char pch = s.charAt(i - 1);
                    if (("abc".indexOf(pch) >= 0 && "abc".indexOf(ch) >= 0) ||
                            ("def".indexOf(pch) >= 0 && "def".indexOf(ch) >= 0) ||
                            ("ghi".indexOf(pch) >= 0 && "ghi".indexOf(ch) >= 0) ||
                            ("jkl".indexOf(pch) >= 0 && "jkl".indexOf(ch) >= 0) ||
                            ("mno".indexOf(pch) >= 0 && "mno".indexOf(ch) >= 0) ||
                            ("pqrs".indexOf(pch) >= 0 && "pqrs".indexOf(ch) >= 0) ||
                            ("tuv".indexOf(pch) >= 0 && "tuv".indexOf(ch) >= 0) ||
                            ("wxyz".indexOf(pch) >= 0 && "wxyz".indexOf(ch) >= 0))
                    {
                        t += 2;
                    }
                }
            }
            System.out.println(t);
        }
        input.close();
    }
}
