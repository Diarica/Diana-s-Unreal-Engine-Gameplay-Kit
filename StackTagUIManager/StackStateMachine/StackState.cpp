#include "StackState.h"

void UStackState::EnterState(EStackAction StackAction)
{
	//Update State Of Blueprint
	ReceiveEnterState(StackAction);
}

void UStackState::ExitState(EStackAction StackAction)
{
	ReceiveExitState(StackAction);
}