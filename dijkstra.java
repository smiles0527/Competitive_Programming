
import java.util.*;

public class dijkstra 
{
    public static ArrayList<ArrayList<ArrayList<Integer>>> constructAdj(int[][] edges, int V)
    {
        ArrayList<ArrayList<ArrayList<Integer>>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++)
        {
            adj.add(new ArrayList<>());
        }

        for (int[] edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            ArrayList<Integer> a1 = new ArrayList<>();
            a1.add(v);
            a1.add(wt);
            adj.get(u).add(a1);

            ArrayList<Integer> a2 = new ArrayList<>();
            a2.add(u);
            a2.add(wt);
            adj.get(v).add(a2);
        }
        return adj;
    }

    public static int[] dijkstraAlgo(int[][]edges, int V, int src)
    {
        ArrayList<ArrayList<ArrayList<Integer>>> adj = constructAdj(edges, V);

        PriorityQueue<ArrayList<Integer>> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.get(0)));

        int[] dist = new int[V];      
        for (int i = 0; i < V; i++)
        {
            dist[i] = Integer.MAX_VALUE;
        }

        dist[src] = 0;

        ArrayList<Integer> start = new ArrayList<>();
        start.add(src);
        start.add(0);

        pq.offer(start);

        while (!pq.isEmpty())
        {
            ArrayList<Integer> curr = pq.poll();
            int u = curr.get(1);

            for (ArrayList<Integer> neighbour : adj.get(u))
            {
                int v = neighbour.get(0);
                int wt = neighbour.get(1);

                if (dist[v] > dist[u] + wt)
                {
                    dist[v] = dist[u] + wt;

                    ArrayList<Integer> temp = new ArrayList<>();
                    temp.add(dist[v]);
                    temp.add(v);
                    pq.offer(temp);             
                } 
            }
          }
        return dist;
    }
    public static void main(String[] args) {
        int[][] edges = {{0, 1, 4}, {0, 2, 8}, {1, 4, 6},{2, 3, 2}, {3, 4, 10}};
        int V = 5;
        int src = 0;

        int[] distance = dijkstraAlgo(edges, V, src);

        for (int d : distance)
        {
            System.out.print(d + " ");
        }
    }
}
