C++ object pool

Copyright (c) 2013, Chen Yu. All rights reserved.

Use of this source code is governed by a BSD-style license that can be found in the License file.

使用方式:
	utility::object_pool_t<int> pool1([]()
	{
		return std::make_shared<int>(10);
	});

	{
		auto t = pool1.get();
	}