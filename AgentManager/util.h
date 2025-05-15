#pragma once

using namespace System;
using namespace System::Windows::Forms;


array<Byte>^ stringToBytes(String^ s);
String^ bytesToString(array<Byte>^ bytes);

String^ toString(DateTime^ dt);
String^ toString(DateTimeOffset^ dt);
String^ toHL7String(DateTimeOffset^ dt);
String^ toString(array<Byte>^ data);
String^ toString(array<UInt16>^ data);
array<UInt16>^ dateTimeToHexString(DateTimeOffset dt);
DateTime hexStringToDateTime(array<UInt16>^ dateTimeString,int index);
array<Byte>^ manModelStringToBytes(String^ man,String^ model);
String^ manModelBytesToString(array<UInt16>^ bytes);

String^ createPath(String^ basePath,UInt64 eui);

array<UInt16>^ serialise(array<UInt16>^ val,UInt16 addVal);
array<UInt16>^ serialise(array<UInt16>^ val,UInt32 addVal);
array<UInt16>^ serialise(array<UInt16>^ dest,array<UInt16>^ src);

Byte intToHex(Byte i);
Byte hexToInt(Byte h);
