#include "StdAfx.h"
#include "util.h"

using namespace System::Text;


array<Byte>^ stringToBytes(String^ s)
{
	UTF8Encoding encoding;
	return encoding.GetBytes(s);
}

String^ bytesToString(array<Byte>^ bytes)
{
	UTF8Encoding encoding;
	return encoding.GetString(bytes);
}

String^ toString(DateTime^ dt)
{
	return dt->ToString("yyyy/MM/dd HH:mm:ss.fff");
}

String^ toString(DateTimeOffset^ dt)
{
	return toString(dt->DateTime);
}

String^ toHL7String(DateTimeOffset^ dt)
{
	return String::Format("{0:yyyyMMddHHmmss}{1}",dt,dt->ToString("zzz")->Replace(":",""));
}

String^ toString(array<Byte>^ data)
{
	String^ s = "";

	for (int i=0;i<data->Length;i++) {
		if ((i > 0) && ((i % 2) == 0))
			s+= " ";
		s+= data[i].ToString("X2");
	}
	return s;
}

String^ toString(array<UInt16>^ data)
{
	String^ s = "";

	for (int i=0;i<data->Length;i++) {
		if ((i > 0) && ((i % 2) == 0))
			s+= " ";
		s+= data[i].ToString("X4");
	}
	return s;
}

array<UInt16>^ dateTimeToHexString(DateTimeOffset dt)
{
	array<UInt16>^ dateTimeString = gcnew array<UInt16>(4);

	dateTimeString[0] = intToHex(dt.Year / 100) * 0x100 | intToHex(dt.Year % 100);
	dateTimeString[1] = intToHex(dt.Month) * 0x100 | intToHex(dt.Day);
	dateTimeString[2] = intToHex(dt.Hour) * 0x100 | intToHex(dt.Minute);
	dateTimeString[3] = intToHex(dt.Second) * 0x100 | intToHex(dt.Millisecond / 10);

	return dateTimeString;
}

DateTime hexStringToDateTime(array<UInt16>^ dateTimeString,int index)
{
	int year,month,day,hour,min,sec,msec;

	year = hexToInt(dateTimeString[index] / 0x100) * 100 +
			hexToInt(dateTimeString[index] & 0xFF);
	month = hexToInt(dateTimeString[index + 1] / 0x100);
	day = hexToInt(dateTimeString[index + 1] & 0xFF);
	hour = hexToInt(dateTimeString[index + 2] / 0x100);
	min = hexToInt(dateTimeString[index + 2] & 0xFF);
	sec = hexToInt(dateTimeString[index + 3] / 0x100);
	msec = hexToInt(dateTimeString[index + 3] & 0xFF) * 10;

	return DateTime(year,month,day,hour,min,sec,msec);
}

array<Byte>^ manModelStringToBytes(String^ man,String^ model)
{
	array<Byte>^ manmodel;
	int manlen = (int)(Math::Ceiling(man->Length / 2.0) * 2);
	int modellen = (int)(Math::Ceiling(model->Length / 2.0) * 2);
	int len = manlen + 2 + modellen + 2;
	int i = 0;

	manmodel = gcnew array<Byte>(len);

	manmodel[i++] = manlen / 0x100;
	manmodel[i++] = manlen & 0xFF;
	for (int j=0;j<manlen;j++) {
		if (j < man->Length) {
			manmodel[i++] = (Byte)man[j];
		} else {
			manmodel[i++] = '\0';
		}
	}

	manmodel[i++] = modellen / 0x100;
	manmodel[i++] = modellen & 0xFF;
	for (int j=0;j<modellen;j++) {
		if (j < model->Length) {
			manmodel[i++] = (Byte)model[j];
		} else {
			manmodel[i++] = '\0';
		}
	}

	return manmodel;
}

String^ manModelBytesToString(array<UInt16>^ bytes)
{
	String^ manModel = "";
	int len;
	int i = 0;

	while (i < bytes->Length) {
		if (i > 0) {
			manModel += "|";
		}
		len = bytes[i++] / 2;
		for (int j=0;j<len;j++) {
			manModel += (Char)(bytes[i] / 0x100);
			manModel += (Char)(bytes[i] & 0xFF);
			i++;
		}
	}
	return manModel;
}

String^ createPath(String^ basePath,UInt64 eui)
{
	return String::Format("{0}{1:X16}",basePath,eui);
}

array<UInt16>^ serialise(array<UInt16>^ dest,UInt16 val16)
{
	int destLen0 = dest->Length;
	Array::Resize(dest,destLen0 + 1);
	dest[destLen0] = val16;

	return dest;
}

array<UInt16>^ serialise(array<UInt16>^ dest,UInt32 val32)
{
	dest = serialise(dest,(UInt16)(val32 / 0x10000));
	dest = serialise(dest,(UInt16)(val32 & 0xFFFF));

	return dest;
}

array<UInt16>^ serialise(array<UInt16>^ dest,array<UInt16>^ src)
{
	int destLen0 = dest->Length;
	Array::Resize(dest,destLen0 + src->Length);
	Array::Copy(src,0,dest,destLen0,src->Length);

	return dest;
}

Byte intToHex(Byte i)
{
	return (i % 10) + (i / 10 * 0x10);
}

Byte hexToInt(Byte h)
{
	return (h % 0x10) + (h / 0x10 * 10);
}
