#include "struct_serialization.h"
#include "data_struct/complete_binary_tree.h"
#include "data_struct/hash_set.h"
#include "data_struct/queue.h"
#include "data_struct/stack.h"
#include "data_struct/list.h"
#include "data_struct/flist.h"
#include "data_struct/string_view.cpp"

using namespace std;
using namespace data_struct;


int main()
{
    DynamicArray<int> arr {1, 2, 3, 4, 5, 6};
    List<int> list {1, 2, 3, 4, 5, 6};
    FList<int> flist {1, 2, 3, 4, 5, 6};
    Stack<int> s {1, 2, 3, 4, 5, 6};
    Queue<int> q {7, 8, 9, 10, 11, 12};
    HashSet<int> hs {1, 2, 3, 4, 5, 6};
    CompleteBinTree<int> tree {1, 2, 3, 4, 5, 6};
    HashTable<string, int> table {
        {"1", 1}
      , {"2", 2}
      , {"3", 3}
    };
    
    json j;
    SerializeAll(j, arr, list, flist, s, q, hs, tree, table);
    ofstream jsonOut ("structs.json");
    jsonOut << j.dump(4);
    jsonOut.close();

    ifstream jsonIn ("structs.json");
    auto j2 = json::parse (jsonIn);
    jsonIn.close();

    auto l = j2["list"].get<List<int>>();

    for (auto& el : l) {
        cout << el << " ";
    }
}