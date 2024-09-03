#include"array.h"

namespace m_array
{
	//在声明处给出缺省值
	//模板的声明和定义分离这样写会导致链接错误
	
	template<class T, size_t N>
	size_t array<T, N>::size() const
	{
		return _size;
	}
	
	//因为各个cpp文件单独编译，模板实例化发生在编译之前，所以在链接之前并不知道实例化成什么类型，所以不会生成其他cpp文件需要的实例化形式

	//通过如下方式进行显式实例化后，生成了其他文件需要的实例化形式就可以在链接的时候成功调用了
	template
	array<int, 5>;
}