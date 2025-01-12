import java.util.*;

public class CCC05J4
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);

        int Cols = input.nextInt();
        int Rows = input.nextInt();
        int CutCols = input.nextInt();
        int CutRows = input.nextInt();
        int steps = input.nextInt();

        boolean[][] yes = new boolean[Rows][Cols];

        for (int r = 0; r < Rows; r++)
        {
            for (int c = 0; c < Cols; c++)
            {
                // corner 1
                if (r < CutRows && c < CutCols)
                {
                    yes[r][c] = true;
                }
                // corner 2
                if (r < CutRows && c > Cols - CutCols - 1)
                {
                    yes[r][c] = true;
                }
                //corner 3
                if (r > Rows - CutRows - 1 && c < CutCols)
                {
                    yes[r][c] = true;
                }
                //corner 4
                if (r > Rows - CutRows - 1 && c > Cols - CutCols - 1)
                {
                    yes[r][c] = true;
                }
            }
        }

        int cr = 0;
        int cc = CutCols;
        yes[cr][cc] = true;
        for (int i = 0; i < steps; i++)
        {
            if (cc >= Cols / 2)
            {
                if (cc + 1 < Cols && !yes[cr][cc + 1])
                {
                    cc++;
                    yes[cr][cc] = true;
                }
                else if (cr + 1 < Rows && !yes[cr + 1][cc])
                {
                    cr++;
                    yes[cr][cc] = true;
                }
                else if (cc - 1 >= 0 && !yes[cr][cc - 1])
                {
                    cc--;
                    yes[cr][cc] = true;
                }
                else if (cr - 1 >= 0 && !yes[cr - 1][cc])
                {
                    cr--;
                    yes[cr][cc] = true;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (cc - 1 >= 0 && !yes[cr][cc - 1])
                {
                    cc--;
                    yes[cr][cc] = true;
                }
                else if (cr - 1 >= 0 && !yes[cr - 1][cc])
                {
                    cr--;
                    yes[cr][cc] = true;
                }
                else if (cc + 1 < Cols && !yes[cr][cc + 1])
                {
                    cc++;
                    yes[cr][cc] = true;
                }
                else if (cr + 1 < Rows && !yes[cr + 1][cc])
                {
                    cr++;
                    yes[cr][cc] = true;
                }
                else
                {
                    break;
                }
            }
        }
        System.out.println(cc + 1);
        System.out.println(cr + 1);

    }

    private static void print2D(boolean[][] table, int cr, int cc)
    {
        for (int r = 0; r < table.length; r++)
        {
            for (int c = 0; c < table[r].length; c++)
            {
                if (r == cr && c == cc)
                {
                    System.out.print("@");
                }
                else if (table[r][c])
                {
                    System.out.print("#");
                }
                else
                {
                    System.out.print("*");
                }
            }
            System.out.println();
        }
        System.out.println("///////////////////////////");

    }
}