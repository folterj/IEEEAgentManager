#pragma once

using namespace System;
using namespace System::Windows::Forms;

ref class TreeString
{
public:
	String^ string;

	TreeString();
	TreeString(String^ string0);

	void add(String^ s);
	void addChild(String^ s,String^ child);
	void addChild(String^ s,TreeString^ child);
	array<TreeNode^>^ getTree();
	static array<TreeNode^>^ getTree(String^ string0);
	static array<String^>^ split(String^ string0);
	static String^ getInitstring(String^ string0);
	static String^ getSubstring(String^ string0);
};
