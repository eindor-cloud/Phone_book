#include "Contact.h"
#include <stdbool.h>
extern struct Contact;
extern struct Contact_Node;

/* function prototypes */
struct Contact_Node* SortedMerge(struct Contact_Node* a, struct Contact_Node* b, bool (*cmp_func)(Contact* a, Contact* b));
void FrontBackSplit(struct Contact_Node* source,
    struct Contact_Node** frontRef, struct Contact_Node** backRef);
bool compare_by_fname(Contact* a, Contact* b);
bool compare_by_lname(Contact* a, Contact* b);
bool compare_by_phone(Contact* a, Contact* b);
bool compare_by_cphone(Contact* a, Contact* b);

/* sorts the linked list by changing next pointers (not data) */
Contact_Node* MergeSort(struct Contact_Node headRef, char compare_by)
{
    struct Contact_Node* head = *headRef;
    struct Contact_Node* a;
    struct Contact_Node* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a, compare_by);
    MergeSort(&b, compare_by);

    /* answer = merge the two sorted lists together */
    switch (compare_by)
    {
    case '1': *headRef = SortedMerge(a, b, compare_by_fname);
        break;
    case '2': *headRef = SortedMerge(a, b, compare_by_lname);
        break;
    case '3': *headRef = SortedMerge(a, b, compare_by_phone);
        break;
    case '4': *headRef = SortedMerge(a, b, compare_by_cphone);
        break;

    }
    *headRef = SortedMerge(a, b);
    return headRef;
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
struct Contact_Node* SortedMerge(struct Contact_Node* a, struct Contact_Node* b, bool (*cmp_func)(Contact* a, Contact* b))
{
    struct Contact_Node* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (cmp_func(a->data, b->data)) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct Contact_Node* source,
    struct Contact_Node** frontRef, struct Contact_Node** backRef)
{
    struct Contact_Node* fast;
    struct Contact_Node* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

/* Function to print nodes in a given linked list */
void printList(struct Contact_Node* node)
{
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

/* Function to insert a node at the beginning of the linked list */
void push(struct Contact_Node** head_ref, int new_data)
{
    /* allocate node */
    struct Contact_Node* new_node = (struct Contact_Node*)malloc(sizeof(struct Contact_Node));

    /* put in the data */
    new_node->data = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Driver program to test above functions*/
int main()
{
    /* Start with the empty list */
    struct Contact_Node* res = NULL;
    struct Contact_Node* a = NULL;

    /* Let us create a unsorted linked lists to test the functions
Created lists shall be a: 2->3->20->5->10->15 */
    push(&a, 15);
    push(&a, 10);
    push(&a, 5);
    push(&a, 20);
    push(&a, 3);
    push(&a, 2);

    /* Sort the above created Linked List */
    MergeSort(&a);

    printf("Sorted Linked List is: \n");
    printList(a);

    getchar();
    return 0;
}

bool compare_by_fname(Contact* a, Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}
bool compare_by_lname(Contact* a, Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}
bool compare_by_phone(Contact* a, Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}
bool compare_by_cphone(Contact* a, Contact* b)
{
    return strcmp(a->fname, b->fname) > 0;
}