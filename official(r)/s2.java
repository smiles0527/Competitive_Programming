import java.util.*;
/*Cyrene, the captain of the Cryptogram Cracking Club (CCC), came across a concerningly
long cipher. Conveniently, this cipher is composed of lower-case characters (a-z). Comfortingly, the cipher is composed of a pattern that repeats infinitely.
Cyrene wishes to locate the c-th character of the cipher. To make your job easier, the CCC
members have extracted the repeated pattern and compressed it using the Run-Length
Encoding (RLE) algorithm, which replaces consecutive repeated characters with a single
occurrence of the character followed by a count of how many times it was repeated. For
example, for the pattern aaaabccdddd, the RLE algorithm outputs a4b1c2d4.
You are given the output of the RLE algorithm for a certain pattern. Can you determine
the c-th character of the long cipher that is formed by repeating this pattern infinitely? */

public class s2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        String temp = input.nextLine();
        int c = input.nextInt();

        char[] table = new char[c/2];
        int[] count = new int[c/2];

        for (int i = 0; i < temp.length(); i++) {
            table[i] = temp.charAt(i);
            count[i] = temp.charAt(i+1);
        }
        int total = 0;

        for (int i = 0; i < c/2; i++) {
            total += count[i];
        }
        
        String str = "";

        for (int i = 0; i < c/2; i++) {
            for (int j = 0; j < count[i]; j++) {
                str += table[i];

            }
        }

        System.out.println(str);







        input.close();
    }
}
