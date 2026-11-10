package quest6;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class day6 {

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new FileReader("quest6/input.txt"));
        ArrayList<ArrayList<Long>> numbers = new ArrayList<>();
        ArrayList<String> operators = new ArrayList<>();
        ArrayList<String> lines = new ArrayList<>();
        String line;
        long finalResult = 0;

        while ((line = br.readLine()) != null) {
            lines.add(line.trim());
        }
        String operatorLine = lines.get(lines.size() - 1);
        String[] ops = operatorLine.split("\\s+");
        for (String op : ops ) {
            operators.add(op);
        }
        for (int i = 0; i < lines.size() - 1; i++) {
            ArrayList<Long> row = new ArrayList<>();
            String[] nums = lines.get(i).split("\\s+");
            for (String num : nums) {
                row.add(Long.parseLong(num));
            }
            numbers.add(row);
        }

        int len = operators.size();

        for (int col = 0; col < len; col ++) {
            if(operators.get(col).equals("*")) {
                long result = 1;
                for (ArrayList<Long> row : numbers) {
                    result *= row.get(col);
                }
                finalResult += result;
            } 
            if (operators.get(col).equals("+")) {
                long result = 0;
                for (ArrayList<Long> row : numbers) {
                    result += row.get(col);
                }
                finalResult += result;
            } 
            //adding subtraction and division functions just to be safe...
            if (operators.get(col).equals("-")) {
                long result = numbers.get(0).get(col);
                for (int i = 1; i < numbers.size(); i++) {
                    result -= numbers.get(i).get(col);
                }
                finalResult += result;
            } 
            if (operators.get(col).equals("/")) {
                long result = numbers.get(0).get(col);
                for (int i = 1; i < numbers.size(); i++) {
                    result /= numbers.get(i).get(col);
                }
                finalResult += result;
            }
        }
        System.out.print("The final result is: " + finalResult);
        br.close();
    }
}
