package quest1;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class day1 {
        public static void main (String[] args) throws IOException{
        ArrayList<String> commands = new ArrayList<>();

        BufferedReader br = new BufferedReader(new FileReader("quest1/input.txt"));
        
        String line;
        while ((line = br.readLine()) != null) {
                commands.add(line);
            }

        br.close(); 

        int startPoint = 50;
        int x = 0;
        for (String command : commands) {
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
    }
}