#pragma once

namespace test {

	class Test
	{
		Test();
		virtual ~Test() = default;

		virtual void OnUpdate(float DeltaTime){}
	};

}