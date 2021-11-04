#include "NewDebugger.h"

NewDebugger* NewDebugger::INSTANCE;
std::thread NewDebugger::DebuggerThread;
NewDebugger* NewDebugger::GetInstance()
{
	if (!INSTANCE) DebuggerThread = std::thread(NewDebugger());
	return INSTANCE;
}

bool NewDebugger::ShouldShutdown = false;
void NewDebugger::ShutDown()
{
	ShouldShutdown = true;
	DebuggerThread.join();
}
