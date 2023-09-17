package main


func main() {
    dll := &DLL{}
    nums := []int{12, 43, 673, 48, 3521}

    for _, i := range nums {
        dll.Append(i)
    }

    dll.Prepend(912)
    dll.Print()
}
