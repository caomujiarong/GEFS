#pragma once

#include "IApplication.h"

namespace WS {
	class BaseApplication : implements IApplication
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		// One cycle of the main loop
		virtual void Tick() override;

		virtual bool IsQuit() override;

	protected:
		// Flag if need quit the main loop of the application
		bool m_bQuit;
	};
}