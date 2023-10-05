public class IntParser {
    private static int charToInt(char c) {
        return ((int) c) - 48;
    }

    private static int firstNumIdx(char[] chars) {
        int charInt;
        for (int i = 0; i < chars.length; i++) {
            charInt = (int) chars[i];
            if (charInt >= 48 && charInt <= 57) {
                return i;
            }
        }
        return -1;
    }


    private static int lastNumIdx(char[] chars, int first) {
        int charInt;
        int i = first;
        for (; i < chars.length; i++) {
            charInt = (int) chars[i];
            if (charInt > 57 || charInt < 48) {
                return (i == 0) ? 0 : i - 1;
            }
        }
        return i - 1;
    }


    public static int parse(String _s) {
        char[] chars = _s.toCharArray();
        if (chars.length == 0) {
            return 0;
        }

        int first = firstNumIdx(chars);
        if (first == -1) {
            return 0;
        }
        int last = lastNumIdx(chars, first);

        int result = 0;
        for (int i = last; i >= first; i--) {
            result += (charToInt(chars[i]) * Math.pow(10, last - i));
        }
        
        return result;
    }


    public static void main(String[] args) {
        assert (1234 == parse("abc1234def"));
        assert (1234 == parse("abc1234"));
        assert (1234 == parse("1234def"));
        assert (1234 == parse("1234"));
        assert (1234 == parse("1234a45bar231"));

        System.out.println("[OK] All tests are passed!");
    }
}
