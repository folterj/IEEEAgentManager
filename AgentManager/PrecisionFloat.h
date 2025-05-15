#pragma once

using namespace System;

ref class PrecisionFloat
{
public:
	float value;
	int precision;

	PrecisionFloat();
	PrecisionFloat(float value0,int precision0);
	PrecisionFloat(UInt16 val);
	PrecisionFloat(UInt32 val);

	void set(float value0,int precision0);
	void set(UInt16 val);
	void set(UInt32 val);
	void set(UInt64 val,int valSize,int expSize);

	UInt16 getBasic();
	UInt32 getSimple();
	UInt64 getPFloat(int valSize,int expSize);

	virtual String^ ToString() override;
};
