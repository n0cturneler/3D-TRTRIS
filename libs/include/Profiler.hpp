#pragma once

#include <chrono>
#include <iostream>

namespace Perf
{
	class Timer
	{
	public:
		Timer()
			: m_start{std::chrono::high_resolution_clock::now()}
		{
		}

		~Timer()
		{
			auto end{std::chrono::high_resolution_clock::now()};
			auto diff{end - m_start};

			std::cout << "\033[90mTime taken: \033[92m"
				<< std::chrono::duration<double, std::milli>(diff).count()
				<< "\033[0m \033[90mms\n\033[0m";
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	};
}
