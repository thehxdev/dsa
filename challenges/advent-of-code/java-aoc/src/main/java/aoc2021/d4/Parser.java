package aoc2021.d4;

import java.util.List;
import java.util.ArrayList;

public class Parser {
    public static ArrayList<Integer> parseResults(String s) {
        ArrayList<Integer> res = new ArrayList<Integer>();
        String[] numsStr = s.split(",");
        for (String num : numsStr) {
            res.add(Integer.parseInt(num));
        }

        return res;
    }

    private static ArrayList<Integer> parseRow(String r) {
        ArrayList<Integer> arr = new ArrayList<Integer>();
        String[] numsStr = r.replace("  ", " ").split(" ");
        
        for (String num : numsStr) {
            arr.add(Integer.parseInt(num.strip()));
        }

        return arr;
    }

    public static Board parseBoard(List<String> b) {
        Board board = new Board();

        for (String row : b) {
            board.rows.add(parseRow(row));
        }

        return board;
    }
}
