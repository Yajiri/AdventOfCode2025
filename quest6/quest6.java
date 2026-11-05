package quest6;
import java.util.Scanner;
import java.util.ArrayList;

public class quest6 {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<int[]> rows = new ArrayList<>();

        while(true) {
            System.out.println("Please enter the sequence of numbers split by spacing (line by line), when done type done:");
            String lineOfNumbers = scanner.nextLine();

            //break the while loop
            if (lineOfNumbers.equalsIgnoreCase("DONE")) {
                break;
            }

            String[] numbers = lineOfNumbers.trim().split("\\s+");

            int[] number = new int[numbers.length];

            //loop and enters the numbers as arrays into the grid.
            for (int i = 0; i < numbers.length; i++) {
                number[i] = Integer.parseInt(numbers[i]);
            }

        rows.add(number);
        }
        System.out.println("Enter operators: ");
        String[] operators = scanner.nextLine().trim().split("\\s+");
        int len = operators.length;
        for (int col = 0; col < len; col ++) {
            if(operators[col].equals("*")) {
                int result = 1;
                for (int[] row : rows) {
                    result *= row[col];
                }
                System.out.println("The value of column " + (col + 1) + " is " + result);
            } 
            if (operators[col].equals("+")) {
                int result = 0;
                for (int[] row : rows) {
                    result += row[col];
                }
                System.out.println("The value of column " + (col + 1) + " is " + result);
            } 
            //adding subtraction and division functions just to be safe...
            if (operators[col].equals("-")) {
                int result = rows.get(0)[col];
                for (int i = 1; i < rows.size(); i++) {
                    result -= rows.get(i)[col];
                }
                System.out.println("The value of column " + (col + 1) + " is " + result);
            } 
            if (operators[col].equals("/")) {
                int result = rows.get(0)[col];
                for (int i = 1; i < rows.size(); i++) {
                    result /= rows.get(i)[col];
                }
                System.out.println("The value of column " + (col + 1) + " is " + result);
            }
        }
        scanner.close();
    }
}
