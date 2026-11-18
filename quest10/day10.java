package quest10;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.regex.*;

public class day10 {

    public static void main(String[] args) throws IOException {
        //need to implement the grids. 
        BufferedReader br = new BufferedReader(new FileReader("quest10/input.txt"));
        ArrayList<ArrayList<Integer>> targets = new ArrayList<>();
        ArrayList<ArrayList<ArrayList<Integer>>> allButtons = new ArrayList<>();
        String line;

        while ((line = br.readLine()) != null) {
            line = line.trim();

            //target 
            Matcher targetMatcher = Pattern.compile("\\[([.#]+)\\]")
                .matcher(line);
        

            if (targetMatcher.find()) {
                ArrayList<Integer> target = new ArrayList<>();

                String targetStr = targetMatcher.group(1);

                for (char c : targetStr.toCharArray()) {
                    if (c == '#') {
                        target.add(1);
                    } else {
                        target.add(0);
                    }
                }
                targets.add(target);
            }
                //buttons
                ArrayList<ArrayList<Integer>> machineButtons = new ArrayList<>();
                Matcher buttonMatcher = Pattern.compile("\\((.*?)\\)")
                    .matcher(line);
                while (buttonMatcher.find()) {
                    ArrayList<Integer> button = new ArrayList<>();
                    //group(1) the one is because there's only one capture group (.*?) but say you had more like in the case of 
                    //Pattern.compile("(\\d+),(\\d+)") then group 0 would combine them, group(1) would only be the first capture block and group(2) is jsut the second one.
                    String[] numbers = buttonMatcher.group(1).split(",");
                    for (String num : numbers) {
                        button.add(Integer.parseInt (num.trim()));
                    }
                    machineButtons.add(button);
                }
                allButtons.add(machineButtons);
        }
        br.close();

        // sum of best presses for all configs
        int totalValue = 0; 

        // Loop through all configurations
        for (int i = 0; i < targets.size(); i++) {
            int best = solveAndReturnBest(targets.get(i), allButtons.get(i));
            System.out.println("Minimum amount of presses = " + best);
            // add this config's best to the total
            totalValue += best; 
        }

        System.out.println("Total value (sum of all best presses) = " + totalValue);
    }

    /**
     * Tries all button combinations and returns the minimum presses
     * for a given target and button setup.
     */
    static int solveAndReturnBest(ArrayList<Integer> target, ArrayList<ArrayList<Integer>> buttons) {

        int best = Integer.MAX_VALUE;
        int combinations = 1 << buttons.size(); // $ 2^{buttons.length} $ subsets

        for (int mask = 0; mask < combinations; mask++) {

            int[] state = new int[target.size()];
            int presses = 0;

            for (int button = 0; button < buttons.size(); button++) {

                if ((mask & (1 << button)) != 0) {
                    presses++;

                    for (int light : buttons.get(button)) {
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
    static boolean matches(int[] state, ArrayList<Integer> target) {

        if (state.length != target.size()) return false;

        for (int i = 0; i < state.length; i++) {
            if (state[i] != target.get(i)) {
                return false;
            }
        }
        return true;
    }
}
