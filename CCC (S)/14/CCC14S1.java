import java.util.Scanner;
import java.util.ArrayList;

public class CCC14S1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int k = input.nextInt();
        ArrayList<Integer> friends = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            friends.add(i+1);
        }
        int m = input.nextInt();
        for (int rounds = 0; rounds < m ; rounds++) {
            int r = input.nextInt();
            int size = friends.size();
            for (int i = 0; i < size; i++) {
                if ((i+1)%r==0)
                {
                    friends.remove(i);
                    friends.add(i, -1);
                }
            }
            for (int i = 0; i < friends.size(); i++)
            {
                if (friends.get(i) == -1)
                {
                    friends.remove(i);
                    i--;
                }
            }
        }
        for (Integer friend : friends)
        {
            System.out.println(friend);
        }
    }
}