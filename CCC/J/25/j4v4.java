import java.util.Scanner;

public class j4v4 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int M = input.nextInt();
        char[] weather = new char[M];

        for (int i = 0; i < M; i++)
        {
            String str = input.next();
            weather[i] = str.charAt(0);
        }
        boolean hasRain = false;
        int rain = 0, before = 0, max = 0;

        for (int i = 0; i < M; i++)
        {
            if (weather[i] == 'P')
            {
                rain++;
                hasRain = true;
            }
            while (rain>1)
            {
                if (weather[before] == 'P')
                {
                    rain--;
                }
                before++;
            }
            max = Math.max(max, i-before+1);
        }

        if (!hasRain)
        {
            max--;
        }
        System.out.println(max);
        input.close();
    }
}
