#pragma once

#include "TCPInfo.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;

namespace AgentManager {

	/// <summary>
	/// Summary for TCPForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class TCPForm : public System::Windows::Forms::Form
	{
	/// <summary>
	/// Required designer variable.
	/// </summary>
	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::Button^  okButton;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::MaskedTextBox^  targetIpText;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MaskedTextBox^  targetPortText;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::MaskedTextBox^  listenPortText;

	public:
		TCPInfo^ portInfo;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listenPortText = (gcnew System::Windows::Forms::MaskedTextBox());
			this->targetPortText = (gcnew System::Windows::Forms::MaskedTextBox());
			this->targetIpText = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// cancelButton
			// 
			this->cancelButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->Location = System::Drawing::Point(223, 96);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 2;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			// 
			// okButton
			// 
			this->okButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->okButton->Location = System::Drawing::Point(12, 96);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 1;
			this->okButton->Text = L"Ok";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &TCPForm::okButton_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->listenPortText);
			this->groupBox1->Controls->Add(this->targetPortText);
			this->groupBox1->Controls->Add(this->targetIpText);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(286, 74);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Properties";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(205, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Port";
			// 
			// listenPortText
			// 
			this->listenPortText->AsciiOnly = true;
			this->listenPortText->Location = System::Drawing::Point(237, 45);
			this->listenPortText->Name = L"listenPortText";
			this->listenPortText->Size = System::Drawing::Size(40, 20);
			this->listenPortText->TabIndex = 5;
			// 
			// targetPortText
			// 
			this->targetPortText->AsciiOnly = true;
			this->targetPortText->Location = System::Drawing::Point(237, 19);
			this->targetPortText->Name = L"targetPortText";
			this->targetPortText->Size = System::Drawing::Size(40, 20);
			this->targetPortText->TabIndex = 3;
			// 
			// targetIpText
			// 
			this->targetIpText->AsciiOnly = true;
			this->targetIpText->Location = System::Drawing::Point(69, 19);
			this->targetIpText->Name = L"targetIpText";
			this->targetIpText->Size = System::Drawing::Size(100, 20);
			this->targetIpText->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(174, 48);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(57, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Listen Port";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(51, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Target IP";
			// 
			// TCPForm
			// 
			this->AcceptButton = this->okButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->cancelButton;
			this->ClientSize = System::Drawing::Size(310, 131);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->cancelButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"TCPForm";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"TCP Port";
			this->Shown += gcnew System::EventHandler(this, &TCPForm::portForm_Shown);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	public:
		TCPForm()
		{
			portInfo = gcnew TCPInfo();
			InitializeComponent();
		}

	protected:
		~TCPForm()
		{
			if (components) {
				delete components;
			}
		}

	private:
		void portToForm()
		{
			targetIpText->Text = portInfo->targetIpInfo->Address->ToString();
			targetPortText->Text = portInfo->targetIpInfo->Port.ToString();
			listenPortText->Text = portInfo->listenPort.ToString();
		}

		bool formToPort()
		{
			return portInfo->parse(targetIpText->Text,targetPortText->Text,listenPortText->Text);
		}

		System::Void portForm_Shown(System::Object^  sender, System::EventArgs^  e)
		{
			portToForm();
		}

		System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (formToPort()) {
				DialogResult = ::DialogResult::OK;
				Close();
			} else {
				MessageBox::Show("Invalid Port information","Port Error",MessageBoxButtons::OK,MessageBoxIcon::Error);
			}
		}

	};
}
