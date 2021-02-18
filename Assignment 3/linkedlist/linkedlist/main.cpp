#include <iostream>
#include <string>
#include "List.h"
#include "ListNode.h"

using namespace std;

template <typename anyType>
void fillList(anyType input, List<char>& list);

int main()
{
    List<char> list1;
    List<char> list2;
    List<char> list3;
    List<char> list4;
    fillList("singlylinkedlist", list1);
    fillList("abcdefg", list2);
    fillList("hijklmnop", list3);
    fillList("qrstuvw", list4);
    list2.concatenate(list3);
    list2.concatenate(list4);
    list1.print();
    list2.print();
    list3.print();
    list4.print();
    return 0;
}

template <typename anyType>
void fillList(anyType input, List<char>& list)
{
    int nThCharacter{0};
    while (input[nThCharacter])
    {
        list.insertAtBack(input[nThCharacter]);
        nThCharacter++;
    }
}