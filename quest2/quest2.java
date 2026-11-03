package quest2;
record Range(int start, int end) {}

public class quest2 {
    public static void main(String[] args){

        Range[] ranges = {
            new Range(11,22),
            new Range(95, 115),
            new Range(998, 1012),
            new Range(1188511880, 1188511890),
            new Range(222220, 222224),
            new Range(1698522, 1698528),
            new Range(446443, 446449),
            new Range(38593856, 38593862)
        };

        int invalidNumberValue = 0;

        for (Range range : ranges) {
            int start = range.start();
            int end = range.end();
            for (int n = start; n <= end; n++){
                String s = Integer.toString(n);
                if (s.length() % 2 == 0) {
                    int half = s.length() /2;
                    String left = s.substring(0, half);
                    String right = s.substring(half);

                    if (left.equals(right)) {
                        System.out.println(n);
                        invalidNumberValue = invalidNumberValue + n;
                    }
                }

            }
        }  
    System.out.println("The amount of invalid numbers are: " + invalidNumberValue);  
    }  
}
