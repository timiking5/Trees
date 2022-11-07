#include <iostream>
#include "Header.h"

int main()
{
    BinaryTreeRB bebra = BinaryTreeRB(5);
    bebra.Insert(4);
    bebra.Insert(6);
    bebra.TreeWalkLVR(bebra);
}

