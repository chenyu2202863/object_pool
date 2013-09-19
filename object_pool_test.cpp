// object_pool_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "object_pool.hpp"

#include <tbb/concurrent_queue.h>

namespace utility  {

	template < >
	struct object_pool_traits_t<tbb::concurrent_bounded_queue<std::shared_ptr<int>>>
	{
		typedef std::shared_ptr<int> value_t;
		typedef tbb::concurrent_bounded_queue<value_t> container_t;
		

		static value_t pop(container_t &l)
		{
			value_t v;
			if( !l.try_pop(v) )
				return std::make_shared<int>();

			return v;
		}

		static void push(container_t &l, value_t && val)
		{
			l.push(val);
		}
	};

}

int _tmain(int argc, _TCHAR* argv[])
{
	utility::object_pool_t<int> pool1([]()
	{
		return std::make_shared<int>(10);
	});

	{
		auto t = pool1.get();
	}

	utility::object_pool_t<int, tbb::concurrent_bounded_queue<std::shared_ptr<int>>> pool2([]()
	{
		return std::make_shared<int>(1);
	});

	{
		auto t = pool2.get(tbb::tbb_allocator<char>());
	}

	{
		auto n = pool2.raw_aciquire();
		*n = 12;
		pool2.raw_release(std::move(n));
	}

	system("pause");
	return 0;
}

