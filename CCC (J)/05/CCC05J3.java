import java.util.Collections;
import java.util.Scanner;
public class CCC05J3 {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String[] names = new String[100000];
        String[] turns = new String[100000];
        int count = 0;
        while (true)
        {
            String turn = input.next();
            String street = input.next();
            names[count] = street;
            if (turn.equals("R")){
                turns[count] = "LEFT";
            }
            if (turn.equals("L")){
                turns[count] = "RIGHT";
            }
            count++;
            if (street.equals("SCHOOL")) {
                break;
            }
        }
        for (int i = count-1; i > 0; i--) {
            System.out.println("Turn " + turns[i] + " onto " + names[i-1] + " street." );
        }
        System.out.println("Turn " + turns[0] + " into your HOME.");
    }
}
