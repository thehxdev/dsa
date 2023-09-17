package main

import (
    "fmt"
)


func main() {
    tree := &GTree{}

    root := tree.Add(50, nil)

    r_ch1 := tree.Add(34, root)
    _ = tree.Add(1, root)
    _ = tree.Add(71, root)
    _ = tree.Add(182, r_ch1)

    tree.Print(root)

    fmt.Println(tree.Find(182, root))
}
