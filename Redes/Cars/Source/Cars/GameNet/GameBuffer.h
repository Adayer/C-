// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Net/buffer.h"
#include "Math/Vector.h"
#include "Math/Transform.h"

class CGameBuffer : public Net::CBuffer
{
public:
	CGameBuffer(size_t initsize = 500, size_t delta = 100);
	virtual ~CGameBuffer();
	
	using Net::CBuffer::write;
	using Net::CBuffer::read;

	//Write
	void write(const FVector& _data);
	void write(const FVector2D& _data);
	void write(const FTransform& _data);

	//Read
	void read(FVector& data_);
	void read(FVector2D& data_);
	void read(FTransform& data_);
};
