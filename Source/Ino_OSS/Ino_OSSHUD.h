// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Ino_OSSHUD.generated.h"

UCLASS()
class AIno_OSSHUD : public AHUD
{
	GENERATED_BODY()

public:
	AIno_OSSHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

