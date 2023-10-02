package aoc;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String programName = "practice";
        if (args.length != 1) {
            System.out.printf("Usage: %s <file-path>\n", programName);
            System.exit(1);
        }


        File inputFile = new File(args[0]);
        Submarine s1 = new Submarine();
        Submarine s2 = new Submarine();
        Scanner fileReader = null;


        try {
            fileReader = new Scanner(inputFile);
        } catch (FileNotFoundException e) {
            System.out.println("[ERROR] Could not open file.");
            e.printStackTrace();
            System.exit(1);
        }


        int command_num = 0;
        while (fileReader.hasNextLine()) {
            String line = fileReader.nextLine();
            command_num = extractNumber(line);
            switch (line.charAt(0)) {
                case 'f':
                    s1.horizontal += command_num;
                    s2.horizontal += command_num;
                    s2.depth += s2.aim * command_num;
                    break;
                case 'u':
                    s1.depth -= command_num;
                    s2.aim -= command_num;
                    break;
                case 'd':
                    s1.depth += command_num;
                    s2.aim += command_num;
                    break;
                default:
                    break;
            }
        }
        fileReader.close();

        System.out.printf("Part 1: %d\n", s1.currentLocation());
        System.out.printf("Part 2: %d\n", s2.currentLocation());
    }


    public static int extractNumber(String str) {
        String[] words = str.split(" ");
        String num_str = words[1];
        return Integer.parseInt(num_str);
    }
}
