package quest2;
import java.io.*; //FileReader, IOException
import java.util.*;

record Range(long start, long end) {}

public class day2 {
    public static void main(String[] args) throws IOException{

        BufferedReader br = new BufferedReader(new FileReader("quest2/input.txt")); 
        String line = br.readLine();
        br.close();
        
        ArrayList<Range> ranges = new ArrayList<>();
        String[] tokens = line.split(",");

        for (String token : tokens) {
            String[] parts = token.split("-");

            long start = Long.parseLong(parts[0]);
            long end = Long.parseLong(parts[1]);

           ranges.add(new Range(start, end));
        } 
        long invalidNumberValue = 0;

        for (Range range : ranges) {
            long start = range.start();
            long end = range.end(); 
            for (long n = start; n <= end; n++){
                String s = Long.toString(n);
                if (s.length() % 2 == 0) {
                    int half = s.length() /2;
                    String left = s.substring(0, half);
                    String right = s.substring(half);

                    if (left.equals(right)) {
                        System.out.println(n);
                        invalidNumberValue += n;
                    }
                }

            }
        }  
    System.out.println("The amount of invalid numbers are: " + invalidNumberValue);  
    }  
}
