/**
 * Parse int values in ascii strings
 */

import java.util.ArrayList;


public class IntParser {
    private static int charToInt(char c) {
        return ((int) c) - 48;
    }


    public static int parse(String s) {
        char[] chars = s.toCharArray();
        if (chars.length == 0) {
            return 0;
        }

        int right = 0, left = 0, result = 0;
        while (right < chars.length) {
            int rightChar = (int) chars[right];

            if (rightChar >= 48 && rightChar <= 57) {
                left = right;

                while (left < chars.length) {
                    int leftChar = (int) chars[left];
                    if (leftChar < 48 || leftChar > 57) {
                        break;
                    }
                    left++;
                }

                for (int i = left - 1; i >= right; i--) {
                    result += (charToInt(chars[i]) * Math.pow(10, left - i - 1));
                }
                return result;
            }

            right++;
        }
        return 0;
    }


    public static ArrayList<Integer> parseAll(String s) {
        char[] chars = s.toCharArray();
        ArrayList<Integer> nums = new ArrayList<Integer>();

        int right = 0, left = 0, tmp = 0;

        while (right < chars.length) {
            int rightChar = (int) chars[right];

            if (rightChar >= 48 && rightChar <= 57) {
                left = right;

                while (left < chars.length) {
                    int leftChar = (int) chars[left];
                    if (leftChar < 48 || leftChar > 57) {
                        break;
                    }
                    left++;
                }

                tmp = parse(s.substring(right, left));
                nums.add(tmp);
                right = left;
                continue;
            }
            right++;
        }

        return nums;
    }


    public static void main(String[] args) {
        assert (1234 == parse("abc1234def"));
        assert (1234 == parse("abc1234"));
        assert (1234 == parse("1234def"));
        assert (1234 == parse("1234"));
        assert (1234 == parse("1234a45bar231"));
        assert (123445 == parse("123445bar231"));
        assert (43 == parse("43 3445bar231"));
        assert (0 == parse(""));

        System.out.println(parseAll("123abc435j545foo 43"));
        System.out.println("[OK] All tests are passed!");
    }
}
