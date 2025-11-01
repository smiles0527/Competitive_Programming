import java.util.*;

public class bfs {


    public static ArrayList<Integer> bfsAlgo(ArrayList<ArrayList<Integer>> adj)
    {
        int V = adj.size();
        ArrayList<Integer> res = new ArrayList<>();
        boolean[] visited = new boolean[V];

        int src = 0;
        Queue<Integer> q = new LinkedList<>();
        visited[src] = true;
        q.offer(src);

        while (!q.isEmpty())
        {
            int u = q.poll();

            for (int n : adj.get(u))
            {
                if (!visited[n])
                {
                    visited[n] = true;
                    res.add(n);
                    q.offer(n);
                }
            }
        }
        return res;
    }


    public static void addEdge(ArrayList<ArrayList<Integer>> adj, int u, int v)
    {
        adj.get(u).add(v);
        adj.get(v).add(u);
    }

    public static void main(String[] args) {

        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();

        for (int i = 0; i < 5; i++)
        {
            adj.add(new ArrayList<>());
        }
        addEdge(adj, 0, 1);
        addEdge(adj, 0, 2);
        addEdge(adj, 1, 2);
        addEdge(adj, 2, 3);
        addEdge(adj, 2, 4);

        ArrayList<Integer> order = bfsAlgo(adj);

        for (int x : order)
        {
            System.out.print(x + " ");
        }

    }
    
}
