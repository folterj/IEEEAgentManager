#include "StdAfx.h"
#include "DelimLine.h"

DelimLine::DelimLine()
{
	items = gcnew array<String^>(0);
}

String^ DelimLine::toString()
{
	String^ s;

	for (int i=0;i<items->Length;i++) {
		if (i > 0) {
			s += "|";
		}
		s += items[i];
	}

	return s;
}
