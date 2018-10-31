#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Runtime::Serialization;
	using namespace System::Runtime::Serialization::Formatters::Binary;
	using namespace System::Runtime::Serialization::Formatters;
	using namespace System::Threading;
	using namespace FormatterText;
	using namespace System::IO;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void) {
			InitializeComponent();
			CheckForIllegalCrossThreadCalls = false;
		}
	public: Socket^ client;
	public: IPEndPoint^ IP;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	public: Thread^ clientThread;
	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  ipTextBox;
	protected:

	private: System::Windows::Forms::Button^  enterButton;
	private: System::Windows::Forms::TextBox^  inputTextBox;


	private: System::Windows::Forms::RichTextBox^  mainTextBox;
	private: System::Windows::Forms::Button^  sendButton;



	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ipTextBox = (gcnew System::Windows::Forms::TextBox());
			this->enterButton = (gcnew System::Windows::Forms::Button());
			this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->mainTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->sendButton = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(25, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"ip林家";
			// 
			// ipTextBox
			// 
			this->ipTextBox->Location = System::Drawing::Point(70, 38);
			this->ipTextBox->Name = L"ipTextBox";
			this->ipTextBox->Size = System::Drawing::Size(205, 21);
			this->ipTextBox->TabIndex = 1;
			// 
			// enterButton
			// 
			this->enterButton->Location = System::Drawing::Point(290, 30);
			this->enterButton->Name = L"enterButton";
			this->enterButton->Size = System::Drawing::Size(71, 39);
			this->enterButton->TabIndex = 2;
			this->enterButton->Text = L"立加";
			this->enterButton->UseVisualStyleBackColor = true;
			this->enterButton->Click += gcnew System::EventHandler(this, &MyForm::enterButton_Click);
			// 
			// inputTextBox
			// 
			this->inputTextBox->Location = System::Drawing::Point(29, 285);
			this->inputTextBox->Multiline = true;
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(264, 29);
			this->inputTextBox->TabIndex = 3;
			// 
			// mainTextBox
			// 
			this->mainTextBox->Location = System::Drawing::Point(27, 84);
			this->mainTextBox->Name = L"mainTextBox";
			this->mainTextBox->Size = System::Drawing::Size(334, 173);
			this->mainTextBox->TabIndex = 4;
			this->mainTextBox->Text = L"";
			// 
			// sendButton
			// 
			this->sendButton->Location = System::Drawing::Point(299, 285);
			this->sendButton->Name = L"sendButton";
			this->sendButton->Size = System::Drawing::Size(62, 29);
			this->sendButton->TabIndex = 5;
			this->sendButton->Text = L"傈价";
			this->sendButton->UseVisualStyleBackColor = true;
			this->sendButton->Click += gcnew System::EventHandler(this, &MyForm::sendButton_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 351);
			this->Controls->Add(this->sendButton);
			this->Controls->Add(this->mainTextBox);
			this->Controls->Add(this->inputTextBox);
			this->Controls->Add(this->enterButton);
			this->Controls->Add(this->ipTextBox);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		client = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::IP);
	}

	private: System::Void enterButton_Click(System::Object^  sender, System::EventArgs^  e) {
		try {
			IP = gcnew IPEndPoint(IPAddress::Parse(ipTextBox->Text), 2016);
			client->Connect(IP);
			backgroundWorker1->RunWorkerAsync();
		}
		catch (Exception^ ex) {
			MessageBox::Show(ex->Message);
		}
	}

	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		while (true) {
			array<unsigned char>^ buf = gcnew array<unsigned char>(1024);
			int temp = client->Receive(buf);
			FormatterText::StructChat^ str = gcnew FormatterText::StructChat();

			str = Deserialize(buf);
			addText(str->textChat);
		}
	}
	private: void addText(String^ text) {
		mainTextBox->AppendText(text + "\n");
		mainTextBox->ScrollToCaret();
	}

	public: array<unsigned char, 1>^ Serialize(FormatterText::StructChat^ str) {
		MemoryStream^ ms = gcnew MemoryStream();
		BinaryFormatter^ bf = gcnew BinaryFormatter();
		bf->Serialize(ms, str);
		return ms->ToArray();
	}

	public: FormatterText::StructChat^ Deserialize(array<unsigned char>^buff) {
		MemoryStream^ ms = gcnew MemoryStream(buff);
		BinaryFormatter^ bf = gcnew BinaryFormatter();
		return (FormatterText::StructChat^)bf->Deserialize(ms);
	}

	private: System::Void sendButton_Click(System::Object^  sender, System::EventArgs^  e) {
		FormatterText::StructChat^ str = gcnew FormatterText::StructChat();
		str->textChat = inputTextBox->Text;

		array<unsigned char>^ buf = gcnew array<unsigned char>(1024);
		MemoryStream^ ms = gcnew MemoryStream();
		BinaryFormatter^ bf = gcnew BinaryFormatter();
		bf->Serialize(ms, str);
		buf = ms->ToArray();
		client->Send(buf, buf->Length, SocketFlags::None);
	}
	};
}
