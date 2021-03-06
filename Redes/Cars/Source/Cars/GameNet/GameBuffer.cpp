// Fill out your copyright notice in the Description page of Project Settings.


#include "GameNet/GameBuffer.h"


CGameBuffer::CGameBuffer(size_t initsize, size_t delta) :
	CBuffer(initsize, delta)
{

}

CGameBuffer::~CGameBuffer()
{

}

//FVector
void CGameBuffer::write(const FVector& _data)
{
	write(_data.X);
	write(_data.Y);
	write(_data.Z);
}

void CGameBuffer::read(FVector& data_)
{
	read(data_.X);
	read(data_.Y);
	read(data_.Z);
}
//FVector2D
void CGameBuffer::write(const FVector2D& _data)
{
	write(_data.X);
	write(_data.Y);
}
void CGameBuffer::read(FVector2D& data_)
{
	read(data_.X);
	read(data_.Y);
}

//FTransform
void CGameBuffer::write(const FTransform& _data)
{
	//Position
	write(_data.GetTranslation());
	write(_data.GetRotation().GetAxisX());

}
void CGameBuffer::read(FTransform& data_)
{
	FVector vPos;
	read(vPos);
	FVector vDir;
	read(vDir);

	FMatrix tMatrix = FRotationMatrix::MakeFromX(vDir);
	data_.SetFromMatrix(tMatrix);
	data_.SetLocation(vPos);
}
