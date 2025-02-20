import java.util.*;

public class main {
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int a = input.nextInt();
        int b = input.nextInt();
        int x = input.nextInt();
        int y = input.nextInt();

        int per1 = 2 * (a + x + Math.max(b, y));  
        int per2 = 2 * (Math.max(a, x) + b + y);

        System.out.println(Math.min(per1, per2));
        input.close();
    }
}