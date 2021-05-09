#include "BaseApplication.h"

int WS::BaseApplication::Initialize()
{
	m_bQuit = false;

	return 0;
}

void WS::BaseApplication::Finalize()
{
}

void WS::BaseApplication::Tick()
{
}

bool WS::BaseApplication::IsQuit()
{
	return m_bQuit;
}
