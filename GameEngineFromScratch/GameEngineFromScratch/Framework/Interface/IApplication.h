#pragma once

#include "Interface.h"
#include "IRuntimeModule.h"

namespace WS {
	Interface IApplication : implements IRuntimeModule
	{
	public:
		virtual bool IsQuit() = 0;
	};
}