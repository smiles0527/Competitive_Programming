import java.io.*;
import java.util.*;  

class s3 {
    // This is a really really big number!
    static final long INF = (long)1e18;
    
    // This is like a tree that helps us find the biggest numbers
    static class SegTree {
        int size;
        long[] values;
        
        // Make a new tree to hold our numbers
        SegTree(int size) {
            this.size = size;
            values = new long[4 * size];
            Arrays.fill(values, -1);
        }
        
        // Put a new number in our tree
        void update(int pos, long val) {
            update(1, 1, size, pos, val);
        }
        
        // Helper to put the number in the right spot
        void update(int node, int start, int end, int pos, long val) {
            if (start == end) {
                values[node] = val;
                return;
            }
            int middle = (start + end) / 2;
            if (pos <= middle)
                update(2*node, start, middle, pos, val);
            else
                update(2*node+1, middle+1, end, pos, val);
            values[node] = Math.max(values[2*node], values[2*node+1]);
        }
        
        // Find the biggest number in a part of our tree
        long query(int left, int right) {
            if (left > right) return -1;
            return query(1, 1, size, left, right);
        }
        
        // Helper to find the biggest number
        long query(int node, int start, int end, int left, int right) {
            if (left > end || right < start) return -1;
            if (left <= start && end <= right) return values[node];
            int middle = (start + end) / 2;
            return Math.max(query(2*node, start, middle, left, right),
                          query(2*node+1, middle+1, end, left, right));
        }
    }
    
    // This helps us keep two numbers together like matching socks!
    static class Pair implements Comparable<Pair> {
        long first;
        int second;
        
        Pair(long f, int s) {
            first = f;
            second = s;
        }
        
        // See which pair is bigger
        public int compareTo(Pair other) {
            if (first != other.first)
                return Long.compare(first, other.first);
            return Integer.compare(second, other.second);
        }
    }
    
    public static void main(String[] args) throws IOException {
        // Get ready to read numbers from keyboard
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        // How many pens and colors do we have?
        int N = Integer.parseInt(st.nextToken());  // Number of pens
        int M = Integer.parseInt(st.nextToken());  // Number of colors
        int Q = Integer.parseInt(st.nextToken());  // Number of questions
        
        // Make lists to remember things about our pens
        int[] penColor = new int[N + 1];          // What color is each pen?
        long[] penPretty = new long[N + 1];       // How pretty is each pen?
        TreeMap<Pair, Integer>[] colorSets = new TreeMap[M + 1];  // Groups of pens by color
        long[] bestVal = new long[M + 1];         // Best prettiness for each color
        long[] secondVal = new long[M + 1];       // Second best prettiness
        int[] countBest = new int[M + 1];         // How many pens have best prettiness
        long[] cand = new long[M + 1];            // Special numbers we might need
        
        // Get everything ready to use
        for (int i = 1; i <= M; i++) {
            colorSets[i] = new TreeMap<>();
            secondVal[i] = -1;
            cand[i] = -1;
        }
        
        // Read about each pen
        for (int i = 1; i <= N; i++) {
            st = new StringTokenizer(br.readLine());
            int c = Integer.parseInt(st.nextToken());    // What color is it?
            long p = Long.parseLong(st.nextToken());    // How pretty is it?
            penColor[i] = c;
            penPretty[i] = p;
            colorSets[c].put(new Pair(p, i), 1);
        }
        
        // Add up all the prettiest numbers
        long baseSum = 0;
        TreeMap<Pair, Integer> globalBestSet = new TreeMap<>();
        
        // Look at each color group
        for (int c = 1; c <= M; c++) {
            var ms = colorSets[c];
            if (!ms.isEmpty()) {
                var last = ms.lastKey();
                bestVal[c] = last.first;
                countBest[c] = 1;
                
                if (ms.size() >= 2) {
                    var it = ms.headMap(last).lastKey();
                    if (it.first == bestVal[c])
                        countBest[c] = 2;
                    secondVal[c] = it.first;
                }
            }
            baseSum += bestVal[c];
            globalBestSet.put(new Pair(bestVal[c], c), 1);
            
            if (ms.size() >= 2)
                cand[c] = (countBest[c] >= 2 ? bestVal[c] : secondVal[c]);
        }
        
        // Make a special helper tree
        SegTree segTree = new SegTree(M);
        for (int c = 1; c <= M; c++) {
            segTree.update(c, cand[c]);
        }
        
        // Answer questions about the pens
        for (int qi = 0; qi < Q; qi++) {
            st = new StringTokenizer(br.readLine());
            int type = Integer.parseInt(st.nextToken());
            
            // Someone wants to change a pen's color
            if (type == 1) {
                int i = Integer.parseInt(st.nextToken());
                int newC = Integer.parseInt(st.nextToken());
                int oldC = penColor[i];
                
                if (oldC == newC) {
                    pw.println(getAnswer(globalBestSet, segTree, baseSum, M));
                    continue;
                }
                
                long p = penPretty[i];
                colorSets[oldC].remove(new Pair(p, i));
                updateGroup(oldC, colorSets, bestVal, secondVal, countBest, cand, globalBestSet, segTree, baseSum);
                
                colorSets[newC].put(new Pair(p, i), 1);
                updateGroup(newC, colorSets, bestVal, secondVal, countBest, cand, globalBestSet, segTree, baseSum);
                
                penColor[i] = newC;
            } 
            // Someone wants to change how pretty a pen is
            else {
                int i = Integer.parseInt(st.nextToken());
                long newP = Long.parseLong(st.nextToken());
                int c = penColor[i];
                long oldP = penPretty[i];
                
                colorSets[c].remove(new Pair(oldP, i));
                colorSets[c].put(new Pair(newP, i), 1);
                updateGroup(c, colorSets, bestVal, secondVal, countBest, cand, globalBestSet, segTree, baseSum);
                penPretty[i] = newP;
            }
            
            // Tell them the answer
            pw.println(getAnswer(globalBestSet, segTree, baseSum, M));
        }
        
        pw.close();
    }
    
