#pragma once

namespace test {

	class Test
	{
	public:
		Test();
		virtual ~Test() = default;

		virtual void OnUpdate(float DeltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

}