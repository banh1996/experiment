import java.io.IOException;
import java.util.Scanner;

class Site_exploration {
    private int N;
    private int[] site_distance;
    private int[] site_time;

    public Site_exploration() {
        init();
        sort(site_distance, 0, N-1);
        System.out.println(cal_minimum_time(first_trans_time, second_trans_time));
    }

    private void init() {
        Scanner reader = new Scanner(System.in);
        String line;
        String[] splited;
        int i = 0;

        // read possible site number
        if (reader.hasNextLine()) {
            line = reader.nextLine();
            N = Integer.parseInt(line);
        }

        // init array
        site_distance = new int [N];
        site_time = new int [N];

        // read distance and time
        i = 0;
        while (i < N) {
            line = reader.nextLine();
            splited = line.split("\\s+");
            site_distance[i] = Integer.parseInt(splited[0]);
            site_time[i] = Integer.parseInt(splited[1]);
            i++;
        }

        // close scanner
        reader.close();
    }

    /* This function takes last element as pivot, places the pivot element at its correct
       position in sorted array, and places all smaller (smaller than pivot) to left of
       pivot and all greater elements to right of pivot */
    private int partition(int arr1[], int arr2[], int low, int high) {
        int pivot = arr1[high], temp;
        int i = low - 1; // index of smaller element
        for (int j = low; j < high; j++) {
            // If current element is smaller than the pivot
            if (arr1[j] < pivot) {
                i++;
                temp = arr1[i];
                arr1[i] = arr1[j];
                arr1[j] = temp;
                temp = arr2[i];
                arr2[i] = arr2[j];
                arr2[j] = temp;
            }
        }
        // swap arr[i+1] and arr[high] (or pivot)
        temp = arr1[i+1];
        arr1[i+1] = arr1[high];
        arr1[high] = temp;
        temp = arr2[i+1];
        arr2[i+1] = arr2[high];
        arr2[high] = temp;
        return i+1;
    }

    /* The function that implements QuickSort() */
    private void sort(int arr1[], int arr2[], int low, int high) {
        if (low < high) {
            /* index is partitioning index, arr[index] is
              now at right place */
            int index = partition(arr1, arr2, low, high);
            // Recursively sort elements before
            // partition and after partition
            sort(arr1, arr2, low, index-1);
            sort(arr1, arr2, index+1, high);
        }
    }

    /* The function that calculate minimum time to translate scrolls */
    private int cal_minimum_time(int trans1[], int trans2[]) {
        int i, timeline, extra_time = 0;
        timeline = trans1[0];
        for (i = 1; i < n; i++) {
            // first translator must work all time for sure
            timeline += trans1[i];
            if (trans2[i-1] + extra_time > trans1[i])
                // second translator maybe not relax if works slow
                extra_time += trans2[i-1] - trans1[i];
            else
                // second translator can relax with no extra time
                extra_time = 0;
        }

        // the final scroll that second translator must handle
        extra_time += trans2[n-1];
        // System.out.println("timeline:"+timeline);
        // System.out.println("ex:"+extra_time);
        return timeline + extra_time;
    }

    public static void main(String[] args) {
        Site_exploration t = new Site_exploration();
    }
}
