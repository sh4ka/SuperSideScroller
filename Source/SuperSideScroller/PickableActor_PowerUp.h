// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
#include "PickableActor_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API APickableActor_PowerUp : public APickableActor_Base
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void PlayerPickedUp(ASuperSideScroller_Player* Player) override;
	
};
