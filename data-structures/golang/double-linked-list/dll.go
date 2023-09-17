package main

import "fmt"


type Node struct {
    val int
    next *Node
    prev *Node
}


type DLL struct {
    head *Node
    tail *Node
}


func (dll *DLL) Append(val int) *Node {
    n := &Node{
        val: val,
    }

    if dll.head == nil {
        dll.head = n
        dll.tail = n
        return n
    }

    n.prev = dll.tail
    dll.tail.next = n
    dll.tail = n

    return n
}


func (dll *DLL) Prepend(val int) *Node {
    if dll.head == nil {
        return dll.Append(val)
    }

    n := &Node{
        val: val,
        next: dll.head,
    }

    dll.head.prev = n
    dll.head = n

    return n
}


func (dll *DLL) Find(val int) *Node {
    tmp := dll.head
    for tmp != nil {
        if tmp.val == val {
            return tmp
        }
        tmp = tmp.next
    }
    return nil
}


func (dll *DLL) Delete(n *Node) {
    if n == nil {
        return
    }

    if n.prev != nil {
        n.prev.next = n.next
    }
    if n.next != nil {
        n.next.prev = n.prev
    }
    n = nil
}


func (dll *DLL) Print() {
    tmp := dll.head
    for tmp != nil {
        fmt.Println(tmp.val)
        tmp = tmp.next
    }
}
