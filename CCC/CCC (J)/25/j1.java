import java.util.*;

public class j1 
{
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int c = input.nextInt();
        int p = input.nextInt();

        int total = c*p;

        if (total >= n)
        {
            System.out.println("yes");
        }
        else
        {
            System.out.println("no");
        }

        input.close();
    
    }
}
