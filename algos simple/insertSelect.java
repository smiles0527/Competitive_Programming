public class insertSelect {

    static void selectSort(int[] arr)
    {
        for (int i = 0; i < arr.length-1; i++)
        {
            int minIndex = i;

            for (int j = i; j < arr.length; j++)
            {
                if (arr[j] > arr[minIndex])
                {
                    minIndex = j;
                }
            }

            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }


    static void insertSort(int[] arr)
    {
        for (int i = 1; i < arr.length; i++)
        {
            int cur = arr[i];
            int j = i-1;

            while (j >= 0 && arr[j] < cur)
            {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = cur;
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

    static void main(String[] args)
    {
        int[] arr = {53, 12, 11, 14, 1004};
        selectSort(arr);
        printArray(arr);
        insertSort(arr);
        printArray(arr);
    }
}
