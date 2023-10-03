package aoc2021.d4;

import java.util.ArrayList;


public class Board {
    public ArrayList<ArrayList<Integer>> rows;


    public Board() {
        this.rows   = new ArrayList<ArrayList<Integer>>();
    }

    public void markNumber(int num) {
        for (ArrayList<Integer> row : this.rows) {
            for (int i : row) {
                if (i == num) {
                    row.set(row.indexOf(i), -1);
                }
            }
        }
    }

    private boolean checkRows() {
        for (ArrayList<Integer> row : this.rows) {
            for (int i : row) {
                if (i != -1) {
                    return false;
                }
            }
        }
        return true;
    }

    private boolean checkColumns() {
        for (int i = 0; i < this.rows.size(); i++) {
            ArrayList<Integer> row1 = this.rows.get(0);
            ArrayList<Integer> row2 = this.rows.get(1);
            ArrayList<Integer> row3 = this.rows.get(2);
            ArrayList<Integer> row4 = this.rows.get(3);
            ArrayList<Integer> row5 = this.rows.get(4);

            if ((row1.get(i) & row2.get(i) & row3.get(i) & row4.get(i) & row5.get(i)) == -1) {
                return true;
            }
        }

        return false;
    }

    public boolean isWinner() {
        return (checkRows() || checkColumns());
    }

    public int scoreSum() {
        int sum = 0;
        for (ArrayList<Integer> row : this.rows) {
            for (int i : row) {
                if (i == -1) {
                    continue;
                }
                sum += i;
            }
        }
        return sum;
    }
}
