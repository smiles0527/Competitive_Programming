import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;


public class B1191 {
    public static void main(String[] args) throws IOException
    {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int[] peb = {0, 1, 2};
        int[] count = new int[3];

        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i<n; i++)
        {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken()) -1;
            int b = Integer.parseInt(st.nextToken())-1;
            int g = Integer.parseInt(st.nextToken())-1;

            int temp = peb[a];
            peb[a] = peb[b];
            peb[b] = temp;

            count[peb[g]]++;

        }
        int ans = Math.max(count[0], Math.max(count[1], count[2]));
        System.out.println(ans);

        br.close();

    }

}
