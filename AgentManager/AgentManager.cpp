// AgentManager.cpp : main project file.

#include "stdafx.h"
#include "AMController.h"
#include "AMModel.h"
#ifdef MANAGER
#include "AMServer.h"
#endif
#ifdef AGENT
#include "AMClient.h"
#endif

using namespace System;
using namespace System::Windows::Forms;

namespace AgentManager {

	[STAThreadAttribute]
	int main(array<System::String ^> ^args)
	{
		// Enabling Windows XP visual effects before any controls are created
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false); 

		// Create the main window and run it
		AMModel^ model;
#ifdef MANAGER
		model = gcnew AMServer();
#endif
#ifdef AGENT
		model = gcnew AMClient();
#endif
		AMController^ controller = gcnew AMController(model);
		Application::Run(controller->getView()->getMainForm());
		if (controller)
			delete controller;
		if (model)
			delete model;
		return 0;
	}
}
