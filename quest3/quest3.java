package quest3;
import java.util.Scanner;

public class quest3 {
    public static void main(String[] args) {
        int largest = 0;
        int secondLargest = 0;
        int startIndex = 0;
        //Need this in order to actually receive the input.
        Scanner scanner = new Scanner(System.in);
        System.out.print("Please write the number sequence: ");
        String stringOfNumbers = scanner.nextLine();

        //Stops the search if we find a 9 and moves on to the second loop.
        for (int i = 0; i < stringOfNumbers.length() - 1; i++){
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
        for (int i = startIndex; i < stringOfNumbers.length(); i++) {
            if (stringOfNumbers.charAt(i) - '0' > secondLargest) {
                secondLargest = stringOfNumbers.charAt(i) - '0'; 
            }
        }

        System.out.print("The largest number is: " + largest + secondLargest);

        //don't forget to close the scanner
        scanner.close();
    }
}
