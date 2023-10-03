package aoc2021.d4;

import java.util.ArrayList;


public class Game {
    private ArrayList<Integer> results;
    private ArrayList<Board> boards;
    private Board winner;
    private int lastNum;

    public Game parseInputInfo(ArrayList<String> lines) {
        this.results = Parser.parseResults(lines.get(0));
        this.boards  = new ArrayList<Board>();

        for (int i = 1; i < lines.size(); i += 5) {
            boards.add(Parser.parseBoard(lines.subList(i, i + 5)));
        }

        return this;
    }

    public Game play() {
        for (int res : this.results) {
            for (Board b : this.boards) {
                b.markNumber(res);
                if (b.isWinner()) {
                    this.winner = b;
                    this.lastNum = res;
                    return this;
                }
            }
        }
        return this;
    }

    public int solvePart1() {
        return this.winner.scoreSum() * this.lastNum;
    }
}
