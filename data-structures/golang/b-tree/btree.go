package main

import "fmt"



type Node struct {
    Data   int
    Right  *Node
    Left   *Node
    Parent *Node
}


type BTree struct {
    Root *Node
}


func (t *BTree) Add(n *Node, val int) *Node {
    if t.Root == nil {
        node := &Node{
            Data: val,
            Right: nil,
            Left: nil,
            Parent: nil,
        }
        t.Root = node
        return node
    }

    if val < n.Data && n.Left == nil {
        node := &Node{
            Data: val,
            Left: nil,
            Right: nil,
            Parent: n,
        }
        n.Left = node
        return node
    } else if val >= n.Data && n.Right == nil {
        node := &Node{
            Data: val,
            Left: nil,
            Right: nil,
            Parent: n,
        }
        n.Right = node
        return node
    } else if val < n.Data && n.Left != nil {
        t.Add(n.Left, val)
    } else if val < n.Data && n.Left != nil {
        t.Add(n.Right, val)
    }

    return nil
}


func (t *BTree) Find(n *Node, val int) *Node {
    if n.Data == val {
        return n
    }

    if (n.Data > val) {
        return (t.Find(n.Left, val))
    } else {
        return (t.Find(n.Right, val))
    }
}


func (t *BTree) FindMax(n *Node) *Node {
    max := n
    for max.Right != nil {
        max = max.Right
    }

    return max
}


func (t *BTree) FindMin(n *Node) *Node {
    min := n
    for min.Left != nil {
        min = min.Left
    }
    return min
}


func (t *BTree) Print(n *Node) {
    if (n != nil) {
        t.Print(n.Left)
        fmt.Println(n.Data)
        t.Print(n.Right)
    }
}
