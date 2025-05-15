#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO::Ports;

namespace AgentManager {

	/// <summary>
	/// Summary for PortForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class PortForm : public System::Windows::Forms::Form
	{
	/// <summary>
	/// Required designer variable.
	/// </summary>
	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  closeButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  openButton;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  receivedbytesthresholdText;
	private: System::Windows::Forms::TextBox^  readtimeoutText;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  readbuffersizeText;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  parityreplaceText;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::CheckBox^  dtsCheck;
	private: System::Windows::Forms::CheckBox^  nullCheck;
	private: System::Windows::Forms::TextBox^  writetimeoutText;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  writebuffersizeText;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::ComboBox^  parityCombo;
	private: System::Windows::Forms::ComboBox^  flowCombo;
	private: System::Windows::Forms::ComboBox^  stopbitsCombo;
	private: System::Windows::Forms::CheckBox^  rtsCheck;
	private: System::Windows::Forms::ComboBox^  databitsCombo;
	private: System::Windows::Forms::ComboBox^  baudrateCombo;
	private: System::Windows::Forms::ComboBox^  portnameCombo;
	private: System::Windows::Forms::Button^  refreshButton;

	public:
		SerialPort^ port;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->closeButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->openButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->refreshButton = (gcnew System::Windows::Forms::Button());
			this->portnameCombo = (gcnew System::Windows::Forms::ComboBox());
			this->databitsCombo = (gcnew System::Windows::Forms::ComboBox());
			this->baudrateCombo = (gcnew System::Windows::Forms::ComboBox());
			this->stopbitsCombo = (gcnew System::Windows::Forms::ComboBox());
			this->rtsCheck = (gcnew System::Windows::Forms::CheckBox());
			this->parityCombo = (gcnew System::Windows::Forms::ComboBox());
			this->flowCombo = (gcnew System::Windows::Forms::ComboBox());
			this->dtsCheck = (gcnew System::Windows::Forms::CheckBox());
			this->nullCheck = (gcnew System::Windows::Forms::CheckBox());
			this->writetimeoutText = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->writebuffersizeText = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->readtimeoutText = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->readbuffersizeText = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->parityreplaceText = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->receivedbytesthresholdText = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// closeButton
			// 
			this->closeButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->closeButton->Location = System::Drawing::Point(242, 441);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(75, 23);
			this->closeButton->TabIndex = 2;
			this->closeButton->Text = L"Close Port";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &PortForm::closeButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 391);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 13);
			this->label1->TabIndex = 26;
			this->label1->Text = L"Received Bytes Threshold";
			// 
			// openButton
			// 
			this->openButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->openButton->Location = System::Drawing::Point(12, 441);
			this->openButton->Name = L"openButton";
			this->openButton->Size = System::Drawing::Size(75, 23);
			this->openButton->TabIndex = 1;
			this->openButton->Text = L"Open Port";
			this->openButton->UseVisualStyleBackColor = true;
			this->openButton->Click += gcnew System::EventHandler(this, &PortForm::openButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(57, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Port Name";
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->refreshButton);
			this->groupBox1->Controls->Add(this->portnameCombo);
			this->groupBox1->Controls->Add(this->databitsCombo);
			this->groupBox1->Controls->Add(this->baudrateCombo);
			this->groupBox1->Controls->Add(this->stopbitsCombo);
			this->groupBox1->Controls->Add(this->rtsCheck);
			this->groupBox1->Controls->Add(this->parityCombo);
			this->groupBox1->Controls->Add(this->flowCombo);
			this->groupBox1->Controls->Add(this->dtsCheck);
			this->groupBox1->Controls->Add(this->nullCheck);
			this->groupBox1->Controls->Add(this->writetimeoutText);
			this->groupBox1->Controls->Add(this->label16);
			this->groupBox1->Controls->Add(this->writebuffersizeText);
			this->groupBox1->Controls->Add(this->label15);
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->readtimeoutText);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->readbuffersizeText);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->parityreplaceText);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->receivedbytesthresholdText);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(305, 419);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Properties";
			// 
			// refreshButton
			// 
			this->refreshButton->Location = System::Drawing::Point(224, 17);
			this->refreshButton->Name = L"refreshButton";
			this->refreshButton->Size = System::Drawing::Size(75, 23);
			this->refreshButton->TabIndex = 2;
			this->refreshButton->Text = L"Refresh";
			this->refreshButton->UseVisualStyleBackColor = true;
			this->refreshButton->Click += gcnew System::EventHandler(this, &PortForm::refreshButton_Click);
			// 
			// portnameCombo
			// 
			this->portnameCombo->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->portnameCombo->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::ListItems;
			this->portnameCombo->FormattingEnabled = true;
			this->portnameCombo->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"none", L"odd", L"even", L"mark", L"space"});
			this->portnameCombo->Location = System::Drawing::Point(144, 19);
			this->portnameCombo->Name = L"portnameCombo";
			this->portnameCombo->Size = System::Drawing::Size(66, 21);
			this->portnameCombo->TabIndex = 1;
			// 
			// databitsCombo
			// 
			this->databitsCombo->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->databitsCombo->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::ListItems;
			this->databitsCombo->FormattingEnabled = true;
			this->databitsCombo->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"7", L"8"});
			this->databitsCombo->Location = System::Drawing::Point(144, 72);
			this->databitsCombo->Name = L"databitsCombo";
			this->databitsCombo->Size = System::Drawing::Size(66, 21);
			this->databitsCombo->TabIndex = 6;
			// 
			// baudrateCombo
			// 
			this->baudrateCombo->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->baudrateCombo->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::ListItems;
			this->baudrateCombo->FormattingEnabled = true;
			this->baudrateCombo->Items->AddRange(gcnew cli::array< System::Object^  >(15) {L"110", L"300", L"600", L"1200", L"2400", L"4800", 
				L"9600", L"14400", L"19200", L"38400", L"57600", L"115200", L"230400", L"460800", L"921600"});
			this->baudrateCombo->Location = System::Drawing::Point(144, 45);
			this->baudrateCombo->Name = L"baudrateCombo";
			this->baudrateCombo->Size = System::Drawing::Size(66, 21);
			this->baudrateCombo->TabIndex = 4;
			// 
			// stopbitsCombo
			// 
			this->stopbitsCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->stopbitsCombo->FormattingEnabled = true;
			this->stopbitsCombo->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"0", L"1", L"2", L"1.5"});
			this->stopbitsCombo->Location = System::Drawing::Point(144, 152);
			this->stopbitsCombo->Name = L"stopbitsCombo";
			this->stopbitsCombo->Size = System::Drawing::Size(66, 21);
			this->stopbitsCombo->TabIndex = 12;
			// 
			// rtsCheck
			// 
			this->rtsCheck->AutoSize = true;
			this->rtsCheck->Location = System::Drawing::Point(9, 234);
			this->rtsCheck->Name = L"rtsCheck";
			this->rtsCheck->Size = System::Drawing::Size(84, 17);
			this->rtsCheck->TabIndex = 16;
			this->rtsCheck->Text = L"RTS Enable";
			this->rtsCheck->UseVisualStyleBackColor = true;
			// 
			// parityCombo
			// 
			this->parityCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->parityCombo->FormattingEnabled = true;
			this->parityCombo->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"none", L"odd", L"even", L"mark", L"space"});
			this->parityCombo->Location = System::Drawing::Point(144, 99);
			this->parityCombo->Name = L"parityCombo";
			this->parityCombo->Size = System::Drawing::Size(66, 21);
			this->parityCombo->TabIndex = 8;
			// 
			// flowCombo
			// 
			this->flowCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->flowCombo->FormattingEnabled = true;
			this->flowCombo->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"None", L"XOnXOff", L"RequestToSend", L"RequestToSendXOnXOff"});
			this->flowCombo->Location = System::Drawing::Point(144, 179);
			this->flowCombo->Name = L"flowCombo";
			this->flowCombo->Size = System::Drawing::Size(150, 21);
			this->flowCombo->TabIndex = 14;
			// 
			// dtsCheck
			// 
			this->dtsCheck->AutoSize = true;
			this->dtsCheck->Location = System::Drawing::Point(9, 208);
			this->dtsCheck->Name = L"dtsCheck";
			this->dtsCheck->Size = System::Drawing::Size(85, 17);
			this->dtsCheck->TabIndex = 15;
			this->dtsCheck->Text = L"DTR Enable";
			this->dtsCheck->UseVisualStyleBackColor = true;
			// 
			// nullCheck
			// 
			this->nullCheck->AutoSize = true;
			this->nullCheck->Location = System::Drawing::Point(9, 260);
			this->nullCheck->Name = L"nullCheck";
			this->nullCheck->Size = System::Drawing::Size(83, 17);
			this->nullCheck->TabIndex = 17;
			this->nullCheck->Text = L"Discard Null";
			this->nullCheck->UseVisualStyleBackColor = true;
			// 
			// writetimeoutText
			// 
			this->writetimeoutText->Location = System::Drawing::Point(144, 310);
			this->writetimeoutText->Name = L"writetimeoutText";
			this->writetimeoutText->Size = System::Drawing::Size(50, 20);
			this->writetimeoutText->TabIndex = 21;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 313);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(73, 13);
			this->label16->TabIndex = 20;
			this->label16->Text = L"Write Timeout";
			// 
			// writebuffersizeText
			// 
			this->writebuffersizeText->Location = System::Drawing::Point(144, 362);
			this->writebuffersizeText->Name = L"writebuffersizeText";
			this->writebuffersizeText->Size = System::Drawing::Size(50, 20);
			this->writebuffersizeText->TabIndex = 25;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(6, 365);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(86, 13);
			this->label15->TabIndex = 24;
			this->label15->Text = L"Write Buffer Size";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 155);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(49, 13);
			this->label14->TabIndex = 11;
			this->label14->Text = L"Stop Bits";
			// 
			// readtimeoutText
			// 
			this->readtimeoutText->Location = System::Drawing::Point(144, 284);
			this->readtimeoutText->Name = L"readtimeoutText";
			this->readtimeoutText->Size = System::Drawing::Size(50, 20);
			this->readtimeoutText->TabIndex = 19;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(6, 287);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(74, 13);
			this->label12->TabIndex = 18;
			this->label12->Text = L"Read Timeout";
			// 
			// readbuffersizeText
			// 
			this->readbuffersizeText->Location = System::Drawing::Point(144, 336);
			this->readbuffersizeText->Name = L"readbuffersizeText";
			this->readbuffersizeText->Size = System::Drawing::Size(50, 20);
			this->readbuffersizeText->TabIndex = 23;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(6, 339);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(87, 13);
			this->label11->TabIndex = 22;
			this->label11->Text = L"Read Buffer Size";
			// 
			// parityreplaceText
			// 
			this->parityreplaceText->Location = System::Drawing::Point(144, 126);
			this->parityreplaceText->Name = L"parityreplaceText";
			this->parityreplaceText->Size = System::Drawing::Size(50, 20);
			this->parityreplaceText->TabIndex = 10;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 129);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(76, 13);
			this->label9->TabIndex = 9;
			this->label9->Text = L"Parity Replace";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 102);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(33, 13);
			this->label8->TabIndex = 7;
			this->label8->Text = L"Parity";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 182);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(65, 13);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Flow Control";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 75);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(50, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Data Bits";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 48);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Baud Rate";
			// 
			// receivedbytesthresholdText
			// 
			this->receivedbytesthresholdText->Location = System::Drawing::Point(144, 388);
			this->receivedbytesthresholdText->Name = L"receivedbytesthresholdText";
			this->receivedbytesthresholdText->Size = System::Drawing::Size(50, 20);
			this->receivedbytesthresholdText->TabIndex = 27;
			// 
			// PortForm
			// 
			this->AcceptButton = this->openButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(329, 476);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->openButton);
			this->Controls->Add(this->closeButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"PortForm";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Com Port";
			this->Shown += gcnew System::EventHandler(this, &PortForm::portForm_Shown);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	public:
		PortForm() {
			InitializeComponent();

			port = gcnew SerialPort();
		}

	protected:
		~PortForm() {
			if (components) {
				delete components;
			}
		}

	private:
		void portToForm() {
			portnameCombo->Text = port->PortName;
			baudrateCombo->Text = port->BaudRate.ToString();
			databitsCombo->Text = port->DataBits.ToString();
			parityCombo->SelectedIndex = (int)port->Parity;
			parityreplaceText->Text = port->ParityReplace.ToString();
			stopbitsCombo->SelectedIndex = (int)port->StopBits;
			flowCombo->SelectedIndex = (int)port->Handshake;
			dtsCheck->Checked = port->DtrEnable;
			rtsCheck->Checked = port->RtsEnable;
			nullCheck->Checked = port->DiscardNull;
			readtimeoutText->Text = port->ReadTimeout.ToString();
			writetimeoutText->Text = port->WriteTimeout.ToString();
			readbuffersizeText->Text = port->ReadBufferSize.ToString();
			writebuffersizeText->Text = port->WriteBufferSize.ToString();
			receivedbytesthresholdText->Text = port->ReceivedBytesThreshold.ToString();
		}

		void formToPort() {
			port->PortName = portnameCombo->Text;
			port->BaudRate = int::Parse(baudrateCombo->Text);
			port->DataBits = int::Parse(databitsCombo->Text);
			port->Parity = (Parity)parityCombo->SelectedIndex;
			port->ParityReplace = int::Parse(parityreplaceText->Text);
			port->StopBits = (StopBits)stopbitsCombo->SelectedIndex;
			port->Handshake = (Handshake)flowCombo->SelectedIndex;
			port->DtrEnable = dtsCheck->Checked;
			port->RtsEnable = rtsCheck->Checked;
			port->DiscardNull = nullCheck->Checked;
			port->ReadTimeout = int::Parse(readtimeoutText->Text);
			port->WriteTimeout = int::Parse(writetimeoutText->Text);
			port->ReadBufferSize = int::Parse(readbuffersizeText->Text);
			port->WriteBufferSize = int::Parse(writebuffersizeText->Text);
			port->ReceivedBytesThreshold = int::Parse(receivedbytesthresholdText->Text);
		}

		void updateUI() {
			array<String^>^ portnames = port->GetPortNames();
			portnameCombo->Items->Clear();
			portnameCombo->Items->AddRange(portnames);

			openButton->Enabled = !port->IsOpen;
			closeButton->Enabled = port->IsOpen;
		}

	private:
		System::Void portForm_Shown(System::Object^  sender, System::EventArgs^  e) {
			updateUI();
			portToForm();
		}

		System::Void refreshButton_Click(System::Object^  sender, System::EventArgs^  e) {
			updateUI();
		}

		System::Void openButton_Click(System::Object^  sender, System::EventArgs^  e) {
			formToPort();
			try {
				port->Open();
				Close();
				DialogResult = ::DialogResult::OK;
			} catch (Exception^ e) {
				MessageBox::Show(e->Message,"Com Error",MessageBoxButtons::OK,MessageBoxIcon::Error);
			}
			updateUI();
		}

		System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e) {
			port->Close();
			updateUI();
		}

	};
}
