#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};


///////////////////////////////////
/// Solution
///////////////////////////////////

struct ListNode *newListNode(int val) {
    struct ListNode *ln = malloc(sizeof(*ln));
    *ln = (struct ListNode){
        .val = val,
        .next = NULL,
    };
    return ln;
}


struct ListNode *appendNode(struct ListNode **ln, int val) {
    struct ListNode *tmp = *ln;

    if (tmp == NULL) {
        *ln = newListNode(val);
        return *ln;
    }

    while (tmp->next)
        tmp = tmp->next;

    tmp->next = newListNode(val);
    return tmp->next;
}


struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    int digitsSum = 0, leadingOne = 0;
    struct ListNode *sum = NULL;

    while (1) {
        digitsSum = ((l1) ? (l1->val) : 0) + ((l2) ? (l2->val) : 0) + leadingOne;
        if (digitsSum >= 10) {
            appendNode(&sum, digitsSum - 10);
            leadingOne = 1;
            goto skip;
        }
        if (l1 == NULL && l2 == NULL && digitsSum == 0)
            break;

        appendNode(&sum, digitsSum);
        leadingOne = 0;

    skip:
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }

    return sum;
}

///////////////////////////////////
/// Test
///////////////////////////////////

struct ListNode *numToListNodes(int num) {
    int digit;
    struct ListNode *ln = NULL;
    while (num > 0) {
        digit = num % 10;
        appendNode(&ln, digit);
        num /= 10;
    }
    return ln;
}


int main(void) {
    struct ListNode *l1 = numToListNodes(342);
    struct ListNode *l2 = numToListNodes(465);

    struct ListNode *sum = addTwoNumbers(l1, l2);

    while (sum) {
        printf("%d", sum->val);
        sum = sum->next;
    }
}
