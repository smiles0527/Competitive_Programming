public class selectionSort {

    public static void selectSortInc(int[] arr)
    {
        for (int i = 0; i < arr.length; i++)
        {
            int minIndex = i;
            for (int j = i; j < arr.length; j++)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            
        }
    }

    public static void selectSortDec(int[] arr)
    {
        for (int i = 0; i < arr.length - 1; i++)
        {
            int maxIndex = i;

            for (int j = i; j < arr.length; j++)
            {
                if (arr[j] > arr[maxIndex])
                {
                    maxIndex = j;
                }
            }
            int temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;      
        }
    }

    static void printArray(int[] arr)
    {
        for (int i : arr)
        {
            System.out.println(i + " ");
        }
        System.out.println();
    } 
    public static void main(String[] args)
    {
        int[] arr = {64, 25, 12, 22, 11};
        selectSortInc(arr);
        printArray(arr);
        selectSortDec(arr);
        printArray(arr);
    }
    
}
