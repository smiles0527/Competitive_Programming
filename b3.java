import java.util.*;

public class b3 {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();
        int q = input.nextInt();

        String str = input.next();


        long[] max = new long[n];
        Arrays.fill(max, -1);


        for (int j = 1; j < n - 1; j++)
        {
            for (int i = 0; i < j; i++)
            {
                if (str.charAt(i) == str.charAt(j)) continue;
                for (int k = j + 1; k < n; k++)
                {
                    if (str.charAt(j) == str.charAt(k))
                    {
                        long value = (long) (j - i) * (k - j);
                        max[j] = Math.max(max[j], value);
                    }
                }
            }
        }


        long[] pref = new long[n];
        pref[0] = max[0];
        for (int i = 1; i < n; i++) {
            pref[i] = Math.max(pref[i - 1], max[i]);
        }


        for (int i = 0; i < q; i++) {
            int l = input.nextInt() - 1;
            int r = input.nextInt() - 1;

            long result;

            if (l == 0)
            {
                result = pref[r];
            }
            else
            {
                result = Math.max(pref[r], max[l]);
            }
            if (result == -1)
            {
                System.out.println(-1);
            }
            else
            {
                System.out.println(result);
            }
        }
    }
}
