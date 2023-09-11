package main

import (
    "fmt"
)


func main() {
    bt := BTree {
        Root: nil,
    }

    nums := []int{84, 32, 14, 1, 2, 4, 65, 98, 102}
    for _, i := range nums {
        _ = bt.Add(bt.Root, i)
    }

    bt.Print(bt.Root)

    fmt.Println("\nMax value:", bt.FindMax(bt.Root).Data)
    fmt.Println("Min value:", bt.FindMin(bt.Root).Data)
}
