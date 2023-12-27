#include "sort.h"
#include "searchTree.h"

bool sort(int* const array, const size_t lengthOfArray)
{
    SearchTree* tree = createTree();
    if (tree == NULL)
    {
        return true;
    }
    for (size_t i = 0; i < lengthOfArray; ++i)
    {
        bool errorOccured = addNode(tree, array[i]);
        if (errorOccured)
        {
            freeTree(&tree);
            return true;
        }
    }
    rewriteArray(tree, &array, lengthOfArray);
    freeTree(&tree);
    return false;
}
