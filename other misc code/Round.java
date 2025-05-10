// import java.util.ArrayList;

// public class Round {
//     private ArrayList<Competitor> competitorList;

//     public Round(String[] names) {
//         competitorList = new ArrayList<>();
//         for (int i = 0; i < names.length; i++) {
//             competitorList.add(new Competitor(names[i], i + 1));
//         }
//     }

//     public ArrayList<Match> buildMatches() {
//         ArrayList<Match> matches = new ArrayList<>();
//         int n = competitorList.size();
//         int start = (n % 2 == 1) ? 1 : 0;
//         int low = start;
//         int high = n - 1;
//         while (low < high) {
//             matches.add(new Match(
//                 competitorList.get(low),
//                 competitorList.get(high)
//             ));
//             low++;
//             high--;
//         }
//         return matches;
//     }
// }
// s