// import java.io.File;
// import java.io.FileNotFoundException;
// import java.io.IOException;
// import java.io.FileWriter;
// import java.util.Scanner;

class BinSearch {
    public void swap(int arr[], int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    public void binary_search(int arr[], int ind[], int range[]) {
        int start = 0, mid, tempIndex;
        int end = arr.length - 1;
        int first, last;

        first = (range[0] < range[1])?range[0]:range[1];
        last = (range[0] > range[1])?range[0]:range[1];
            
        while (start < end) {
            mid = (start + end)/2;
            if (first < arr[mid])
                end = mid;
            else
                start = mid + 1;
        }

        tempIndex = start;

        start = 0;
        end = arr.length - 1;
        while (start < end) {
            mid = (start + end)/2 + 1;
            if (last < arr[mid])
                end = mid - 1;
            else 
                start = mid;
        }

        //System.out.println(end);
        if (tempIndex < end) {
            for (int i = tempIndex; i <= end; i++)
                System.out.print(ind[i] + " ");
            System.out.println();
        }
        else
        System.out.println("-1");
    }

    public void sort(int arr[], int ind[], int left, int right) {
        for (int i = left; i < right; i++) {
            for (int j = i + 1; j <= right; j++) {
                if (arr[i] > arr[j]) {
                    swap(arr, i, j);
                    swap(ind, i, j);
                }
            }
        }
    }

    public static void main(String[] args) {
        int arr[] = {1,5,4,0,9,9,6,7,8,1,1,3,5,0,9,7,3,0,8,6};
        int range[] = {5, 10};
        int ind[];
        ind = new int[arr.length];
        for (int i = 0; i < arr.length; i++)
            ind[i] = i;

        BinSearch t = new BinSearch();
        t.sort(arr, ind, 0, arr.length - 1);
        System.out.println();
        t.binary_search(arr, ind, range);
    }
}
