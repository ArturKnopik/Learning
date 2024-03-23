#pragma once

#include "export.h"

#include <functional>

namespace KOD {
namespace GUI {

using CallableFunc = std::function<void()>;

class Callable
{
public:
	GUI_API ~Callable();
	GUI_API Callable(CallableFunc&& task);
	GUI_API void execute();

private:
	Callable(){};
	CallableFunc m_callable;
};

} // namespace GUI
} // namespace KOD