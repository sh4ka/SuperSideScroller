// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

	//Constructor
	ASuperSideScroller_Player();

protected:
	//Override base character class function to setup our player input component
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Sprint();

	void StopSprinting();

public:
	
	void Throw();

	void SpawnProjectile();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentNumberOfCollectables() { return NumberOfCollectables;}

	void IncrementNumberofCollectables(int32 Value);

private:
	bool bIsSprinting;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ThrowMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerProjectile> PlayerProjectile;

	int32 NumberOfCollectables;

	FTimerHandle PowerupHandle;
	bool bHasPowerupActive;
	void IncreaseMovementPowerup();
	void EndPowerup();
	
	
};
