// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CarMovementComponent.h"

// Sets default values for this component's properties
UCarMovementComponent::UCarMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCarMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCarMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	FVector vAccel(CalculateAcceleration());
	FVector vAverageVel(CalculateAverageVelocity(vAccel, DeltaTime));
	MoveActor(vAverageVel, DeltaTime);
}

FVector UCarMovementComponent::CalculateAcceleration() const
{
	FVector vAccel;
	//Forward Accel
	if (m_vMovementInput.Y > 0)
	{
		vAccel = m_fAccel * m_vMovementInput.Y * GetOwner()->GetActorForwardVector();
	}
	else if (m_vMovementInput.Y < 0)
	{
		vAccel = m_fBreakAccel * m_vMovementInput.Y * GetOwner()->GetActorForwardVector();
	}
	else
	{
		vAccel = -m_fDrag * GetOwner()->GetActorForwardVector();
	}
	//Turn Accel
	vAccel += (m_fRotationFactor * m_vVelocity.Size() * m_vMovementInput.X * GetOwner()->GetActorRightVector());
	return vAccel;
}

FVector UCarMovementComponent::CalculateAverageVelocity(const FVector& _vAccel, float _fDeltaTime)
{
	FVector vAverageVelocity = m_vVelocity + 0.5 * _vAccel * _fDeltaTime;
	ClampVelocity(vAverageVelocity);

	m_vVelocity += _vAccel * _fDeltaTime;
	ClampVelocity(m_vVelocity);

	return vAverageVelocity;
}
void UCarMovementComponent::ClampVelocity(FVector& _vVelocity_) const
{
	if (_vVelocity_ != FVector::ZeroVector && FVector::DotProduct(_vVelocity_,GetOwner()->GetActorForwardVector()) < 0.f)
	{
		_vVelocity_ = FVector::ZeroVector;
	}
	else if (_vVelocity_.SizeSquared() > (m_fMaxVelocity * m_fMaxVelocity))
	{
		_vVelocity_ *= (m_fMaxVelocity / _vVelocity_.Size());
	}
}
void UCarMovementComponent::MoveActor(const FVector& _vVelocity, float _fDeltaTime)
{
	FTransform mTrans(GetOwner()->GetActorTransform());
	mTrans.AddToTranslation(_vVelocity * _fDeltaTime);
	GetOwner()->SetActorTransform(mTrans);

	if (_vVelocity != FVector::ZeroVector)
	{
		FRotator oRotator = FRotationMatrix::MakeFromX(_vVelocity).Rotator();
		GetOwner()->SetActorRotation(oRotator);
	}
}
