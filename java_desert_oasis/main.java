import java.util.Scanner;
import java.util.Arrays;
import java.lang.Math;
import java.lang.Double; 

class Desert_Oasis {
    public static class Friend {
        int x, y;
        String name;
    
        double get_distance(int xo, int yo) {
            return Math.sqrt((double)Math.pow(this.x - xo, 2) + (double)Math.pow(this.y - yo, 2));
        }
    }

    private int N, xo, yo;
    private Friend[] friends;

    public Desert_Oasis() {
        init();
        /* sort friends array based on distance */
        sort(this.friends, 0, this.N - 1);
        for (int i = 0; i < this.N; i++) {
            System.out.println(this.friends[i].name);
        }
    }

    private void init() {
        Scanner reader = new Scanner(System.in);
        String line;
        String[] splited;
        int i = 0;

        // read friend number, x0, y0
        if (reader.hasNextLine()) {
            line = reader.nextLine();
            splited = line.split("\\s+");
            this.N = Integer.parseInt(splited[0]);
            this.xo = Integer.parseInt(splited[1]);
            this.yo = Integer.parseInt(splited[2]);
        }

        friends = new Friend [N];

        // read friend coordinates
        i = 0;
        while (i < N) {
            line = reader.nextLine();
            splited = line.split("\\s+");
            friends[i] = new Friend();
            friends[i].x = Integer.parseInt(splited[0]);
            friends[i].y = Integer.parseInt(splited[1]);
            friends[i].name = splited[2];
            i++;
        }

        // close scanner
        reader.close();
    }

    /* This function takes last element as pivot, places the pivot element at its correct
       position in sorted array, and places all smaller (smaller than pivot) to left of
       pivot and all greater elements to right of pivot */
    private int partition(Friend arr[], int low, int high) {
        double pivot = arr[high].get_distance(this.xo, this.yo);
        Friend temp;
        int i = low - 1; // index of smaller element
        for (int j = low; j < high; j++) {
            // If current element is smaller than the pivot
            if (Double.compare(arr[j].get_distance(this.xo, this.yo), pivot) < 0) {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // swap
        temp = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp;
        return i+1;
    }

    /* The function to sort arr based on arr */
    private void sort(Friend arr[], int low, int high) {
        if (low < high) {
            /* index is partitioning index, arr[index] is now at right place */
            int index = partition(arr, low, high);
            // Recursively sort elements before partition and after partition
            sort(arr, low, index-1);
            sort(arr, index+1, high);
        }
    }

    public static void main(String[] args) {
        Desert_Oasis run = new Desert_Oasis();
    }
}
