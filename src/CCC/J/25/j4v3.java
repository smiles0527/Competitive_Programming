import java.util.Scanner;

public class j4v3 {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        char[] weather = new char[n];

        for (int i = 0; i < n; i++)
        {
            weather[i] = input.next().charAt(0);
        }

        boolean alexRain = false;
        int rain = 0, before = 0, best = 0;
        for (int i = 0; i < n; i++)
        {
            if (weather[i] == 'P')
            {
                alexRain = true; //PSPSSPPS
                rain++;
            }
            while (rain>1)
            {
                if (weather[before] == 'P')
                {
                    rain--;
                }
                before++;
            }
            best = Math.max(best, i-before+1);
        }

        if (!alexRain)
        {
            best--;
        }
        System.out.println(best);

        input.close();
    }
}
