import java.util.*;

public class CCC04J4
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        String key = input.nextLine();
        String msg = input.nextLine();
        int len = msg.length();
        int indexing = 0;
        for (int i = 0; i < len; i++) {
            char x = msg.charAt(i);
            int index = alphabet.indexOf(x);
            if (index >= 0) {
                int shifti = key.charAt(indexing) - 'A';
                int nx = x + shifti;
                if (nx > 'Z')
                {
                    nx = 'A' + (nx - 'Z' - 1);
                }

                char fin = (char) nx;

                System.out.print(fin);

                int keyl = key.length();
                indexing++;
                if (indexing >= keyl)
                {
                    indexing = 0;
                }
            }
        }

    }
}
