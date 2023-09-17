package main

import (
    "fmt"
    "flag"
    "math/rand"
)

func gen_rand_num(min, max int) int {
    return (rand.Intn(max - min) + min)
}

func break_array(arr *[]int, max_len int) [][]int {
    right := 0
    left  := 0
    arr_len := len(*arr)
    var tmp []int
    var super_list [][]int

    if max_len >= arr_len {
        super_list = append(super_list, *arr)
        return super_list
    }

    for right < arr_len {
        left = gen_rand_num(right, (right + max_len))
        for right == left { // prevent empty sub-list
            left = gen_rand_num(right, (right + max_len))
        }
        if left >= arr_len {
            left = arr_len - 1
        }

        tmp = (*arr)[right:left + 1]
        super_list = append(super_list, tmp)

        right = left + 1
    }

    return super_list
}


func main() {
    max := flag.Int("max", 5, "maximum length of sub-lists")
    flag.Parse()

    var nums []int
    for i := 0; i < 50; i++ {
        nums = append(nums, i)
    }

    super_list := break_array(&nums, *max)

    for i := 0; i < len(super_list); i++ {
        fmt.Println(super_list[i])
    }
}
