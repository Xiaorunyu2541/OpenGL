#pragma once

#include "test.h"

namespace test 
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor(){}
		~TestClearColor() = default;

		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_Color[4];
	};
}