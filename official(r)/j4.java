import java.util.Scanner;

public class j4 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        int n = input.nextInt();
        char[] weather = new char[n];
        
        for (int i = 0; i < n; i++) {
            weather[i] = input.next().charAt(0);
        }
        
        int max = 0;
        boolean hasP = false;
        
        for (int i = 0; i < n; i++) {
            if (weather[i] == 'P') {
                hasP = true;
                
                int before = 0;
                for (int j = i-1; j >= 0 && weather[j] == 'S'; j--) {
                    before++;
                }
                
                int after = 0; 
                for (int j = i+1; j < n && weather[j] == 'S'; j++) {
                    after++;
                }
                
                int count = before + 1 + after;
                max = Math.max(max, count);
            }
        }
        
        if (!hasP) {
            max = n - 1;
        }
        
        System.out.println(max);
        input.close();
    }
}