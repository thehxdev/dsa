package aoc2021.d2;

class Submarine {
    public int horizontal = 0;
    public int depth = 0;
    public int aim = 0;

    public int currentLocation() {
        return (this.horizontal * this.depth);
    }
}
