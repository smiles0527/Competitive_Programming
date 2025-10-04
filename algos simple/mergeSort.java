public class mergeSort {

    //merge() function for merging
    static void merge(int[] arr, int l, int m, int r){
        // size of two arrays
        int n1 = m - l + 1;
        int n2 = r - m;

        // two temp arrays
        int L[] = new int[n1];
        int R[] = new int[n2];

        // copy data to temp arrays
        for(int i = 0; i < n1 ; i++){
            L[i] = arr[l+i];
        }
        for (int j = 0; j < n2; j++){
            R[j] = arr[m+1+j];
        }

        // merge the temp arrays

        int i = 0, j = 0;

        int k = l;
        while (i < n1 && j < n2){
            if (L[i] <= R[j]){
                arr[k] = L[i];
                i++;
            }else{
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // copy remaining to the arr
        while (i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2){
            arr[k] = R[j];
            j++;
            k++;

        }

    }

    //mergeS for divid and con
    static void mergeS(int[] arr, int l, int r){
        if (l < r){
            // find mid ,
            //int m = (l + r) / 2;
            int m = l + (r - l) / 2;


            //11, 25, 65, 37, 28, 11, 21
            // sort first and second half
            mergeS(arr, l, m);
            mergeS(arr, m+1, r);


            //merge function
            merge(arr, l, m, r);
        }
    }


    //main function
    static void printArray(int[] arr)
    {
        for (int i : arr)
        {
            System.out.print(i + " ");
        }
        System.out.println();
    }
    public static void main(String[] args) {
        int[] array = {11, 25, 65, 37, 28};
        mergeS(array, 0, array.length-1);
        printArray(array);
    }
}
