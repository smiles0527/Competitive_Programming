import java.util.*;

public class CCC11J4{

    public static void main(String[] args) {
        List<int[]> dangers = new ArrayList<>();
        dangers.add(new int[]{0, -1});
        dangers.add(new int[]{0, -2});
        dangers.add(new int[]{0, -3});
        dangers.add(new int[]{1, -3});
        dangers.add(new int[]{2, -3});
        dangers.add(new int[]{3, -3});
        dangers.add(new int[]{3, -4});
        dangers.add(new int[]{3, -5});
        dangers.add(new int[]{4, -5});
        dangers.add(new int[]{5, -5});
        dangers.add(new int[]{5, -4});
        dangers.add(new int[]{5, -3});
        dangers.add(new int[]{6, -3});
        dangers.add(new int[]{7, -3});
        dangers.add(new int[]{7, -4});
        dangers.add(new int[]{7, -5});
        dangers.add(new int[]{7, -6});
        dangers.add(new int[]{7, -7});
        dangers.add(new int[]{6, -7});
        dangers.add(new int[]{5, -7});
        dangers.add(new int[]{4, -7});
        dangers.add(new int[]{3, -7});
        dangers.add(new int[]{2, -7});
        dangers.add(new int[]{1, -7});
        dangers.add(new int[]{0, -7});
        dangers.add(new int[]{-1, -7});
        dangers.add(new int[]{-1, -6});
        dangers.add(new int[]{-1, -5});

        int[] position = {-1, -5};

        Scanner input = new Scanner(System.in);

        while (true) {
            String direction = input.nextLine();
            String[] parts = direction.split(" ");
            char d = parts[0].charAt(0);
            int n = Integer.parseInt(parts[1]);
            String idk = "safe";

            if (d == 'q')
            {
                break;
            }

            while (n > 0)
            {
                if (d == 'l')
                {
                    position[0] -= 1;
                }
                else if (d == 'r')
                {
                    position[0] += 1;
                }
                else if (d == 'u')
                {
                    position[1] += 1;
                }
                else if (d == 'd')
                {
                    position[1] -= 1;
                }
                n--;

                if (isDanger(position, dangers))
                {
                    idk = "DANGER";
                } else
                {
                    dangers.add(position.clone());
                }
            }

            System.out.println(position[0] + " " + position[1] + " " + idk);
            if (idk.equals("DANGER"))
            {
                break;
            }
        }
        input.close();
    }

    public static boolean isDanger(int[] position, List<int[]> dangers)
    {
        for (int i = 0; i < dangers.size(); i++)
        {
            int[] p = dangers.get(i);
            if (Arrays.equals(p, position))
            {
                return true;
            }
        }
        return false;
    }
}
