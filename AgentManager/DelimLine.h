#pragma once

using namespace System;
using namespace System::Collections::Generic;

ref class DelimLine
{
private:
	array<String^>^ items;

public:
	DelimLine();

	String^ toString();

	property String^ default[int]
	{
		String^ get(int index)
		{
			return items[index];
		}
		void set(int index, String^ value)
		{
			if (index >= items->Length) {
				Array::Resize(items,index+1);
			}
			items[index] = value;
		}
	}

};
