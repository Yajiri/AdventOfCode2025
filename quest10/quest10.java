package quest10;

public class quest10 {

    public static void main(String[] args) {

        int[] target = {0, 1, 1, 1, 0, 1};

        int[][] buttons = {
            {0, 1, 2, 3, 4},
            {0, 3, 4},
            {0, 1, 2, 4, 5},
            {1, 2}
        };

        int best = Integer.MAX_VALUE;

        int combinations = 1 << buttons.length;  //This is the same as (int) Math.pow(2, buttons.length);

        //we call it mask because it's being used as a bitmask.
        for (int mask = 0; mask < combinations; mask++) { 

            // Start with all lights off
            int[] state = new int[target.length];

            int presses = 0;

            for (int button = 0; button < buttons.length; button++) {

                if ((mask & (1 << button)) != 0) {

                    presses++;

                    for (int light : buttons[button]) {
                        state[light] ^= 1;
                        }
                    }
                }

            if (matches(state, target)) {
                best = Math.min(best, presses);
            }
        }

        System.out.println("Fewest presses = " + best);
    }

    static boolean matches(int[] a, int[] b) {

        for (int i = 0; i < a.length; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }
}