public class insertionSort
{
    public static void insertSortInc(int[] arr)
    {
        for (int i = 0; i < arr.length-1; i++)
        {
            int key = arr[i+1];
            int j;
            for (j = i; j >= 0 && arr[j] > key; j--)
            {
                arr[j+1] = arr[j];
            }
            arr[j+1] = key;
        }
    }
    public static void insertSortDec(int[] arr)
    {
        for (int i = 0; i < arr.length-1; i++)
        {
            int key = arr[i+1];
            int j;
            for (j = i; j >= 0 && arr[j] < key; j--)
            {
                arr[j+1] = arr[j];
            }
            arr[j+1] = key;
        }

    }

    static void printArray(int[] arr)
    {
        for (int i : arr)
        {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public static void main(String[] args)
    {
        int[] arr = {12, 11, 13, 5, 6};
        insertSortInc(arr);
        printArray(arr);
        insertSortDec(arr);
        printArray(arr);
    }
}