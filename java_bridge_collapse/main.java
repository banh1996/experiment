// import java.io.File;
// import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

class Graph
{
    private int V, E;
    private LinkedList<Integer>[] graph_data; // store input and find all edge to create new graph without cycle
    private LinkedList<Integer>[] new_graph_data; // graph without cycle

    // Utility class for storing maximum distance pedestal with its distance
    static class Tetra<T,U,V,C>
    {
        T first;
        U middle1;
        V middle2;
        C last;
        //Constructor
        Tetra(T first, U middle1, V middle2, C last) {
            this.first = first;
            this.middle1 = middle1;
            this.middle2 = middle2;
            this.last = last;
        }
    }
    @SuppressWarnings("unchecked")
    public Graph()
    {
        Integer center_node, leaf_node, dis, mindis;
        init_graph();
        mindis = V;
        // center_node = find_center_node(0);
        // System.out.println("center node is " + center_node);

        /* I tried to find the center node by get the middle node in the any longest path but it doesn't work
         * so, I bruteforce all center-node to create new graph, then find the min of longest path each center-node passed
         */
        for (int j = 0; j < V; j++) {
            // init null array for graph
            new_graph_data = new LinkedList[V];
            for (int i = 0; i < V; i++) {
                new_graph_data[i] = new LinkedList<>();
            }

            // using bfs to create a new graph from center-node
            create_new_graph(j);

            // first bfs to find one end pedestal of longest path
            leaf_node = bfs(0, new_graph_data).last;

            // second bfs to find actual longest path
            dis = bfs(leaf_node, new_graph_data).first;
            mindis = Math.min(mindis, dis);

            // clear new graph to create new one
            for (int i = 0; i < V; i++) {
                new_graph_data[i].clear();
            }
        }

        //System.out.println("leaf node is " + leaf_node);
        System.out.println(mindis);
    }
    @SuppressWarnings("unchecked")
    private void init_graph()
    {
        // try {
        //     File input_file = new File("big_input.txt");
        //     Scanner reader = new Scanner(input_file);
            Scanner reader = new Scanner(System.in);
            String line;
            String[] splited;
            int i = 0;

            // read V - pedestal number, E - path number
            //if (reader.hasNextLine()) {
                line = reader.nextLine();
                splited = line.split("\\s+");
                V = Integer.parseInt(splited[0]); //pedestals
                E = Integer.parseInt(splited[1]); //paths
            //}

            // init null array for graph
            graph_data = new LinkedList[V];
            for (i = 0; i < V; i++) {
                graph_data[i] = new LinkedList<>();
            }

            // read graph from input.txt to array
            i = 0;
			//while (reader.hasNextLine() && i < E) {
            while (i < E) {
				line = reader.nextLine();
				splited = line.split("\\s+");
                graph_data[Integer.parseInt(splited[0]) - 1].add(Integer.parseInt(splited[1]) - 1);
                graph_data[Integer.parseInt(splited[1]) - 1].add(Integer.parseInt(splited[0]) - 1);
				i++;
			}

            // close scanner
			reader.close();
		// } catch (FileNotFoundException e) {
		// 	System.out.println("An error occurred.");
		// 	e.printStackTrace();
		// }
    }

    /* brief: I tried to find the center node by get the middle node in the any longest path but it doesn't work
     * so I temporarily comment this code
    */
    /*
    private Integer find_center_node(Integer u)
    {
        Queue<Integer> q = new LinkedList<>();
        int[] level = new int[V];
        Tetra<Integer, Integer, Integer, Integer> p0, p1;

        // first bfs to find one end pedestal of longest path
        p0 = bfs(0, graph_data);
        // System.out.println("first(leaf) node is " + (p0.last+1));

        p1 = bfs(p0.last, graph_data);
        // System.out.println("last node is " + (p1.last+1));

        // System.out.println("center node is " + (p1.middle1+1) + " and " + (p1.middle2+1));
        // System.out.println("distance is " + p1.first);
        // the center node is in the middle of path in the logest path
        return p1.middle1;
    }
    */

    private void create_new_graph(Integer u)
    {
        Queue<Integer> q = new LinkedList<>();
        boolean visited[] = new boolean[V];

        Arrays.fill(visited, false);
        // push pedestal-u to queue
        q.add(u);

        // visit u
        visited[u] = true;
        while (!q.isEmpty()) {
            // get the first pedestal in queue
            int t = q.poll();

            // loop for all adjacent pedestals of pedestal-t
            for(int i = 0; i < graph_data[t].size(); i++) {
                int v = graph_data[t].get(i);

                // push pedestal-v into queue only if it is not visited already
                if(visited[v] == false) {
                    new_graph_data[t].add(v); // add edge t-v to new graph
                    new_graph_data[v].add(t); // add edge v-t to new graph
                    q.add(v);
                    visited[v] = true;
                }
            }
        }
    }

    private Tetra<Integer, Integer, Integer, Integer> bfs(int u, LinkedList<Integer>[] local_graph)
    {
        int[] dis = new int[V]; // use bfs to find farthest pedestal
        int[] tracer = new int[V]; // to log all path
        int[] need_path = new int[V]; // log path from u to farthest pedestal to find middle
        int i, node_num = 0, max_distance = 0, farthest_pedestal = 0, middle_pedestal1 = 0, middle_pedestal2 = -1;
        Queue<Integer> q = new LinkedList<>();

        // mark all distance with -1
        Arrays.fill(dis, -1);
        Arrays.fill(tracer, -1);
        // push pedestal-u to queue
        q.add(u);

        // distance of u from u will be 0
        dis[u] = 0;
        while (!q.isEmpty()) {
            // get the first pedestal in queue
            int t = q.poll();

            // loop for all adjacent pedestals of pedestal-t
            for(i = 0; i < local_graph[t].size(); i++) {
                int v = local_graph[t].get(i);

                // push pedestal-v into queue only if it is not visited already
                if(dis[v] == -1) {
                    q.add(v);
                    // make distance of v, one more than distance of t
                    dis[v] = dis[t] + 1;
                    tracer[v] = t;
                }
            }
        }

        // get farthest pedestal distance and its index 
        for(i = 0; i < V; i++) {
            //System.out.println("dis " + dis[i]);
            if(dis[i] > max_distance) {
                max_distance = dis[i];
                farthest_pedestal = i;//to get the first end pedestal
            }
        }

        //find the middle pedestals
        i = farthest_pedestal;
        while (tracer[i] != -1) {
            //System.out.print((i+1) + "<=");
            need_path[node_num++] = i;
            i = tracer[i];
        }
        //System.out.println((u+1));
        need_path[node_num++] = u;
        //System.out.println("node num is " + node_num);

        if (node_num%2 == 0) {
            middle_pedestal1 = need_path[node_num/2 - 1];
            middle_pedestal2 = need_path[node_num/2];
        }
        else {
            middle_pedestal1 = need_path[node_num/2];
        }

        //returns longest distance from pedestal u
        //System.out.println("farthest pefestal " + first_pedestal + " and " + max_distance);
        return new Tetra<Integer, Integer, Integer, Integer>(max_distance, middle_pedestal1, middle_pedestal2, farthest_pedestal);
    }

    public static void main(String[] args)
    {
        Graph g = new Graph();
    }
}
