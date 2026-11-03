package quest5;
import java.util.Scanner;

record Range(int start, int end) {}

public class quest5 {


    public static void main(String[] args){

        Range[] ranges = {
            new Range(3, 5),
            new Range(10, 14),
            new Range(16, 20),
            new Range(12, 18)
        };

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter numbers separated by spaces:");
        String input = scanner.nextLine();
        String[] numbers = input.split(" ");

        for (String num : numbers) {
            int number = Integer.parseInt(num);
            boolean fresh = false;
            for (Range range : ranges) {
                if (number >= range.start() && number <= range.end()) {
                    fresh = true;
                    break;
                }
            }

        if (fresh) {
            System.out.println(number + " is a fresh item");
        } else {
            System.out.println(number + " is not a fresh item");
            }
        }
        scanner.close();
    }
}