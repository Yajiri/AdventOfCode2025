package quest3;
import java.io.*;

public class day3 {
    public static void main(String[] args) throws IOException {
        long total = 0;
        
        try (BufferedReader br = new BufferedReader(new FileReader("quest3/input.txt"))) {
            String stringOfNumbers;
            while((stringOfNumbers = br.readLine()) != null) {

            long largest = 0;
            long secondLargest = 0;
            int startIndex = 0;
            //Need this in order to actually receive the input.

            int len = stringOfNumbers.length();

            //Stops the search if we find a 9 and moves on to the second loop.
            for (int i = 0; i < len - 1; i++){
                if (stringOfNumbers.charAt(i) == '9'){
                    largest = 9;
                    startIndex = i + 1;
                    break;
                }

                //The - '0' is a trick in java/c/c++ that allows you to skip the Integer.parseInt(String.valueOf(stringOfNumbers.charAt(i)));
                if (stringOfNumbers.charAt(i) - '0' > largest){
                    largest = stringOfNumbers.charAt(i) - '0';
                    startIndex = i + 1;
                }
            }
            //Initiates the second loop
            for (int i = startIndex; i < len; i++) {
                if (stringOfNumbers.charAt(i) - '0' > secondLargest) {
                    secondLargest = stringOfNumbers.charAt(i) - '0'; 
                        }
                    }
                total += largest * 10 + secondLargest;
                }
            }
            System.out.print("The largest number is: " + total);
        }
    }
