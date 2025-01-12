import java.util.*;

public class CCC02J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        boolean idk = false;
        while (!idk)
        {
            String spell = input.nextLine();
            int len = spell.length();
            if (spell.equals("quit!"))
            {
                break;
            }
            else if (len > 4 && spell.substring(len - 2, len).equals("or") &&
                    spell.charAt(len - 3) != 'a' && spell.charAt(len - 3) != 'e' &&
                    spell.charAt(len - 3) != 'i' && spell.charAt(len - 3) != 'o'
                    && spell.charAt(len - 3) != 'u' && spell.charAt(len - 3) != 'y')
            {
                System.out.println(spell.substring(0, len - 2) + "our");
            }
            else
            {
                System.out.println(spell);
            }
        }
    }
}
