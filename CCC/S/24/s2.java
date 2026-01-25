import java.util.*;

public class s2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int t = input.nextInt();
        int n = input.nextInt();
        input.nextLine();

        for(int i = 0; i < t; i++)
        {
            String str = input.nextLine();

            int[] freq = new int[26];
            int[] comp = new int[n];

            for (int j = 0; j < n; j++)
            {
                char ch = str.charAt(j);
                freq[ch-'a']++;
            }

            for (int j = 0; j < n; j++)
            {
                comp[j] = freq[str.charAt(j)-'a'];
            }

            boolean alex = true;
            for (int j = 0; j+1 < n; j++)
            {
                boolean b1 = (comp[j] > 1);
                boolean b2 = (comp[j + 1] > 1);

                if (b1 == b2)
                {
                    System.out.println("F");
                    alex = false;
                    break;
                }
            }
            if (alex)
            {
                System.out.println("T");
            }
        }

        input.close();

    }

}


