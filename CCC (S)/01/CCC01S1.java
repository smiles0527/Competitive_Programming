import java.util.*;

public class CCC01S1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String str = input.next();
        int c = 0;
        int d = 0;
        int h = 0;
        int s = 0;
        int total = 0;
        String clubs = "";
        String diamonds = "";
        String hearts = "";
        String spades = "";

        int len = str.length();

        // clubs :D
        int clubc = 0;
        for (int i = 1; i < len; i++)
        {
            char card = str.charAt(i);
            if (card == 'D')
            {
                break;
            }
            clubs += card + " ";
            clubc++;
            c += points(card);
        }
        c += extra(clubc);

        // diamonds :3
        int diamondc = 0;
        for (int i = clubc + 2; i < len; i++)
        {
            char card = str.charAt(i);
            if (card == 'H')
            {
                break;
            }
            diamonds += card + " ";
            diamondc++;
            d += points(card);
        }
        d += extra(diamondc);

        //hearts :O
        int heartsc = 0;
        for (int i = clubc + diamondc + 3; i < len; i++)
        {
            char card = str.charAt(i);
            if (card == 'S')
            {
                break;
            }
            hearts += card + " ";
            heartsc++;
            h += points(card);
        }
        h += extra(heartsc);

        //spades :>

        int spadec = 0;
        for (int i = clubc + diamondc + heartsc + 4; i < len; i++)
        {
            char card = str.charAt(i);
            spades += card + " ";
            spadec++;
            s += points(card);
        }
        s += extra(spadec);
        total = c + d + h + s;


        System.out.println("Cards Dealt      Points");
        System.out.println("Clubs " + clubs + "  " + c);
        System.out.println("Diamonds " + diamonds + "  " + d);
        System.out.println("Hearts " + hearts + "  " + h);
        System.out.println("Spades " + spades + "  " + s);
        System.out.println("           Total  " + total);
    }

    public static int points(char x)
    {
        if (x == 'A')
        {
            return 4;
        }
        if (x == 'K')
        {
            return 3;
        }
        if (x == 'Q')
        {
            return 2;
        }
        if (x == 'J')
        {
            return 1;
        }
        return 0;
    }

    public static int extra(int cards)
    {
        if (cards == 0)
        {
            return 3;
        }
        if (cards == 1)
        {
            return 2;
        }
        if (cards == 2)
        {
            return 1;
        }
        return 0;
    }
}
