import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;

public class j4v2 {
    
     public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();

        char[] weather = new char[n];
        
        for (int i = 0; i < n; i++)
        {
            weather[i] = input.next().charAt(0);
        }
        ArrayList<Integer> pValues = new ArrayList<>();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char[] subset = Arrays.copyOfRange(weather, i, j+1);
                int pCount = 0; 
                for (int k = 0; k < subset.length; k++)
                {
                    if (subset[k] == 'P')
                    {
                        pCount++;
                    }
                }
                pValues.add(pCount);
            }
        }
        Collections.sort(pValues, Collections.reverseOrder());
        
        System.out.println(pValues.get(0));
        input.close();
     }
}
