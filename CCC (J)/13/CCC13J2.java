import java.util.*;

public class CCC13J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String sign = input.next();
        int len = sign.length();
        boolean yes = false;
        for (int i = 0; i < len; i++)
        {
            char idk = sign.charAt(i);
            if (idk == 'I' || idk == 'O' || idk == 'S' || idk == 'H'
                    || idk == 'Z' || idk == 'Z' || idk == 'N')
            {
                yes = true;
            }
            else
            {
                yes = false;
            }
        }
        if (yes)
        {
            System.out.println("YES");
        }
        else
        {
            System.out.println("NO");
        }
    }
}
