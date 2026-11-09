package quest5;
import java.io.*;
import java.util.*;



record Range(int start, int end) {}

public class day5 {

    record Range(long start, long end) {}

    public static void main(String[] args) throws IOException{

        BufferedReader br = new BufferedReader(new FileReader("quest5/input.txt"));

        ArrayList<Range> ranges = new ArrayList<>();
        ArrayList<Long> numbers = new ArrayList<>();
        String line;
        boolean readingRanges = true;
        int numberOfFreshItems = 0;

        while ((line = br.readLine()) != null) {
            line = line.trim();

            if (line.isEmpty()) {
                readingRanges = false;
                continue;
            }
            if (readingRanges) {
                String[] parts = line.split("-");

                long start = Long.parseLong(parts[0]);
                long end = Long.parseLong(parts[1]);

                ranges.add(new Range(start, end));
            } else {
                numbers.add(Long.parseLong(line));
            }
        }
        br.close();

        //change to read from input file
        for (long number : numbers) {
            boolean fresh = false;

            for (Range range : ranges) {
                if (number >= range.start() && number <= range.end()) {
                    fresh = true;
                    numberOfFreshItems++;
                    break;
                }
            }
        
        if (fresh) {
            System.out.println(number + " is a fresh item.");
        } else {
            System.out.println(number + " is not a fresh item.");
            }
        }
        System.out.println("Number of fresh items: " + numberOfFreshItems);
    }
}