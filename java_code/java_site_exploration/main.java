import java.io.IOException;
import java.util.Scanner;
import java.util.Arrays;

class Site_exploration {
    private int N, Max_dis = 0;
    private int[] site_distance;
    private int[] site_time;
    private int[] raw_tree;
    private int[] left_lower_tree;
    private int[] down_tree;

    public Site_exploration() {
        init();

        // sort time&distance array follow time x-component
        sort(site_time, site_distance, 0, N-1);

        // create Fenwick Tree with distance array, y-component
        FenwickTree(N);

        // calculate result
        System.out.println(cal_sites());
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
            Max_dis = Math.max(site_distance[i], Max_dis);
            i++;
        }

        // init BIT
        raw_tree = new int [Max_dis+1];
        left_lower_tree = new int [Max_dis+1];
        down_tree = new int [Max_dis+1];
        for (i = 0; i <= Max_dis; i++) {
            raw_tree[i] = 0;
            left_lower_tree[i] = 0;
            down_tree[i] = 0;
        }
        for (i = 0; i < N; i++) {
            raw_tree[site_distance[i]]++;
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
        // swap
        temp = arr1[i+1];
        arr1[i+1] = arr1[high];
        arr1[high] = temp;
        temp = arr2[i+1];
        arr2[i+1] = arr2[high];
        arr2[high] = temp;
        return i+1;
    }

    /* The function to sort arr1&arr2 based on arr1 */
    private void sort(int arr1[], int arr2[], int low, int high) {
        if (low < high) {
            /* index is partitioning index, arr[index] is
              now at right place */
            int index = partition(arr1, arr2, low, high);
            // Recursively sort elements before partition and after partition
            sort(arr1, arr2, low, index-1);
            sort(arr1, arr2, index+1, high);
        }
    }

    private long getBIT(int arr[], int index) {
        long sum = 0;
        int i = site_distance[index];

        // Traverse ancestors of BITree[index]
        while(i > 0) {
            // Add current element of BITree to sum
            sum += arr[i];
            // Move index to parent node
            i -= i & (-i); 
        }

        return sum; // I want to get the only points that lower index
    }

    private void updateBIT(int []arr, int n, int index, int val) {
        // Traverse all ancestors and add 'val'
        while(index <= n) {
            // Add 'val' to current node of BIT Tree
            arr[index] += val;

            // Update index to that of parent in update View
            index += index & (-index);
        }
    }

    /* Function to construct fenwick tree from given array */
    private void FenwickTree(int n) {
        // Store the actual values in tree[] using update()
        for(int i = 0; i < N; i++)
            updateBIT(down_tree, Max_dis, site_distance[i], raw_tree[site_distance[i]]);
    }

    private long cal_sites() {
        long result = 0;
        for (int i = 0; i < N; i++) {
            long temp = getBIT(down_tree, i);
            // now, sum is the point number that its distance lower than distance[index]
            // I'll calculate left lower & right upper angle later
            long left = i, right = N-i-1, down = temp-1, up = N-temp-1;

            updateBIT(left_lower_tree, Max_dis, site_distance[i], raw_tree[site_distance[i]]);
            long left_down = getBIT(left_lower_tree, i) - 1; // here is the left lower tree while sweeping
            long right_up = right - down + left_down;
            // System.out.print(left_down + "+");
            // System.out.print(right_up + " ");
            result += left_down*right_up;
        }
        return result;
    }

    public static void main(String[] args) {
        Site_exploration t = new Site_exploration();
    }
}
