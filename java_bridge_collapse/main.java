import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

class Graph
{
    private int V, E, first_pedestal = 0;
    private int[] degree;
    private LinkedList<Integer>[] graph_data;

    public Graph()
    {
        int center_node;
        init_graph();
        center_node = find_center_node(0);
        // first bfs to find one end pedestal of longest path
        bfs(0);

        // second bfs to find actual longest path
        System.out.println(first_pedestal);
        System.out.println(bfs(first_pedestal));
        System.out.println(first_pedestal);
    }
    @SuppressWarnings("unchecked")
    private void init_graph()
    {
        try {
            File input_file = new File("input.txt");
            Scanner reader = new Scanner(input_file);
            //Scanner reader = new Scanner(System.in);
            String line;
            String[] splited;
            int i = 0;

            // read V - pedestal number, E - path number
            if (reader.hasNextLine()) {
                line = reader.nextLine();
                splited = line.split("\\s+");
                V = Integer.parseInt(splited[0]); //pedestals
                E = Integer.parseInt(splited[1]); //paths
            }

            // init null array for graph
            graph_data = new LinkedList[V];
            degree = new int[V];
            for (i = 0; i < V; i++) {
                graph_data[i] = new LinkedList<>();
                degree[i] = 0;
            }

            // read graph from input.txt to array
            i = 0;
			while (reader.hasNextLine() && i < E) {
            //while (i < E) {
				line = reader.nextLine();
				splited = line.split("\\s+");
                graph_data[Integer.parseInt(splited[0]) - 1].add(Integer.parseInt(splited[1]) - 1);
                graph_data[Integer.parseInt(splited[1]) - 1].add(Integer.parseInt(splited[0]) - 1);
                degree[Integer.parseInt(splited[0]) - 1]++;
                degree[Integer.parseInt(splited[1]) - 1]++;
				i++;
			}

            // close scanner
			reader.close();
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		}
    }

    private Integer find_center_node(int u)
    {
        Queue<Integer> q = new LinkedList<>();
        int[] level = new int[V];
        int maxlevel = 0;
        // Start from leaves
        for (int i = 0; i < V; i++) {
            if (degree[i] == 1) {
                q.add(i);
            }
            level[i] = 0;
        }

        while (!q.isEmpty()) {
            int t = q.poll();
            for(int i = 0; i < graph_data[t].size(); i++) {
                int v = graph_data[t].get(i);

                degree[v]--;
                if(degree[v] == 1) {
                    q.add(v);
                    level[v] = level[t] + 1;
                    maxlevel = Math.max(maxlevel, level[i]);
                }
            }
        }
        
        for (int i = 0; i < V; i++) {
            if (level[i] == maxlevel) {
                System.out.println("center node " + i + " and " + maxlevel);
            }
        }

        return maxlevel;
    }

    /*
    boolean isCycle()
    {
        // Create a vector to store indegrees of all
        // vertices. Initialize all indegrees as 0.
        int[] in_degree = new int[this.V];
        Arrays.fill(in_degree, 0);

        // Traverse adjacency lists to fill indegrees of 
        // vertices. This step takes O(V+E) time 
        for (int u = 0; u < V; u++)
        {
            for (int v : graph_data[u])
                in_degree[v]++;
        }

        // Create an queue and enqueue all vertices with
        // indegree 0
        Queue<Integer> q = new LinkedList<Integer>();
        for (int i = 0; i < V; i++)
            if (in_degree[i] == 0)
                q.add(i);

        // Initialize count of visited vertices
        int cnt = 0;

        // Create a vector to store result (A topological 
        // ordering of the vertices) 
        Vector<Integer> top_order = new Vector<>();

        // One by one dequeue vertices from queue and enqueue 
        // adjacents if indegree of adjacent becomes 0 
        while (!q.isEmpty()) 
        {
            // Extract front of queue (or perform dequeue) 
            // and add it to topological order 
            int u = q.poll(); 
            top_order.add(u); 

            // Iterate through all its neighbouring nodes 
            // of dequeued node u and decrease their in-degree 
            // by 1 
            for (int itr : graph_data[u]) 
                if (--in_degree[itr] == 0) 
                    q.add(itr); 
            cnt++; 
        } 

        // Check if there was a cycle 
        if (cnt != this.V) 
            return true; 
        else
            return false; 
    }
    */

    private Integer bfs(int u)
    {
        int[] dis = new int[V];
        int i, Maxdis = 0;
        Queue<Integer> q = new LinkedList<>();

        // mark all distance with -1
        Arrays.fill(dis, -1);
        // push pedestal-u to queue
        q.add(u);

        // distance of u from u will be 0
        dis[u] = 0;
        while (!q.isEmpty()) {
            // get the first pedestal in queue
            int t = q.poll();

            // loop for all adjacent pedestals of pedestal-t
            for(i = 0; i < graph_data[t].size(); i++) {
                int v = graph_data[t].get(i);

                // push pedestal-v into queue only if it is not visited already
                if(dis[v] == -1) {
                    q.add(v);
                    // make distance of v, one more than distance of t
                    dis[v] = dis[t] + 1;
                }
            }
        }

        // get farthest pedestal distance and its index 
        for(i = 0; i < V; i++) {
            //System.out.println("dis " + dis[i]);
            if(dis[i] > Maxdis) {
                Maxdis = dis[i];
                first_pedestal = i;//to get the first end pedestal
            }
        }

        //returns longest distance from pedestal u
        //System.out.println("farthest pefestal " + first_pedestal + " and " + Maxdis);
        return Maxdis;
    }

    public static void main(String[] args)
    {
        Graph g = new Graph();
    }
}
