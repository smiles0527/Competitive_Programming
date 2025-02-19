import java.util.Scanner;
public class j2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int d = input.nextInt();
        int e = input.nextInt();
        int current = d;
        
        for (int i = 0; i < e; i++) {
            String op = input.next();
            int q = input.nextInt();
            if (op.equals("+")) {
                current += q;
            } else {
                current -= q;
            }
        }
        
        System.out.println(current);
        input.close();
    }
}