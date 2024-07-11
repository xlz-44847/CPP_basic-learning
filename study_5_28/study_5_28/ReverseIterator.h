#pragma once
//反向迭代器：和正向迭代器的逻辑相似，只是方向相反
//为了方便起见，可以写一个反向迭代器的类模板，然后对于各种容器利用他们的正向迭代器实例化出他们独特的反向迭代器

//迭代器适配器
template <class Iterator, class Ref, class Ptr>	//模板参数传递的是容器的正向迭代器类型，元素引用以及元素指针
struct ReverseIterator	//反向迭代器和之前的正向迭代器等都一样，因为其成员全部都是公开的，所以使用struct结构体定义 
{
	//使用正向迭代器变量作为成员变量，可以通过正向迭代器的行为模拟出反向迭代器的效果
	Iterator _it;

	//构造函数
	ReverseIterator(Iterator it)
		:_it(it)
	{}

	//首先要明白反向迭代器的使用原理
	//为了满足对称，反向迭代器和正向迭代器的指向刚好相反，所以正向迭代器的begin是反向迭代器的end，正向迭代器的end是反向迭代器的begin
	//因此就可以发现，正向迭代器可以直接访问的位置，对于反向迭代器而言实际上是所在位置的前一个位置（因为从end开始，而end位置是不访问的）
	//有了这样的认识，我们就可以妥善处理解引用了
	Ref operator*()
	{
		//因为需要访问前一个位置，且解引用不改变迭代器的指向，所以通过一个临时变量来找到前一个位置
		//对于其中出现的--操作和*操作，是调用了正向迭代器Iterator的操作符重载，这也就是所谓的通过正向迭代器实现反向迭代器
		Iterator tmp = _it;
		return *(--tmp);
	}
	Ptr operator->()
	{
		//和*一样，解引用访问前一个位置，所以使用临时变量
		//Iterator tmp = _it;
		//return (--tmp).operator->();	//调用->解引用操作符作为返回值
		return &(operator*());	//复用反向迭代器自己的*重载函数，*重载返回所要求的位置值引用，对其取地址即可
	}
	
	//因为自增运算需要返回操作数本身，所以迭代器自增自减运算也需要返回迭代器变量，为了方便编写，将返回类型为自身的反向迭代器进行typedef
	typedef ReverseIterator<Iterator, Ref, Ptr> self;
	//前置++，反向迭代器的++实际上迭代器在向前走
	self& operator++()	
	{
		--_it;
		//return _it;	//返回的是反向迭代器的引用类型，所以不支持隐式类型转换
		return *this;
	}
	//前置--，反向迭代器的--实际上迭代器在向后走
	self& operator--()
	{
		++_it;
		return *this;
	}
	bool operator!=(const self& rit)
	{
		return _it != rit._it;
	}
};