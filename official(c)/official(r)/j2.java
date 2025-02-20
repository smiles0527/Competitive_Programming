import java.util.*;

public class j2 {
    public static void main(String[] args) 
    {
        Scanner input = new Scanner(System.in);

        int d = input.nextInt();
        int e = input.nextInt();

        for (int i = 0; i < e; i++)
        {
            String str = input.next();
            int a = input.nextInt();
            

            if (str.equals("+"))
            {
                d+=a;
            }
            else if (str.equals("-"))
            {
                d-=a;
            }
            
        }

        System.out.println(d);
        input.close();
        

    }
}