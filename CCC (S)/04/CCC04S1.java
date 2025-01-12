import java.util.*;

public class CCC04S1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        for (int i = 0; i < n; i++)
        {
            String w1 = input.next();
            String w2 = input.next();
            String w3 = input.next();
            if (w1.startsWith(w2) || w1.startsWith(w3) ||
                    w2.startsWith(w3) || w2.startsWith(w1) ||
                    w3.startsWith(w1) || w3.startsWith(w2) ||
                    w1.endsWith(w2) || w1.endsWith(w3) ||
                    w2.endsWith(w3) || w2.endsWith(w1) ||
                    w3.endsWith(w1) || w3.endsWith(w2))
            {
                System.out.println("No");
            }
            else
            {
                System.out.println("Yes");
            }
        }
    }
}