    // Update all the numbers for one color group
    static void updateGroup(int c, TreeMap<Pair,Integer>[] colorSets, long[] bestVal, long[] secondVal, 
                          int[] countBest, long[] cand, TreeMap<Pair,Integer> globalBestSet, 
                          SegTree segTree, long baseSum) {
        long oldBest = bestVal[c];
        globalBestSet.remove(new Pair(bestVal[c], c));
        var ms = colorSets[c];
        
        // Look at all the pens of this color
        if (ms.isEmpty()) {
            bestVal[c] = 0;
            secondVal[c] = -1;
            countBest[c] = 0;
        } else {
            var last = ms.lastKey();
            bestVal[c] = last.first;
            countBest[c] = 1;
            
            if (ms.size() >= 2) {
                var it = ms.headMap(last).lastKey();
                if (it.first == bestVal[c])
                    countBest[c] = 2;
                secondVal[c] = it.first;
            } else {
                secondVal[c] = -1;
            }
        }
        
        // Update all our lists with new numbers
        baseSum = baseSum - oldBest + bestVal[c];
        globalBestSet.put(new Pair(bestVal[c], c), 1);
        
        if (colorSets[c].size() < 2)
            cand[c] = -1;
        else
            cand[c] = (countBest[c] >= 2 ? bestVal[c] : secondVal[c]);
        segTree.update(c, cand[c]);
    }
    
    // Find the best answer we can get
    static long getAnswer(TreeMap<Pair,Integer> globalBestSet, SegTree segTree, long baseSum, int M) {
        var first = globalBestSet.firstKey();
        long g = first.first;
        int gColor = first.second;
        boolean unique = true;
        long h = INF;
        
        var higher = globalBestSet.higherKey(first);
        if (higher != null) {
            if (higher.first == g)
                unique = false;
            else
                h = higher.first;
        }
        
        // Try to make our answer even better!
        long bestImprovement = 0;
        if (!unique) {
            long maxCand = segTree.query(1, M);
            bestImprovement = maxCand - g;
        } else {
            long cand_g = segTree.query(gColor, gColor);
            long opt1 = cand_g - h;
            long opt2 = Math.max(segTree.query(1, gColor - 1),
                               segTree.query(gColor + 1, M)) - g;
            bestImprovement = Math.max(opt1, opt2);
        }
        
        if (bestImprovement < 0)
            bestImprovement = 0;
        return baseSum + bestImprovement;
    }
}
