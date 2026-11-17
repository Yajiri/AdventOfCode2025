package quest10;

public class quest10 {

    public static void main(String[] args) {

        // All targets grouped in one 2D array
        int[][] targets = {
            // Config 0: [.##.]
            {0, 1, 1, 0},

            // Config 1: [...#.]
            {0, 0, 0, 1, 0},

            // Config 2: [.###.#]
            {0, 1, 1, 1, 0, 1}
        };

        // All button sets grouped in one 3D array
        int[][][] allButtons = {
            // Buttons for config 0: (3) (1,3) (2) (2,3) (0,2) (0,1)
            {
                {3},
                {1, 3},
                {2},
                {2, 3},
                {0, 2},
                {0, 1}
            },

            // Buttons for config 1: (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4)
            {
                {0, 2, 3, 4},
                {2, 3},
                {0, 4},
                {0, 1, 2},
                {1, 2, 3, 4}
            },

            // Buttons for config 2 (your original): 
            // (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2)
            {
                {0, 1, 2, 3, 4},
                {0, 3, 4},
                {0, 1, 2, 4, 5},
                {1, 2}
            }
        };

        String[] names = {
            "Config 1 [.##.]",
            "Config 2 [...#.]", 
            "Config 3 [.###.#]"
        };

        // sum of best presses for all configs
        int totalValue = 0; 

        // Loop through all configurations
        for (int i = 0; i < targets.length; i++) {
            int best = solveAndReturnBest(targets[i], allButtons[i]);
            System.out.println(names[i] + " - Minimum amount of presses = " + best);
            // add this config's best to the total
            totalValue += best; 
        }

        System.out.println("Total value (sum of all best presses) = " + totalValue);
    }

    /**
     * Tries all button combinations and returns the minimum presses
     * for a given target and button setup.
     */
    static int solveAndReturnBest(int[] target, int[][] buttons) {

        int best = Integer.MAX_VALUE;
        int combinations = 1 << buttons.length; // $ 2^{buttons.length} $ subsets

        for (int mask = 0; mask < combinations; mask++) {

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

        return best;
    }

    /**
     * Returns true if two arrays have exactly the same contents.
     */
    static boolean matches(int[] a, int[] b) {

        if (a.length != b.length) return false;

        for (int i = 0; i < a.length; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }
}
