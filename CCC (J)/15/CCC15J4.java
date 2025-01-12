import java.util.*;

public class CCC15J4 {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int time = 0;
        int[] answers = new int[101];
        int[] received = new int[101];
        int[] sent = new int[101];
        for (int i = 0; i < n; i++) {
            String command = input.next();
            int person = input.nextInt();
            if (command.equals("W"))
            {
                time += person - 2;
            }
            else if (command.equals("R"))
            {
                sent[person] = -1;
                received[person] = time;
            }
            else if (command.equals("S"))
            {
                sent[person] = 1;
                answers[person] += time - received[person];
            }
            time++;
        }
        for (int i = 1; i <= 100; i++)
        {
            if (sent[i] < 0) System.out.println(i + " -1");
            else if (answers[i] > 0) System.out.println(i + " " + answers[i]);
        }
    }
}