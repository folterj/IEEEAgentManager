#include "StdAfx.h"
#include "TreeString.h"

using namespace System::Collections::Generic;

TreeString::TreeString()
{
	string = "";
}

TreeString::TreeString(String^ string0)
{
	string = string0;
}

void TreeString::add(String^ s)
{
	if (string != "" && s != "") {
		string += ",";
	}
	string += s;
}

void TreeString::addChild(String^ s,String^ child)
{
	add(s);
	if (child != "") {
		string += "{" + child + "}";
	}
}

void TreeString::addChild(String^ s,TreeString^ child)
{
	addChild(s,child->ToString());
}

array<TreeNode^>^ TreeString::getTree()
{
	return getTree(string);
}

array<TreeNode^>^ TreeString::getTree(String^ string0)
{
	array<TreeNode^>^ tree;
	array<String^>^ parts = split(string0);
	String^ initstring;
	String^ substring;
	int n = parts->Length;
	int i = 0;

	tree = gcnew array<TreeNode^>(n);
	for each (String^ s in parts) {
		if (s->Contains("{")) {
			initstring = getInitstring(s);
			substring = getSubstring(s);
			tree[i++] = gcnew TreeNode(initstring,getTree(substring));
		} else {
			tree[i++] = gcnew TreeNode(s);
		}
	}
	return tree;
}

array<String^>^ TreeString::split(String^ string0)
{
	List<String^> parts0;
	array<String^>^ parts;
	int depth = 0;
	int i = 0;
	String^ s = "";

	for each (Char c in string0) {
		if (c == ',' && depth == 0) {
			parts0.Add(s);
			s = "";
		} else {
			s += c;
		}
		if (c == '{')
			depth++;
		if (c == '}')
			depth--;
	}
	if (s != "") {
		parts0.Add(s);
	}
	parts = gcnew array<String^>(parts0.Count);
	for each (String^ part in parts0) {
		parts[i++] = part;
	}
	return parts;
}

String^ TreeString::getInitstring(String^ string0)
{
	int len = string0->IndexOf("{");
	if (len > 0) {
		return string0->Substring(0,len);
	}
	return "";
}

String^ TreeString::getSubstring(String^ string0)
{
	int start = string0->IndexOf("{") + 1;
	int end = string0->LastIndexOf("}");
	int len = end - start;
	if (len > 0) {
		return string0->Substring(start,len);
	}
	return "";
}
