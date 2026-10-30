import java.util.Scanner;

public class quest1 {
        public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int startPoint = 50;
        int x = 0;
        while (true) {
            System.out.print("Command: ");
            String command = scanner.nextLine().toUpperCase();

            if (command.equals("DONE")){
                break;
            }
            char direction = command.charAt(0);
            int moveSteps = Integer.parseInt(command.substring(1));
            if (direction == 'L') {
                startPoint = (startPoint + moveSteps) % 100;
                if (startPoint == 0) {
                    x++;
                    }
                }    
            else if (direction == 'R') {
                startPoint = ((startPoint - moveSteps) % 100 + 100) %100;
                if (startPoint == 0) {
                    x++;
                }
            }
        }
        System.out.print("Stopped at 0: " + x + " amount of times");
        scanner.close();
    }
}