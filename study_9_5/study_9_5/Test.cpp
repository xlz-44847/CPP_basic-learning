#include "HashTable.h"

void Test1()
{
	HashTable_open_address::HashTable<int, int> h;
	h.Insert({ 1,1 });
	h.Insert({ 4,11 });
	h.Insert({ 7,2 });
	h.Insert({ 22,65 });
	h.Insert({ 3,3 });
	h.Insert({ 54,33 });
	h.Insert({ 34,6 });
	h.Insert({ 12,122 });
	h.Insert({ 81,14 });

	h.Erase(4);
}

void Test2()
{
	HashTable_open_address::HashTable<string, string> h;
	h.Insert({ "window","窗户"});
	h.Insert({ "core","核心"});
	h.Insert({ "hand","手"});
	h.Insert({ "put","放"});
	h.Insert({ "handicap","障碍"});
	h.Insert({ "conspicuous","显著的"});
	h.Insert({ "snob","小人"});
	h.Insert({ "elicit","引出"});
	h.Insert({ "ask","问"});

	h.Erase("put");
}

void Test3()
{
	HashTable_bucket::HashTable<int, int> h;
	h.Insert({ 1,1 });
	h.Insert({ 4,11 });
	h.Insert({ 7,2 });
	h.Insert({ 22,65 });
	h.Insert({ 3,3 });
	h.Insert({ 54,33 });
	h.Insert({ 34,6 });
	h.Insert({ 12,122 });
	h.Insert({ 19,132 });
	h.Insert({ 32,34 });
	h.Insert({ 81,14 });

	h.Erase(4);
}

void Test4()
{
	HashTable_bucket::HashTable<string, string> h;
	h.Insert({ "window","窗户"});
	h.Insert({ "core","核心"});
	h.Insert({ "hand","手"});
	h.Insert({ "put","放"});
	h.Insert({ "handicap","障碍"});
	h.Insert({ "conspicuous","显著的"});
	h.Insert({ "snob","小人"});
	h.Insert({ "elicit","引出"});
	h.Insert({ "ask","问"});
	h.Insert({ "basic","基础的"});
	h.Insert({ "study","学习"});

	h.Erase("put");
}


int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
}