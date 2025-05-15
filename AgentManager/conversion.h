
using namespace System;

String^ apduChoice(int choice);
String^ acseChoice(int choice);
String^ roseChoice(int choice);
String^ actionType(int action);
String^ objClass(UInt16 objclass);
String^ attrId(UInt16 id);
String^ partId(UInt16 id);
String^ typeId(UInt16 id);
String^ typeIdFull(UInt16 id);
String^ unitId(UInt16 id);
String^ unitIdFull(UInt16 id);
String^ devTypeId(UInt16 id);
String^ devTypeIdFull(UInt16 id);
String^ configId(UInt16 id);
String^ assocRes(UInt16 res);
String^ releaseReason(UInt16 id);
String^ abortReason(UInt16 id);
String^ errorId(UInt16 id);
String^ rejectId(UInt16 id);
String^ resultId(UInt16 id);
String^ getFlagText(UInt16 code, UInt16 type);
String^ metricSpecSmallToString(UInt16 val);
String^ metricMdsTimeInfoToString(UInt16 val);
