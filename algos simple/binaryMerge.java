public class binaryMerge {

    static int binarySearch(int[] arr, int l, int h, int x)
    { //1 1 2 7 10 11 11 45 65 78 
        if (l <= h)
        {
            int m = l + (h-l)/2;

            if (arr[m] == x)
            {
                return m;
            }

            if (arr[m] < x)
            {
                return binarySearch(arr, m+1, h, x);
            }
            else
            {
                return binarySearch(arr, l, m, x);
            }
        }
        return -1;
    }

    static void merge(int[] arr, int l, int m, int r)

    {
        int n1 = m-l+1;
        int n2 = r-m;

        int[] L = new int[n1];
        int[] R = new int[n2];

        for (int i = 0; i < n1; i++) // copy the left side of the array 
        {
            L[i] = arr[l+i];
        }
        
        for (int j = 0; j < n2; j++) // right side 
        {
            R[j] = arr[m+1+j];
        } 

        int i = 0, j = 0;
        int k = l; 

        while (i < n1 && j < n2)
        {
            if (L[i] < R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    static void mergeS(int[] arr, int l, int r)
    {
        if (l < r)
        {
            int m = l + (r-l)/2;

            mergeS(arr, l, m);
            mergeS(arr, m+1, r);

            merge(arr, l, m, r);
        }

    }

    static void printArr(int[] arr)
    {
        for (int i : arr)
        {
            System.out.print(i + " ");
        }
        System.out.println();
    }
    

    static void main(String[] args)
    {
        int[] arr = {7, 1, 45, 65, 78, 11, 11, 2, 10, 1};
        int x = 78;

        mergeS(arr, 0, arr.length-1);
        int index = binarySearch(arr, 0, arr.length-1, x); 

        printArr(arr);
        System.out.println(index);

    }
}

