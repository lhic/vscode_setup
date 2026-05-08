//bitset
_Find_first(); _Find_next(prev);
//PBDS
//#include <ext/pb_ds/assoc_container.hpp>
#include <bits/extc++.h>
using namespace __gnu_pbds;

//set
typedef tree<int,
		null_type,
		less<int>,
		rb_tree_tag,
		tree_order_statistics_node_update>
		ordered_set;

find_by_order(k);
order_of_key(x);
//Первая возвращает итератор на k-ый по величине элемент (отсчёт с нуля), вторая — возвращает количество элементов в множестве, строго меньших, чем наш элемент.

//hasttable

gp_hash_table<int, int> table;

//SSE pragma

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx") 

//measure time
ld sum = 0;
auto start = std::chrono::system_clock::now();
auto end = std::chrono::system_clock::now();
sum += std::chrono::duration<double>(end - start).count();

