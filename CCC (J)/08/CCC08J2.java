import java.util.Scanner;

public class CCC08J2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String[] songs = {"A", "B", "C", "D", "E"};
        while (true)
        {
            int number = input.nextInt();
            int times = input.nextInt();
            if (number!=4)
            {
                if (number==1)
                {
                    for (int i = 0; i < times; i++)
                    {
                        one(songs);
                    }
                }
                else if (number==2)
                {
                    for (int i = 0; i < times; i++)
                    {
                        two(songs);
                    }
                }
                else if (number==3)
                {
                    three(songs);
                }

            }
            if (number==4)
            {
                break;
            }
        }
        for (int i = 0; i < songs.length; i++)
        {
            System.out.print(songs[i] + " ");
        }
    }

    public static void one(String[] songs)
    {
        String temp = songs[4];
        songs[4] = songs[0];
        songs[0] = songs[1];
        songs[1] = songs[2];
        songs[2] = songs[3];
        songs[3] = temp;
    }
    public static void two(String[] songs)
    {
        String temp = songs[0];
        songs[0] = songs[4];
        songs[4] = songs[3];
        songs[3] = songs[2];
        songs[2] = songs[1];
        songs[1] = temp;
    }
    public static void three(String[] songs)
    {
        String temp = songs[0];
        songs[0] = songs[1];
        songs[1] = temp;
    }
}

