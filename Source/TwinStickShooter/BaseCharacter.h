// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TWINSTICKSHOOTER_API ABaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=BaseCharacter)
    bool IsDead{false};

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category=BaseCharacter)
    float Health{100};

    // Sets default values for this character's properties
    ABaseCharacter();

    virtual void CalculateDead()
    {
        IsDead = Health <= 0;
    }

    UFUNCTION(BlueprintCallable, Category=BaseCharacter)
    virtual void CalculateHealth(const float Delta)
    {
        Health += Delta;
        CalculateDead();
    }

#if WITH_EDITOR
    void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
    {
        Health = 100;
        IsDead = false;
        Super::PostEditChangeProperty(PropertyChangedEvent);
        CalculateDead();
    }
#endif

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
