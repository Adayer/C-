#pragma once
#include <stdio.h>
class CStream
{
public: 
	virtual void Open() { printf("BASE OPEN"); }
	virtual void Close() { printf("BASE CLOSE"); }
	virtual void Read() { printf("BASE READ"); }
	virtual void Write() { printf("BASE WRITE"); }
};

class CFile : public CStream
{
public:
	virtual void Open() override { printf("Opening CFile\n"); }
	virtual void Close() override { printf("Closing CFile\n"); }
	virtual void Read() override { printf("Reading CFile\n"); }
	virtual void Write() override { printf("Writing CFile\n"); }
};

class CCom : public CStream
{
public:
	virtual void Open() override { printf("Opening CCom\n"); }
	virtual void Close() override { printf("Closing CCom\n"); }
	virtual void Read() override { printf("Reading CCom\n"); }
	virtual void Write() override { printf("Writing CCom\n"); }
};

class CTcp : public CStream
{
public:
	virtual void Open() override { printf("Opening CTcp\n"); }
	virtual void Close() override { printf("Closing CTcp\n"); }
	virtual void Read() override { printf("Reading CTcp\n"); }
	virtual void Write() override { printf("Writing CTcp\n"); }
};
