#include "RogueAction.h"

void URogueAction::StartAction()
{
	float GameTime = 0.0f;
	//GetWorld()->TimeSeconds;

	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}",
	          ("ActionName", ActionName),
	          ("WorldTime", GameTime));
}
