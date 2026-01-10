import java.util.*;

public class CCC01S2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int x = input.nextInt();
        int y = input.nextInt();
        input.close();

        int size = (int) Math.sqrt(y - x) + 1;
        int[][] spiral = new int[size][size];
        int nx = size / 2;
        int ny = size / 2;

        if (size % 2 == 0)
        {
            nx--;
            ny--;
        }

        int n = x;
        int direction = 4; // 1r 2u 3l 4d
        spiral[nx][ny] = n;
        int count = 0;
        int max = 1;
        boolean idk = false;

        while (n < y)
        {
            n++;
            if (direction == 1) ny++;
            else if (direction == 2) nx--;
            else if (direction == 3) ny--;
            else nx++;

            count++;
            spiral[nx][ny] = n;

            if (count == max)
            {
                count = 0;
                direction++;
                if (direction == 5) direction = 1;
                if (idk)
                {
                    max++;
                    idk = false;
                }
                else
                {
                    idk = true;
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (spiral[i][j] != 0)
                {
                    if (spiral[i][j] < 10)
                    {
                        System.out.print(" " + spiral[i][j] + " ");
                    } else {
                        System.out.print(spiral[i][j] + " ");
                    }
                }
                else
                {
                    System.out.print("   ");
                }
            }
            System.out.println();
        }
    }
}
//uwu