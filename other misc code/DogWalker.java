// public class DogWalker {
//     private int maxDogs;
//     private DogWalkCompany company;

//     public DogWalker(int max, DogWalkCompany comp) {
//         maxDogs = max;
//         company = comp;
//     }

//     public int walkDogs(int hour) {
//         int available = company.numAvailableDogs(hour);
//         int toWalk = available < maxDogs ? available : maxDogs;
//         company.updateDogs(hour, toWalk);
//         return toWalk;
//     }

//     public int dogWalkShift(int startHour, int endHour) {
//         int total = 0;
//         for (int h = startHour; h <= endHour; h++) {
//             int walked = walkDogs(h);
//             int pay = walked * 5;
//             if (walked == maxDogs || (h >= 9 && h <= 17)) {
//                 pay += 3;
//             }
//             total += pay;
//         }
//         return total;
//     }
// }
