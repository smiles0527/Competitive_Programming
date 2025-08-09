import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class j3v2
{
  public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        long n = input.nextInt();
        for (int i = 0; i < n; i++)
        {
            String str = input.next();
            char[] idk = str.toCharArray();
            String ans = "";
            for (char c : idk)
            {
                if (Character.isUpperCase(c))
                {
                    ans+=c;
                }
            }  
            Pattern pattern = Pattern.compile("-?\\d+");
            Matcher matcher = pattern.matcher(str);      
            long num = 0;
            while (matcher.find())
            {
                num += Long.parseLong(matcher.group());
            }
            System.out.println(ans + num);
            input.close();
        }
    }
}