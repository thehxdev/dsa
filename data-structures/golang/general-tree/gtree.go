package main

import (
    "fmt"
)


type Node struct {
    val     int
    parent  *Node
    children []*Node
}


type GTree struct {
    root *Node
}


func (t *GTree) Add(val int, parent *Node) *Node {
    n := &Node{
        val: val,
        parent: parent,
        children: nil,
    }

    if t.root == nil && parent == nil {
        t.root = n
        return n
    } else if t.root != nil && parent == nil {
        return nil
    }

    parent.children = append(parent.children, n)
    return n
}


func (t *GTree) Print(n *Node) {
    if n != nil {
        fmt.Println(n)
        for _, child := range n.children {
            t.Print(child)
        }
    }
}


func __find_helper(val int, n *Node, res *Node) {
    if n != nil {
        if n.val == val {
            *res = *n
            return
        }
        for _, child := range n.children {
            __find_helper(val, child, res)
        }
    }
}


func (t *GTree) Find(val int, n *Node) *Node {
    result := &Node{}
    __find_helper(val, n, result)
    return result
}
