// public @interface SignedText {
//     public class SignedText {
//         private String firstName;
//         private String lastName;
    
//         public SignedText(String first, String last) {
//             firstName = first;
//             lastName = last;
//         }
    
//         public String getSignature() {
//             if (firstName.isEmpty()) {
//                 return lastName;
//             }
//             return firstName.substring(0, 1) + "-" + lastName;
//         }
    
//         public String addSignature(String text) {
//             String sig = getSignature();
//             if (text.startsWith(sig)) {
//                 return text.substring(sig.length()) + sig;
//             }
//             if (text.endsWith(sig)) {
//                 return text;
//             }
//             return text + sig;
//         }
//     }
    
// }
