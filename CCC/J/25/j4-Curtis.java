import java.util.Scanner;

public class j4 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        int n = input.nextInt();
        char[] weather = new char[n];
        
        for (int i = 0; i < n; i++) {
            weather[i] = input.next().charAt(0);
        }
      
 
        int before = 0, rain = 0, best = 0;
        for (int after = 0; after < n; after++){
            if (weather[after] == 'P') rain++;
            while(rain > 1){
                if (weather[before] == 'P') rain--;
                before++;
            }
            best = Math.max(best, after - before + 1);
        }

        System.out.println(best);
        input.close();
    }
}