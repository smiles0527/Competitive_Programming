import java.util.Scanner;

public class CCC09J3
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int otime = input.nextInt();
        input.close();
        int vtime = getCityTime(otime, -300);
        int etime = getCityTime(otime, -200);
        int wtime = getCityTime(otime, -100);
        int ttime = getCityTime(otime, 0);
        int htime = getCityTime(otime, 100);
        int stime = getCityTime(otime, 130);

        System.out.println(otime + " in Ottawa");
        System.out.println(vtime + " in Victoria");
        System.out.println(etime + " in Edmonton");
        System.out.println(wtime + " in Winnipeg");
        System.out.println(ttime + " in Toronto");
        System.out.println(htime + " in Halifax");
        System.out.println(stime + " in St. John's");


    }

    private static int getCityTime(int otime, int offSet)
    {
        int cityTime = otime + offSet;
        int m = cityTime % 100;
        if (m >= 60)
        {
            cityTime += 40;
        }
        if (cityTime < 0)
        {
            cityTime += 2400;
        }
        if (cityTime >= 2400)
        {
            cityTime -= 2400;
        }

        return cityTime;
    }
}