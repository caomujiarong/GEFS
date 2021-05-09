// GameEngineFromScratch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "IApplication.h"

using namespace WS;
using namespace std;

namespace WS {
    extern IApplication* g_pApp;
}

int main(int argc, char** argv)
{
    int ret;

    if ((ret = g_pApp->Initialize()) != 0)
    {
        printf("App Initialize failed, will exit now.");
        return ret;
    }
    
    while (!g_pApp->IsQuit())
    {
        g_pApp->Tick();
    }

    g_pApp->Finalize();

    return 0;
}
