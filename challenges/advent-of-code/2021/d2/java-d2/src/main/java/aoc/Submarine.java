package aoc;

class Submarine {
    public int horizontal = 0;
    public int depth = 0;
    public int aim = 0;

    public int currentLocation() {
        return (this.horizontal * this.depth);
    }
}
