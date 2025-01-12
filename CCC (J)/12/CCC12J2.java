import java.util.Scanner;

public class CCC12J2
{
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int depth1 = input.nextInt();
        int depth2 = input.nextInt();
        int depth3 = input.nextInt();
        int depth4 = input.nextInt();
        if (depth1 < depth2 && depth2 < depth3 && depth3 < depth4){
            System.out.println("Fish Rising");}
        else if (depth1 > depth2 && depth2 > depth3 && depth3 > depth4) {
            System.out.println("Fish Diving");}
        else if (depth1 == depth2 && depth2 == depth3 && depth3 == depth4) {
            System.out.println("Fish At Constant Depth");}
        else{
            System.out.println("No Fish");
        }


    }
}

