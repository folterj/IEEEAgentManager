#pragma once

#include "DevSpec.h"
#include "ConnectInfo.h"
#include "ComInterface.h"
#include "PortForm.h"

namespace AgentManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;
	using namespace System::Reflection;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::TabControl^  tabs;
	private: System::Windows::Forms::TabPage^  comTab;
	private: System::Windows::Forms::TabPage^  attrTab;
	private: System::Windows::Forms::TabPage^  obsTab;
	private: System::Windows::Forms::TabPage^  hl7Tab;
	private: System::Windows::Forms::RichTextBox^  hl7Text;
	private: System::Windows::Forms::Splitter^  hl7Splitter;
	private: System::Windows::Forms::ListView^  hl7ListView;
	private: System::Windows::Forms::ColumnHeader^  hl7TimeColumnHeader;
	private: System::Windows::Forms::ColumnHeader^  hl7MsgIdColumnHeader;
	private: System::Windows::Forms::RichTextBox^  comText;
	private: System::Windows::Forms::Splitter^  comSplitter1;
	private: System::Windows::Forms::ListView^  comListView;
	private: System::Windows::Forms::ColumnHeader^  comTimeColumnHeader;
	private: System::Windows::Forms::ColumnHeader^  comDescColumnHeader;
	private: System::Windows::Forms::RichTextBox^  attrText;
	private: System::Windows::Forms::Splitter^  attrSplitter1;
	private: System::Windows::Forms::ListView^  attrListView;
	private: System::Windows::Forms::ColumnHeader^  attrIdColumnHeader;
	private: System::Windows::Forms::RichTextBox^  obsText;
	private: System::Windows::Forms::Splitter^  obsSplitter;
	private: System::Windows::Forms::ListView^  obsListView;
	private: System::Windows::Forms::ColumnHeader^  obsTimeColumnHeader;
	private: System::Windows::Forms::ColumnHeader^  obsObjHandleColumnHeader;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator7;
	private: System::Windows::Forms::ToolStripMenuItem^  selectAllToolStripMenuItem;
	private: System::Windows::Forms::TabPage^  specTab;
	private: System::Windows::Forms::DataGridView^  specDataGrid;
	private: System::Windows::Forms::Button^  connectButton;
	private: System::Windows::Forms::Splitter^  comSplitter2;
	private: System::Windows::Forms::TreeView^  comTreeView;
	private: System::Windows::Forms::ListView^  specListView;
	private: System::Windows::Forms::ColumnHeader^  specEuiColumnHeader;
	private: System::Windows::Forms::ColumnHeader^  specSpecColumnHeader;
	private: System::Windows::Forms::ColumnHeader^  specStateColumnHeader;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  euiColumn;
	private: System::Windows::Forms::DataGridViewComboBoxColumn^  specColumn;
	private: System::Windows::Forms::ListView^  objListView;
	private: System::Windows::Forms::ColumnHeader^  objHandleColumnHeader;
	private: System::Windows::Forms::Splitter^  attrSplitter2;
	private: System::Windows::Forms::ColumnHeader^  objClassColumnHeader;
	private: System::Windows::Forms::Panel^  obsPanel;
	private: System::Windows::Forms::Button^  obsFixedButton;
	private: System::Windows::Forms::ColumnHeader^  obsStateColumnHeader;
	private: System::Windows::Forms::ColumnHeader^  hl7StateColumnHeader;
	private: System::Windows::Forms::ComboBox^  comTypeCombo;
	private: System::Windows::Forms::Button^  obsVarButton;
	private: System::Windows::Forms::Panel^  attrPanel;
	private: System::Windows::Forms::Button^  attrButton;
	private: System::Windows::Forms::ColumnHeader^  reportnoColumnHeader;
	private: System::Windows::Forms::ColumnHeader^  lengthColumnHeader;
	private: System::Windows::Forms::TabPage^  aboutTab;
	private: System::Windows::Forms::GroupBox^  aboutGroup;
	private: System::Windows::Forms::PictureBox^  logoPicture;
	private: System::Windows::Forms::Label^  productLabel;
	private: System::Windows::Forms::Label^  versionLabel;
	private: System::Windows::Forms::Label^  copyLabel;
	private: System::Windows::Forms::Label^  compLabel;
	private: System::Windows::Forms::RichTextBox^  descText;

	private:
		AMControllerInterface^ controller;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->tabs = (gcnew System::Windows::Forms::TabControl());
			this->specTab = (gcnew System::Windows::Forms::TabPage());
			this->comTypeCombo = (gcnew System::Windows::Forms::ComboBox());
			this->connectButton = (gcnew System::Windows::Forms::Button());
			this->specDataGrid = (gcnew System::Windows::Forms::DataGridView());
			this->euiColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->specColumn = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->specListView = (gcnew System::Windows::Forms::ListView());
			this->specEuiColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->specSpecColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->specStateColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->comTab = (gcnew System::Windows::Forms::TabPage());
			this->comText = (gcnew System::Windows::Forms::RichTextBox());
			this->contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->selectAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->comSplitter2 = (gcnew System::Windows::Forms::Splitter());
			this->comTreeView = (gcnew System::Windows::Forms::TreeView());
			this->comSplitter1 = (gcnew System::Windows::Forms::Splitter());
			this->comListView = (gcnew System::Windows::Forms::ListView());
			this->comTimeColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->lengthColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->comDescColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->attrTab = (gcnew System::Windows::Forms::TabPage());
			this->attrButton = (gcnew System::Windows::Forms::Button());
			this->attrPanel = (gcnew System::Windows::Forms::Panel());
			this->attrText = (gcnew System::Windows::Forms::RichTextBox());
			this->attrSplitter2 = (gcnew System::Windows::Forms::Splitter());
			this->attrListView = (gcnew System::Windows::Forms::ListView());
			this->attrIdColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->attrSplitter1 = (gcnew System::Windows::Forms::Splitter());
			this->objListView = (gcnew System::Windows::Forms::ListView());
			this->objHandleColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->objClassColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->obsTab = (gcnew System::Windows::Forms::TabPage());
			this->obsVarButton = (gcnew System::Windows::Forms::Button());
			this->obsFixedButton = (gcnew System::Windows::Forms::Button());
			this->obsPanel = (gcnew System::Windows::Forms::Panel());
			this->obsText = (gcnew System::Windows::Forms::RichTextBox());
			this->obsSplitter = (gcnew System::Windows::Forms::Splitter());
			this->obsListView = (gcnew System::Windows::Forms::ListView());
			this->obsTimeColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->reportnoColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->obsObjHandleColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->obsStateColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->hl7Tab = (gcnew System::Windows::Forms::TabPage());
			this->hl7Text = (gcnew System::Windows::Forms::RichTextBox());
			this->hl7Splitter = (gcnew System::Windows::Forms::Splitter());
			this->hl7ListView = (gcnew System::Windows::Forms::ListView());
			this->hl7TimeColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->hl7MsgIdColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->hl7StateColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->aboutTab = (gcnew System::Windows::Forms::TabPage());
			this->aboutGroup = (gcnew System::Windows::Forms::GroupBox());
			this->descText = (gcnew System::Windows::Forms::RichTextBox());
			this->compLabel = (gcnew System::Windows::Forms::Label());
			this->copyLabel = (gcnew System::Windows::Forms::Label());
			this->versionLabel = (gcnew System::Windows::Forms::Label());
			this->productLabel = (gcnew System::Windows::Forms::Label());
			this->logoPicture = (gcnew System::Windows::Forms::PictureBox());
			this->tabs->SuspendLayout();
			this->specTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->specDataGrid))->BeginInit();
			this->comTab->SuspendLayout();
			this->contextMenuStrip->SuspendLayout();
			this->attrTab->SuspendLayout();
			this->attrPanel->SuspendLayout();
			this->obsTab->SuspendLayout();
			this->obsPanel->SuspendLayout();
			this->hl7Tab->SuspendLayout();
			this->aboutTab->SuspendLayout();
			this->aboutGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->logoPicture))->BeginInit();
			this->SuspendLayout();
			// 
			// tabs
			// 
			this->tabs->Controls->Add(this->specTab);
			this->tabs->Controls->Add(this->comTab);
			this->tabs->Controls->Add(this->attrTab);
			this->tabs->Controls->Add(this->obsTab);
			this->tabs->Controls->Add(this->hl7Tab);
			this->tabs->Controls->Add(this->aboutTab);
			this->tabs->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabs->Location = System::Drawing::Point(0, 0);
			this->tabs->Name = L"tabs";
			this->tabs->SelectedIndex = 0;
			this->tabs->Size = System::Drawing::Size(484, 462);
			this->tabs->TabIndex = 0;
			// 
			// specTab
			// 
			this->specTab->Controls->Add(this->comTypeCombo);
			this->specTab->Controls->Add(this->connectButton);
			this->specTab->Controls->Add(this->specDataGrid);
			this->specTab->Controls->Add(this->specListView);
			this->specTab->Location = System::Drawing::Point(4, 22);
			this->specTab->Name = L"specTab";
			this->specTab->Padding = System::Windows::Forms::Padding(3);
			this->specTab->Size = System::Drawing::Size(476, 436);
			this->specTab->TabIndex = 4;
			this->specTab->Text = L"Spec";
			this->specTab->UseVisualStyleBackColor = true;
			// 
			// comTypeCombo
			// 
			this->comTypeCombo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->comTypeCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comTypeCombo->FormattingEnabled = true;
			this->comTypeCombo->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Select com type:", L"Message Queuing", L"Serial Port", 
				L"TCP Port", L"Internet Protocol"});
			this->comTypeCombo->Location = System::Drawing::Point(9, 402);
			this->comTypeCombo->Name = L"comTypeCombo";
			this->comTypeCombo->Size = System::Drawing::Size(121, 21);
			this->comTypeCombo->TabIndex = 8;
			this->comTypeCombo->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comTypeCombo_SelectedIndexChanged);
			// 
			// connectButton
			// 
			this->connectButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->connectButton->Enabled = false;
			this->connectButton->Location = System::Drawing::Point(390, 402);
			this->connectButton->Name = L"connectButton";
			this->connectButton->Size = System::Drawing::Size(75, 23);
			this->connectButton->TabIndex = 1;
			this->connectButton->Text = L"Connect";
			this->connectButton->UseVisualStyleBackColor = true;
			this->connectButton->Click += gcnew System::EventHandler(this, &MainForm::connectButton_Click);
			// 
			// specDataGrid
			// 
			this->specDataGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->specDataGrid->BackgroundColor = System::Drawing::Color::White;
			this->specDataGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->specDataGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->euiColumn, 
				this->specColumn});
			this->specDataGrid->Location = System::Drawing::Point(3, 3);
			this->specDataGrid->Name = L"specDataGrid";
			this->specDataGrid->Size = System::Drawing::Size(470, 390);
			this->specDataGrid->TabIndex = 0;
			this->specDataGrid->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &MainForm::specDataGrid_RowsAdded);
			// 
			// euiColumn
			// 
			this->euiColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->euiColumn->FillWeight = 70;
			this->euiColumn->HeaderText = L"EUI";
			this->euiColumn->Name = L"euiColumn";
			// 
			// specColumn
			// 
			this->specColumn->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->specColumn->DisplayStyle = System::Windows::Forms::DataGridViewComboBoxDisplayStyle::ComboBox;
			this->specColumn->FillWeight = 30;
			this->specColumn->HeaderText = L"Specialisation";
			this->specColumn->Name = L"specColumn";
			this->specColumn->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->specColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			// 
			// specListView
			// 
			this->specListView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->specListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->specEuiColumnHeader, 
				this->specSpecColumnHeader, this->specStateColumnHeader});
			this->specListView->FullRowSelect = true;
			this->specListView->Location = System::Drawing::Point(3, 3);
			this->specListView->MultiSelect = false;
			this->specListView->Name = L"specListView";
			this->specListView->Size = System::Drawing::Size(470, 390);
			this->specListView->TabIndex = 7;
			this->specListView->UseCompatibleStateImageBehavior = false;
			this->specListView->View = System::Windows::Forms::View::Details;
			this->specListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::specListView_SelectedIndexChanged);
			// 
			// specEuiColumnHeader
			// 
			this->specEuiColumnHeader->Text = L"EUI";
			this->specEuiColumnHeader->Width = 150;
			// 
			// specSpecColumnHeader
			// 
			this->specSpecColumnHeader->Text = L"Specialisation";
			this->specSpecColumnHeader->Width = 100;
			// 
			// specStateColumnHeader
			// 
			this->specStateColumnHeader->Text = L"State";
			this->specStateColumnHeader->Width = 100;
			// 
			// comTab
			// 
			this->comTab->Controls->Add(this->comText);
			this->comTab->Controls->Add(this->comSplitter2);
			this->comTab->Controls->Add(this->comTreeView);
			this->comTab->Controls->Add(this->comSplitter1);
			this->comTab->Controls->Add(this->comListView);
			this->comTab->Location = System::Drawing::Point(4, 22);
			this->comTab->Name = L"comTab";
			this->comTab->Padding = System::Windows::Forms::Padding(3);
			this->comTab->Size = System::Drawing::Size(476, 436);
			this->comTab->TabIndex = 0;
			this->comTab->Text = L"Com";
			this->comTab->UseVisualStyleBackColor = true;
			this->comTab->SizeChanged += gcnew System::EventHandler(this, &MainForm::comTab_SizeChanged);
			// 
			// comText
			// 
			this->comText->AutoWordSelection = true;
			this->comText->BackColor = System::Drawing::Color::White;
			this->comText->ContextMenuStrip = this->contextMenuStrip;
			this->comText->Dock = System::Windows::Forms::DockStyle::Fill;
			this->comText->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comText->HideSelection = false;
			this->comText->Location = System::Drawing::Point(3, 349);
			this->comText->Name = L"comText";
			this->comText->ReadOnly = true;
			this->comText->Size = System::Drawing::Size(470, 84);
			this->comText->TabIndex = 8;
			this->comText->Text = L"";
			// 
			// contextMenuStrip
			// 
			this->contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->copyToolStripMenuItem, 
				this->toolStripSeparator7, this->selectAllToolStripMenuItem});
			this->contextMenuStrip->Name = L"contextMenuStrip";
			this->contextMenuStrip->Size = System::Drawing::Size(123, 54);
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"copyToolStripMenuItem.Image")));
			this->copyToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->copyToolStripMenuItem->Text = L"&Copy";
			this->copyToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::copyToolStripMenuItem_Click);
			// 
			// toolStripSeparator7
			// 
			this->toolStripSeparator7->Name = L"toolStripSeparator7";
			this->toolStripSeparator7->Size = System::Drawing::Size(119, 6);
			// 
			// selectAllToolStripMenuItem
			// 
			this->selectAllToolStripMenuItem->Name = L"selectAllToolStripMenuItem";
			this->selectAllToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->selectAllToolStripMenuItem->Text = L"Select &All";
			this->selectAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::selectAllToolStripMenuItem_Click);
			// 
			// comSplitter2
			// 
			this->comSplitter2->BackColor = System::Drawing::Color::White;
			this->comSplitter2->Dock = System::Windows::Forms::DockStyle::Top;
			this->comSplitter2->Location = System::Drawing::Point(3, 341);
			this->comSplitter2->MinExtra = 50;
			this->comSplitter2->MinSize = 50;
			this->comSplitter2->Name = L"comSplitter2";
			this->comSplitter2->Size = System::Drawing::Size(470, 8);
			this->comSplitter2->TabIndex = 10;
			this->comSplitter2->TabStop = false;
			// 
			// comTreeView
			// 
			this->comTreeView->Dock = System::Windows::Forms::DockStyle::Top;
			this->comTreeView->Location = System::Drawing::Point(3, 176);
			this->comTreeView->Name = L"comTreeView";
			this->comTreeView->Size = System::Drawing::Size(470, 165);
			this->comTreeView->TabIndex = 9;
			// 
			// comSplitter1
			// 
			this->comSplitter1->BackColor = System::Drawing::Color::White;
			this->comSplitter1->Dock = System::Windows::Forms::DockStyle::Top;
			this->comSplitter1->Location = System::Drawing::Point(3, 168);
			this->comSplitter1->MinExtra = 50;
			this->comSplitter1->MinSize = 50;
			this->comSplitter1->Name = L"comSplitter1";
			this->comSplitter1->Size = System::Drawing::Size(470, 8);
			this->comSplitter1->TabIndex = 7;
			this->comSplitter1->TabStop = false;
			// 
			// comListView
			// 
			this->comListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->comTimeColumnHeader, 
				this->lengthColumnHeader, this->comDescColumnHeader});
			this->comListView->Dock = System::Windows::Forms::DockStyle::Top;
			this->comListView->FullRowSelect = true;
			this->comListView->Location = System::Drawing::Point(3, 3);
			this->comListView->MultiSelect = false;
			this->comListView->Name = L"comListView";
			this->comListView->Size = System::Drawing::Size(470, 165);
			this->comListView->TabIndex = 6;
			this->comListView->UseCompatibleStateImageBehavior = false;
			this->comListView->View = System::Windows::Forms::View::Details;
			this->comListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comListView_SelectedIndexChanged);
			// 
			// comTimeColumnHeader
			// 
			this->comTimeColumnHeader->Text = L"Time";
			this->comTimeColumnHeader->Width = 150;
			// 
			// lengthColumnHeader
			// 
			this->lengthColumnHeader->Text = L"Length";
			this->lengthColumnHeader->Width = 45;
			// 
			// comDescColumnHeader
			// 
			this->comDescColumnHeader->Text = L"Description";
			this->comDescColumnHeader->Width = 1000;
			// 
			// attrTab
			// 
			this->attrTab->Controls->Add(this->attrButton);
			this->attrTab->Controls->Add(this->attrPanel);
			this->attrTab->Location = System::Drawing::Point(4, 22);
			this->attrTab->Name = L"attrTab";
			this->attrTab->Padding = System::Windows::Forms::Padding(3);
			this->attrTab->Size = System::Drawing::Size(476, 436);
			this->attrTab->TabIndex = 1;
			this->attrTab->Text = L"Attr";
			this->attrTab->UseVisualStyleBackColor = true;
			this->attrTab->SizeChanged += gcnew System::EventHandler(this, &MainForm::attrTab_SizeChanged);
			// 
			// attrButton
			// 
			this->attrButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->attrButton->Enabled = false;
			this->attrButton->Location = System::Drawing::Point(368, 405);
			this->attrButton->Name = L"attrButton";
			this->attrButton->Size = System::Drawing::Size(100, 23);
			this->attrButton->TabIndex = 12;
			this->attrButton->Text = L"Update Report";
			this->attrButton->UseVisualStyleBackColor = true;
			this->attrButton->Click += gcnew System::EventHandler(this, &MainForm::attrButton_Click);
			// 
			// attrPanel
			// 
			this->attrPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->attrPanel->Controls->Add(this->attrText);
			this->attrPanel->Controls->Add(this->attrSplitter2);
			this->attrPanel->Controls->Add(this->attrListView);
			this->attrPanel->Controls->Add(this->attrSplitter1);
			this->attrPanel->Controls->Add(this->objListView);
			this->attrPanel->Location = System::Drawing::Point(3, 3);
			this->attrPanel->Name = L"attrPanel";
			this->attrPanel->Size = System::Drawing::Size(470, 396);
			this->attrPanel->TabIndex = 11;
			// 
			// attrText
			// 
			this->attrText->AutoWordSelection = true;
			this->attrText->BackColor = System::Drawing::Color::White;
			this->attrText->ContextMenuStrip = this->contextMenuStrip;
			this->attrText->Dock = System::Windows::Forms::DockStyle::Fill;
			this->attrText->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->attrText->HideSelection = false;
			this->attrText->Location = System::Drawing::Point(0, 346);
			this->attrText->Name = L"attrText";
			this->attrText->ReadOnly = true;
			this->attrText->Size = System::Drawing::Size(470, 50);
			this->attrText->TabIndex = 8;
			this->attrText->Text = L"";
			// 
			// attrSplitter2
			// 
			this->attrSplitter2->BackColor = System::Drawing::Color::White;
			this->attrSplitter2->Dock = System::Windows::Forms::DockStyle::Top;
			this->attrSplitter2->Location = System::Drawing::Point(0, 338);
			this->attrSplitter2->MinExtra = 100;
			this->attrSplitter2->MinSize = 100;
			this->attrSplitter2->Name = L"attrSplitter2";
			this->attrSplitter2->Size = System::Drawing::Size(470, 8);
			this->attrSplitter2->TabIndex = 10;
			this->attrSplitter2->TabStop = false;
			// 
			// attrListView
			// 
			this->attrListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->attrIdColumnHeader});
			this->attrListView->Dock = System::Windows::Forms::DockStyle::Top;
			this->attrListView->FullRowSelect = true;
			this->attrListView->Location = System::Drawing::Point(0, 173);
			this->attrListView->MultiSelect = false;
			this->attrListView->Name = L"attrListView";
			this->attrListView->Size = System::Drawing::Size(470, 165);
			this->attrListView->TabIndex = 6;
			this->attrListView->UseCompatibleStateImageBehavior = false;
			this->attrListView->View = System::Windows::Forms::View::Details;
			this->attrListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::attrListView_SelectedIndexChanged);
			// 
			// attrIdColumnHeader
			// 
			this->attrIdColumnHeader->Text = L"Attribute Id";
			this->attrIdColumnHeader->Width = 350;
			// 
			// attrSplitter1
			// 
			this->attrSplitter1->BackColor = System::Drawing::Color::White;
			this->attrSplitter1->Dock = System::Windows::Forms::DockStyle::Top;
			this->attrSplitter1->Location = System::Drawing::Point(0, 165);
			this->attrSplitter1->MinExtra = 100;
			this->attrSplitter1->MinSize = 100;
			this->attrSplitter1->Name = L"attrSplitter1";
			this->attrSplitter1->Size = System::Drawing::Size(470, 8);
			this->attrSplitter1->TabIndex = 7;
			this->attrSplitter1->TabStop = false;
			// 
			// objListView
			// 
			this->objListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->objHandleColumnHeader, 
				this->objClassColumnHeader});
			this->objListView->Dock = System::Windows::Forms::DockStyle::Top;
			this->objListView->FullRowSelect = true;
			this->objListView->Location = System::Drawing::Point(0, 0);
			this->objListView->MultiSelect = false;
			this->objListView->Name = L"objListView";
			this->objListView->Size = System::Drawing::Size(470, 165);
			this->objListView->TabIndex = 9;
			this->objListView->UseCompatibleStateImageBehavior = false;
			this->objListView->View = System::Windows::Forms::View::Details;
			this->objListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::objListView_SelectedIndexChanged);
			// 
			// objHandleColumnHeader
			// 
			this->objHandleColumnHeader->Text = L"Object Handle";
			this->objHandleColumnHeader->Width = 80;
			// 
			// objClassColumnHeader
			// 
			this->objClassColumnHeader->Text = L"Class";
			this->objClassColumnHeader->Width = 270;
			// 
			// obsTab
			// 
			this->obsTab->Controls->Add(this->obsVarButton);
			this->obsTab->Controls->Add(this->obsFixedButton);
			this->obsTab->Controls->Add(this->obsPanel);
			this->obsTab->Location = System::Drawing::Point(4, 22);
			this->obsTab->Name = L"obsTab";
			this->obsTab->Padding = System::Windows::Forms::Padding(3);
			this->obsTab->Size = System::Drawing::Size(476, 436);
			this->obsTab->TabIndex = 2;
			this->obsTab->Text = L"Obs";
			this->obsTab->UseVisualStyleBackColor = true;
			this->obsTab->SizeChanged += gcnew System::EventHandler(this, &MainForm::obsTab_SizeChanged);
			// 
			// obsVarButton
			// 
			this->obsVarButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->obsVarButton->Enabled = false;
			this->obsVarButton->Location = System::Drawing::Point(370, 405);
			this->obsVarButton->Name = L"obsVarButton";
			this->obsVarButton->Size = System::Drawing::Size(100, 23);
			this->obsVarButton->TabIndex = 11;
			this->obsVarButton->Text = L"Generate (Var)";
			this->obsVarButton->UseVisualStyleBackColor = true;
			this->obsVarButton->Click += gcnew System::EventHandler(this, &MainForm::obsVarButton_Click);
			// 
			// obsFixedButton
			// 
			this->obsFixedButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->obsFixedButton->Enabled = false;
			this->obsFixedButton->Location = System::Drawing::Point(264, 405);
			this->obsFixedButton->Name = L"obsFixedButton";
			this->obsFixedButton->Size = System::Drawing::Size(100, 23);
			this->obsFixedButton->TabIndex = 10;
			this->obsFixedButton->Text = L"Generate (Fixed)";
			this->obsFixedButton->UseVisualStyleBackColor = true;
			this->obsFixedButton->Click += gcnew System::EventHandler(this, &MainForm::obsFixedButton_Click);
			// 
			// obsPanel
			// 
			this->obsPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->obsPanel->Controls->Add(this->obsText);
			this->obsPanel->Controls->Add(this->obsSplitter);
			this->obsPanel->Controls->Add(this->obsListView);
			this->obsPanel->Location = System::Drawing::Point(3, 3);
			this->obsPanel->Name = L"obsPanel";
			this->obsPanel->Size = System::Drawing::Size(470, 396);
			this->obsPanel->TabIndex = 9;
			// 
			// obsText
			// 
			this->obsText->AutoWordSelection = true;
			this->obsText->BackColor = System::Drawing::Color::White;
			this->obsText->ContextMenuStrip = this->contextMenuStrip;
			this->obsText->Dock = System::Windows::Forms::DockStyle::Fill;
			this->obsText->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->obsText->HideSelection = false;
			this->obsText->Location = System::Drawing::Point(0, 202);
			this->obsText->Name = L"obsText";
			this->obsText->ReadOnly = true;
			this->obsText->Size = System::Drawing::Size(470, 194);
			this->obsText->TabIndex = 8;
			this->obsText->Text = L"";
			// 
			// obsSplitter
			// 
			this->obsSplitter->BackColor = System::Drawing::Color::White;
			this->obsSplitter->Dock = System::Windows::Forms::DockStyle::Top;
			this->obsSplitter->Location = System::Drawing::Point(0, 194);
			this->obsSplitter->MinExtra = 100;
			this->obsSplitter->MinSize = 100;
			this->obsSplitter->Name = L"obsSplitter";
			this->obsSplitter->Size = System::Drawing::Size(470, 8);
			this->obsSplitter->TabIndex = 7;
			this->obsSplitter->TabStop = false;
			// 
			// obsListView
			// 
			this->obsListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->obsTimeColumnHeader, 
				this->reportnoColumnHeader, this->obsObjHandleColumnHeader, this->obsStateColumnHeader});
			this->obsListView->Dock = System::Windows::Forms::DockStyle::Top;
			this->obsListView->FullRowSelect = true;
			this->obsListView->Location = System::Drawing::Point(0, 0);
			this->obsListView->MultiSelect = false;
			this->obsListView->Name = L"obsListView";
			this->obsListView->Size = System::Drawing::Size(470, 194);
			this->obsListView->TabIndex = 6;
			this->obsListView->UseCompatibleStateImageBehavior = false;
			this->obsListView->View = System::Windows::Forms::View::Details;
			this->obsListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::obsListView_SelectedIndexChanged);
			// 
			// obsTimeColumnHeader
			// 
			this->obsTimeColumnHeader->Text = L"Time";
			this->obsTimeColumnHeader->Width = 150;
			// 
			// reportnoColumnHeader
			// 
			this->reportnoColumnHeader->Text = L"Report #";
			// 
			// obsObjHandleColumnHeader
			// 
			this->obsObjHandleColumnHeader->Text = L"Object";
			// 
			// obsStateColumnHeader
			// 
			this->obsStateColumnHeader->Text = L"State";
			this->obsStateColumnHeader->Width = 180;
			// 
			// hl7Tab
			// 
			this->hl7Tab->Controls->Add(this->hl7Text);
			this->hl7Tab->Controls->Add(this->hl7Splitter);
			this->hl7Tab->Controls->Add(this->hl7ListView);
			this->hl7Tab->Location = System::Drawing::Point(4, 22);
			this->hl7Tab->Name = L"hl7Tab";
			this->hl7Tab->Padding = System::Windows::Forms::Padding(3);
			this->hl7Tab->Size = System::Drawing::Size(476, 436);
			this->hl7Tab->TabIndex = 3;
			this->hl7Tab->Text = L"HL7";
			this->hl7Tab->UseVisualStyleBackColor = true;
			this->hl7Tab->SizeChanged += gcnew System::EventHandler(this, &MainForm::hl7Tab_SizeChanged);
			// 
			// hl7Text
			// 
			this->hl7Text->AutoWordSelection = true;
			this->hl7Text->BackColor = System::Drawing::Color::White;
			this->hl7Text->ContextMenuStrip = this->contextMenuStrip;
			this->hl7Text->Dock = System::Windows::Forms::DockStyle::Fill;
			this->hl7Text->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->hl7Text->HideSelection = false;
			this->hl7Text->Location = System::Drawing::Point(3, 222);
			this->hl7Text->Name = L"hl7Text";
			this->hl7Text->ReadOnly = true;
			this->hl7Text->Size = System::Drawing::Size(470, 211);
			this->hl7Text->TabIndex = 5;
			this->hl7Text->Text = L"";
			// 
			// hl7Splitter
			// 
			this->hl7Splitter->BackColor = System::Drawing::Color::White;
			this->hl7Splitter->Dock = System::Windows::Forms::DockStyle::Top;
			this->hl7Splitter->Location = System::Drawing::Point(3, 214);
			this->hl7Splitter->MinExtra = 100;
			this->hl7Splitter->MinSize = 100;
			this->hl7Splitter->Name = L"hl7Splitter";
			this->hl7Splitter->Size = System::Drawing::Size(470, 8);
			this->hl7Splitter->TabIndex = 4;
			this->hl7Splitter->TabStop = false;
			// 
			// hl7ListView
			// 
			this->hl7ListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->hl7TimeColumnHeader, 
				this->hl7MsgIdColumnHeader, this->hl7StateColumnHeader});
			this->hl7ListView->Dock = System::Windows::Forms::DockStyle::Top;
			this->hl7ListView->FullRowSelect = true;
			this->hl7ListView->Location = System::Drawing::Point(3, 3);
			this->hl7ListView->MultiSelect = false;
			this->hl7ListView->Name = L"hl7ListView";
			this->hl7ListView->Size = System::Drawing::Size(470, 211);
			this->hl7ListView->TabIndex = 3;
			this->hl7ListView->UseCompatibleStateImageBehavior = false;
			this->hl7ListView->View = System::Windows::Forms::View::Details;
			this->hl7ListView->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::hl7ListView_SelectedIndexChanged);
			// 
			// hl7TimeColumnHeader
			// 
			this->hl7TimeColumnHeader->Text = L"Time";
			this->hl7TimeColumnHeader->Width = 150;
			// 
			// hl7MsgIdColumnHeader
			// 
			this->hl7MsgIdColumnHeader->Text = L"MsgId";
			this->hl7MsgIdColumnHeader->Width = 50;
			// 
			// hl7StateColumnHeader
			// 
			this->hl7StateColumnHeader->Text = L"State";
			this->hl7StateColumnHeader->Width = 200;
			// 
			// aboutTab
			// 
			this->aboutTab->Controls->Add(this->aboutGroup);
			this->aboutTab->Location = System::Drawing::Point(4, 22);
			this->aboutTab->Name = L"aboutTab";
			this->aboutTab->Padding = System::Windows::Forms::Padding(3);
			this->aboutTab->Size = System::Drawing::Size(476, 436);
			this->aboutTab->TabIndex = 5;
			this->aboutTab->Text = L"About";
			this->aboutTab->UseVisualStyleBackColor = true;
			// 
			// aboutGroup
			// 
			this->aboutGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->aboutGroup->Controls->Add(this->descText);
			this->aboutGroup->Controls->Add(this->compLabel);
			this->aboutGroup->Controls->Add(this->copyLabel);
			this->aboutGroup->Controls->Add(this->versionLabel);
			this->aboutGroup->Controls->Add(this->productLabel);
			this->aboutGroup->Controls->Add(this->logoPicture);
			this->aboutGroup->Location = System::Drawing::Point(8, 6);
			this->aboutGroup->Name = L"aboutGroup";
			this->aboutGroup->Size = System::Drawing::Size(460, 424);
			this->aboutGroup->TabIndex = 0;
			this->aboutGroup->TabStop = false;
			// 
			// descText
			// 
			this->descText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->descText->Location = System::Drawing::Point(6, 217);
			this->descText->Name = L"descText";
			this->descText->ReadOnly = true;
			this->descText->Size = System::Drawing::Size(448, 201);
			this->descText->TabIndex = 5;
			this->descText->Text = L"";
			this->descText->LinkClicked += gcnew System::Windows::Forms::LinkClickedEventHandler(this, &MainForm::descText_LinkClicked);
			// 
			// compLabel
			// 
			this->compLabel->AutoSize = true;
			this->compLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->compLabel->Location = System::Drawing::Point(204, 191);
			this->compLabel->Name = L"compLabel";
			this->compLabel->Size = System::Drawing::Size(76, 20);
			this->compLabel->TabIndex = 4;
			this->compLabel->Text = L"Company";
			// 
			// copyLabel
			// 
			this->copyLabel->AutoSize = true;
			this->copyLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->copyLabel->Location = System::Drawing::Point(204, 134);
			this->copyLabel->Name = L"copyLabel";
			this->copyLabel->Size = System::Drawing::Size(76, 20);
			this->copyLabel->TabIndex = 3;
			this->copyLabel->Text = L"Copyright";
			// 
			// versionLabel
			// 
			this->versionLabel->AutoSize = true;
			this->versionLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->versionLabel->Location = System::Drawing::Point(204, 74);
			this->versionLabel->Name = L"versionLabel";
			this->versionLabel->Size = System::Drawing::Size(63, 20);
			this->versionLabel->TabIndex = 2;
			this->versionLabel->Text = L"Version";
			// 
			// productLabel
			// 
			this->productLabel->AutoSize = true;
			this->productLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->productLabel->Location = System::Drawing::Point(204, 19);
			this->productLabel->Name = L"productLabel";
			this->productLabel->Size = System::Drawing::Size(64, 20);
			this->productLabel->TabIndex = 1;
			this->productLabel->Text = L"Product";
			// 
			// logoPicture
			// 
			this->logoPicture->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"logoPicture.Image")));
			this->logoPicture->Location = System::Drawing::Point(6, 19);
			this->logoPicture->Name = L"logoPicture";
			this->logoPicture->Size = System::Drawing::Size(192, 192);
			this->logoPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->logoPicture->TabIndex = 0;
			this->logoPicture->TabStop = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 462);
			this->Controls->Add(this->tabs);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"AgentManager";
			this->tabs->ResumeLayout(false);
			this->specTab->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->specDataGrid))->EndInit();
			this->comTab->ResumeLayout(false);
			this->contextMenuStrip->ResumeLayout(false);
			this->attrTab->ResumeLayout(false);
			this->attrPanel->ResumeLayout(false);
			this->obsTab->ResumeLayout(false);
			this->obsPanel->ResumeLayout(false);
			this->hl7Tab->ResumeLayout(false);
			this->aboutTab->ResumeLayout(false);
			this->aboutGroup->ResumeLayout(false);
			this->aboutGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->logoPicture))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	public:
		MainForm(AMControllerInterface^ controller0)
		{
			controller = controller0;
			InitializeComponent();
			comTypeCombo->SelectedIndex = (int)ComType::None;
#ifdef MANAGER
			specListView->Visible = true;
			specDataGrid->Visible = false;
			connectButton->Text = "Disconnect";
			obsFixedButton->Visible = false;
			obsVarButton->Visible = false;
			attrButton->Visible = false;
#endif
#ifdef AGENT
			tabs->TabPages->Remove(hl7Tab);
			specColumn->DataSource = Enum::GetNames(SpecType::typeid);
			specListView->Visible = false;
			specDataGrid->Visible = true;
			connectButton->Text = "Connect";
			obsFixedButton->Visible = true;
			obsVarButton->Visible = true;
			attrButton->Visible = true;
#endif
			Assembly^ assembly = Assembly::GetExecutingAssembly();
			AssemblyName^ assemblyName = assembly->GetName();
			String^ version = assemblyName->Version->ToString();
			String^ product = ((AssemblyProductAttribute^)assembly->GetCustomAttributes(AssemblyProductAttribute::typeid,false)[0])->Product;
			String^ copyright = ((AssemblyCopyrightAttribute^)assembly->GetCustomAttributes(AssemblyCopyrightAttribute::typeid,false)[0])->Copyright;
			String^ company = ((AssemblyCompanyAttribute^)assembly->GetCustomAttributes(AssemblyCompanyAttribute::typeid,false)[0])->Company;
			String^ desc = ((AssemblyDescriptionAttribute^)assembly->GetCustomAttributes(AssemblyDescriptionAttribute::typeid,false)[0])->Description;

			productLabel->Text = product;
			versionLabel->Text = "Version " + version;
			compLabel->Text = company;
			copyLabel->Text = copyright;
			descText->Text = desc;
		}

		void setTitle(String^ title)
		{
			this->Text = title;
		}

		void setComInitialised(bool set)
		{
			comTypeCombo->Enabled = !set;
			connectButton->Enabled = set;
		}

		delegate void UpdateSpecDelegate(UInt64 eui,String^ spec,String^ state,ComCommand command);

		void updateSpec(UInt64 eui,String^ spec,String^ state,ComCommand command)
		{
			if (specListView->InvokeRequired) {
				UpdateSpecDelegate^ delegate = gcnew UpdateSpecDelegate(this,&MainForm::updateSpec);
				this->BeginInvoke(delegate,gcnew array<Object^>{eui,spec,state,command});
			} else {
				ListViewItem^ item;

				String^ euis = String::Format("{0:X16}",eui);

				for each (ListViewItem^ item0 in specListView->Items) {
					if (item0->SubItems[0]->Text == euis) {
						// found existing item in listview
						item = item0;
					}
				}
				if (command == ComCommand::Remove) {
					// remove item
					if (item) {
						// item exists; remove
						item->Remove();
					}
				} else {
					// add or update item
					if (!item) {
						// item not found in list; create new item
						item = gcnew ListViewItem(gcnew array<String^>{euis,spec,state});
						specListView->Items->Add(item);
					} else {
						// update item
						item->SubItems[0]->Text = euis;
						item->SubItems[1]->Text = spec;
						item->SubItems[2]->Text = state;
					}
					if (command == ComCommand::Connect) {
						item->ForeColor = SystemColors::ControlText;
					} else if (command == ComCommand::Disconnect) {
						item->ForeColor = Color::Gray;					
					}
				}
			}
		}

		void showLastListViewItem(ListView^ listView)
		{
			listView->EnsureVisible(listView->Items->Count-1);
		}

		delegate void ClearComListDelegate();

		void clearComList()
		{
			if (comListView->InvokeRequired) {
				this->BeginInvoke(gcnew ClearComListDelegate(this,&MainForm::clearComList));
			} else {
				comListView->Items->Clear();
			}
		}

		delegate void AddComDelegate(String^ timestamp,String^ desc,int length,bool rec,bool ok);

		void addCom(String^ timestamp,String^ desc,int length,bool rec,bool ok)
		{
			if (comListView->InvokeRequired) {
				this->BeginInvoke(gcnew AddComDelegate(this,&MainForm::addCom),gcnew array<Object^>{timestamp,desc,length,rec,ok});
			} else {
				if (rec) {
					desc = "> " + desc;
				} else {
					desc = "< " + desc;
				}
				ListViewItem^ item = gcnew ListViewItem(gcnew array<String^>{timestamp,length.ToString(),desc});
				if (!ok) {
					item->ForeColor = Color::Red;
				}
				comListView->Items->Add(item);
				showLastListViewItem(comListView);
			}
		}

		void dispComMsg(String^ data,array<TreeNode^>^ tree)
		{
			clearComMsg();

			comText->Text = data;
			comTreeView->Nodes->AddRange(tree);
		}

		void clearComMsg()
		{
			comText->Text = "";
			comTreeView->Nodes->Clear();
		}

		delegate void ClearObjListDelegate();

		void clearObjList()
		{
			if (objListView->InvokeRequired) {
				this->BeginInvoke(gcnew ClearObjListDelegate(this,&MainForm::clearObjList));
			} else {
				objListView->Items->Clear();
			}
		}

		delegate void AddObjDelegate(String^ objHandle,String^ objClass);

		void addObj(String^ objHandle,String^ objClass)
		{
			if (objListView->InvokeRequired) {
				this->BeginInvoke(gcnew AddObjDelegate(this,&MainForm::addObj),gcnew array<Object^>{objHandle,objClass});
			} else {
				objListView->Items->Add(gcnew ListViewItem(gcnew array<String^>{objHandle,objClass}));
			}
		}

		delegate void ClearAttrListDelegate();

		void clearAttrList()
		{
			if (attrListView->InvokeRequired) {
				this->BeginInvoke(gcnew ClearAttrListDelegate(this,&MainForm::clearAttrList));
			} else {
				attrListView->Items->Clear();
			}
		}

		delegate void AddAttrDelegate(String^ id);

		void addAttr(String^ id)
		{
			if (attrListView->InvokeRequired) {
				this->BeginInvoke(gcnew AddAttrDelegate(this,&MainForm::addAttr),gcnew array<Object^>{id});
			} else {
				attrListView->Items->Add(gcnew ListViewItem(gcnew array<String^>{id}));
			}
		}

		delegate void ClearObsListDelegate();

		void clearObsList()
		{
			if (obsListView->InvokeRequired) {
				this->BeginInvoke(gcnew ClearObsListDelegate(this,&MainForm::clearObsList));
			} else {
				obsListView->Items->Clear();
			}
		}

		delegate void AddObsDelegate(String^ timestamp,String^ reportNo,String^ objHandle,String^ state,bool active);

		void addObs(String^ timestamp,String^ reportNo,String^ objHandle,String^ state,bool active)
		{
			if (obsListView->InvokeRequired) {
				this->BeginInvoke(gcnew AddObsDelegate(this,&MainForm::addObs),gcnew array<Object^>{timestamp,reportNo,objHandle,state,active});
			} else {
				ListViewItem^ item = gcnew ListViewItem(gcnew array<String^>{timestamp,reportNo,objHandle,state});
				if (!active) {
					item->ForeColor = Color::Gray;
				}
				obsListView->Items->Add(item);
				showLastListViewItem(obsListView);
			}
		}

		delegate void ClearHL7ListDelegate();

		void clearHL7List()
		{
			if (hl7ListView->InvokeRequired) {
				this->BeginInvoke(gcnew ClearHL7ListDelegate(this,&MainForm::clearHL7List));
			} else {
				hl7ListView->Items->Clear();
			}
		}

		delegate void AddHL7Delegate(String^ timestamp,String^ msgId,String^ state,bool active);

		void addHL7(String^ timestamp,String^ msgId,String^ state,bool active)
		{
			if (hl7ListView->InvokeRequired) {
				this->BeginInvoke(gcnew AddHL7Delegate(this,&MainForm::addHL7),gcnew array<Object^>{timestamp,msgId,state,active});
			} else {
				ListViewItem^ item = gcnew ListViewItem(gcnew array<String^>{timestamp,msgId,state});
				if (!active) {
					item->ForeColor = Color::Gray;
				}
				hl7ListView->Items->Add(item);
				showLastListViewItem(hl7ListView);
			}
		}

		delegate void DispAttrTextDelegate(String^ text);

		void dispAttrText(String^ text)
		{
			if (attrText->InvokeRequired) {
				this->BeginInvoke(gcnew DispAttrTextDelegate(this,&MainForm::dispAttrText),gcnew array<Object^>{text});
			} else {
				attrText->Text = text;
			}
		}

		delegate void DispObsTextDelegate(String^ text);

		void dispObsText(String^ text)
		{
			if (obsText->InvokeRequired) {
				this->BeginInvoke(gcnew DispObsTextDelegate(this,&MainForm::dispObsText),gcnew array<Object^>{text});
			} else {
				obsText->Text = text;
			}
		}

		delegate void DispHL7TextDelegate(String^ text);

		void dispHL7Text(String^ text)
		{
			if (hl7Text->InvokeRequired) {
				this->BeginInvoke(gcnew DispHL7TextDelegate(this,&MainForm::dispHL7Text),gcnew array<Object^>{text});
			} else {
				hl7Text->Text = text;
			}
		}

	protected:
		~MainForm()
		{
			if (components) {
				delete components;
			}
		}

	private:
		System::Void comTypeCombo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			if (comTypeCombo->SelectedIndex > 0) {
				if (!controller->comInit((ComType)comTypeCombo->SelectedIndex)) {
					comTypeCombo->SelectedIndex = 0;
				}
			}
		}

		System::Void connectButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			array<ConnectInfo^>^ devices;
			String^ eui;
			String^ spec;
			int len = 0;
			int i = 0;
			bool connected;

			if (specDataGrid->Visible) {
				specListView->Items->Clear();
				for each (DataGridViewRow^ row in specDataGrid->Rows) {
					if (!row->IsNewRow) {
						len++;
					}
				}
				devices = gcnew array<ConnectInfo^>(len);
				for each (DataGridViewRow^ row in specDataGrid->Rows) {
					if (!row->IsNewRow) {
						devices[i] = gcnew ConnectInfo();
						if (row->Cells["euiColumn"]->Value) {
							eui = row->Cells["euiColumn"]->Value->ToString();
							devices[i]->eui = UInt64::Parse(eui,NumberStyles::HexNumber);
						}
						if (row->Cells["specColumn"]->Value) {
							spec = row->Cells["specColumn"]->Value->ToString();
							devices[i]->specType = (SpecType)Enum::Parse(SpecType::typeid,spec);
						}
						i++;
					}
				}
			}
			// connect or disconnect
			connected = controller->connect(devices);
			specDataGrid->Visible = false;
			specListView->Visible = true;
			if (connected) {
				connectButton->Text = "Disconnect";
			} else {
				connectButton->Text = "Reconnect";
			}
		}

		System::Void specListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			Int64 eui = 0;

			if (specListView->SelectedItems->Count > 0) {
				ListViewItem^ item = specListView->SelectedItems[0];
				eui = UInt64::Parse(item->SubItems[0]->Text,NumberStyles::HexNumber);
			}
			obsFixedButton->Enabled = (eui != 0);
			obsVarButton->Enabled = (eui != 0);
			attrButton->Enabled = (eui != 0);
			controller->selectSpec(eui);
		}

		System::Void comListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			ListView::SelectedIndexCollection^ sel = comListView->SelectedIndices;
			int index = -1;

			if (sel->Count > 0) {
				index = sel[0];
			}
			controller->selectComMsg(index);
		}

		System::Void objListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			ListView::SelectedIndexCollection^ sel = objListView->SelectedIndices;
			int index = -1;

			if (sel->Count > 0) {
				index = sel[0];
			}
			controller->selectObject(index);
		}

		System::Void attrListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			ListView::SelectedIndexCollection^ sel = attrListView->SelectedIndices;
			int index = -1;

			if (sel->Count > 0) {
				index = sel[0];
			}
			controller->selectAttribute(index);
		}

		System::Void obsListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			ListView::SelectedIndexCollection^ sel = obsListView->SelectedIndices;
			int index = -1;

			if (sel->Count > 0) {
				index = sel[0];
			}
			controller->selectObs(index);
		}

		System::Void hl7ListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			ListView::SelectedIndexCollection^ sel = hl7ListView->SelectedIndices;
			int index = -1;

			if (sel->Count > 0) {
				index = sel[0];
			}
			controller->selectHL7(index);
		}

		System::Void obsFixedButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			controller->obsFixedButton();
		}

		System::Void obsVarButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			controller->obsVarButton();
		}

		System::Void attrButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			controller->attrButton();
		}

		System::Void copyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			Windows::Forms::ContextMenuStrip^ owner = (Windows::Forms::ContextMenuStrip^)((ToolStripMenuItem^)sender)->Owner;
			if (owner->SourceControl) {
				((RichTextBox^)owner->SourceControl)->Copy();
			}
		}

		System::Void selectAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			Windows::Forms::ContextMenuStrip^ owner = (Windows::Forms::ContextMenuStrip^)((ToolStripMenuItem^)sender)->Owner;
			if (owner->SourceControl) {
				((RichTextBox^)owner->SourceControl)->SelectAll();
			}
		}

		System::Void specDataGrid_RowsAdded(System::Object^  sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^  e)
		{
			Random^ rnd = gcnew Random();
			UInt64 eui;

			for each (DataGridViewRow^ row in specDataGrid->Rows) {
				if (!row->IsNewRow) {
					if (!row->Cells["euiColumn"]->Value) {
						eui = 0;
						for (int i=0;i<64/8;i++) {
							eui *= 0x100;
							eui |= rnd->Next(0xFF);
						}
						row->Cells["euiColumn"]->Value = String::Format("{0:X16}",eui);
					}
				}
			}
		}

		System::Void comTab_SizeChanged(System::Object^  sender, System::EventArgs^  e)
		{
			int totheight = (comTab->Height - comSplitter1->Height - comSplitter2->Height);
			comListView->Height = (int)(totheight * 0.4);
			comTreeView->Height = (int)(totheight * 0.4);
		}

		System::Void attrTab_SizeChanged(System::Object^  sender, System::EventArgs^  e)
		{
			int totheight = (attrTab->Height - attrSplitter1->Height - attrSplitter2->Height);
			objListView->Height = (int)(totheight * 0.4);
			attrListView->Height = (int)(totheight * 0.4);
		}

		System::Void obsTab_SizeChanged(System::Object^  sender, System::EventArgs^  e)
		{
			int totheight = obsTab->Height - obsSplitter->Height;
			obsListView->Height = totheight / 2;
		}

		System::Void hl7Tab_SizeChanged(System::Object^  sender, System::EventArgs^  e)
		{
			int totheight = hl7Tab->Height - hl7Splitter->Height;
			hl7ListView->Height = totheight / 2;
		}

		System::Void descText_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkClickedEventArgs^  e)
		{
			 System::Diagnostics::Process::Start(e->LinkText);
		}

	};
}
