#pragma once

namespace c3p1
{
	class exception
	{
	public:
		exception(const char* msg);
		const char* message;
	};
}