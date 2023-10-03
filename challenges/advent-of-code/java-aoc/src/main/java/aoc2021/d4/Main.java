package aoc2021.d4;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;


class Main {
    public static void main(String[] args) {
        final String programName = "PROGRAM";
        if (args.length != 1) {
            System.err.printf("Usage: %s <input-file-path>\n", programName);
            System.exit(1);
        }

        File inputFile = new File(args[0]);
        Scanner fileReader = null;
        try {
            fileReader = new Scanner(inputFile);
        } catch (FileNotFoundException e) {
            System.err.printf("[ERROR] file %s not found.", args[0]);
            e.printStackTrace();
            System.exit(1);
        }

        ArrayList<String> lines = new ArrayList<String>();
        while (fileReader.hasNextLine()) {
            String line = fileReader.nextLine().strip();
            if (line.length() == 0) {
                continue;
            }
            lines.add(line);
        }
        fileReader.close();

        Game game = new Game()
            .parseInputInfo(lines)
            .play();

        System.out.println("== AOC 2021 Day 4 ==");
        System.out.printf("Part 1: %d\n", game.solvePart1());
    }
}
