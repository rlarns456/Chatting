#pragma once

namespace Chatting {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;
	using namespace FormatterText;

	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
		{
			InitializeComponent();
			CheckForIllegalCrossThreadCalls = false;
		}

	protected:
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Button;
	protected:
	private: System::Windows::Forms::TextBox^  ipTextBox;
	private: System::Windows::Forms::RichTextBox^  mainTextBox;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->Button = (gcnew System::Windows::Forms::Button());
			this->ipTextBox = (gcnew System::Windows::Forms::TextBox());
			this->mainTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// Button
			// 
			this->Button->Location = System::Drawing::Point(271, 32);
			this->Button->Name = L"Button";
			this->Button->Size = System::Drawing::Size(66, 33);
			this->Button->TabIndex = 0;
			this->Button->Text = L"����";
			this->Button->UseVisualStyleBackColor = true;
			this->Button->Click += gcnew System::EventHandler(this, &MyForm1::button1_Click);
			// 
			// ipTextBox
			// 
			this->ipTextBox->Location = System::Drawing::Point(74, 38);
			this->ipTextBox->Name = L"ipTextBox";
			this->ipTextBox->Size = System::Drawing::Size(173, 21);
			this->ipTextBox->TabIndex = 3;
			// 
			// mainTextBox
			// 
			this->mainTextBox->Location = System::Drawing::Point(31, 89);
			this->mainTextBox->Name = L"mainTextBox";
			this->mainTextBox->Size = System::Drawing::Size(311, 223);
			this->mainTextBox->TabIndex = 4;
			this->mainTextBox->Text = L"";
			this->mainTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm1::mainTextBox_KeyPress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 42);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 12);
			this->label1->TabIndex = 5;
			this->label1->Text = L"ip�ּ�";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm1::BackgroundWorker_DoWork);
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 351);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->mainTextBox);
			this->Controls->Add(this->ipTextBox);
			this->Controls->Add(this->Button);
			this->Name = L"MyForm1";
			this->Text = L"Server";
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		IP = gcnew IPEndPoint(IPAddress::Parse(ipTextBox->Text), 2016);
		backgroundWorker1->WorkerSupportsCancellation = true;
		backgroundWorker1->RunWorkerAsync();
	}

	private: System::Void mainTextBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		e->Handled = true;
	}

	public: static Socket^ server;
	public: static List<Socket^>^ listClient = gcnew List<Socket^>();
	public: static IPEndPoint^ IP;
	public: static Thread^ threadClient;

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		server = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::IP);
	}

	private: static void client(Object^ obj) {
		Socket^ socket = (Socket^)obj;
		while (true) {
			try
			{
				array<unsigned char>^ buff = gcnew array<unsigned char>(1024);
				int temp = socket->Receive(buff);

				for each(Socket^ sock in listClient)
				{
					try {
						sock->Send(buff, buff->Length, SocketFlags::None);
					}
					catch (Exception^ ex) {
					}
				}
			}
			catch (Exception^ ex) {
				listClient->Remove(socket);
				return;
			}
		}
	}
	private: void addTextToMainText(String ^text) {
		mainTextBox->AppendText(text + "\n");
	}

			 // backgroundWorker1 ���� �Լ�
	private: System::Void BackgroundWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		// ���� ������ �˸�
		server->Bind(IP);
		server->Listen(10);
		String^ text = "������ �����ϰ� �ֽ��ϴ�.";
		addTextToMainText(text);

		// ���� �ݺ����� ����ڵ��� ��Ʈ����
		while (true)
		{
			Socket^ clientAccept = server->Accept();
			listClient->Add(clientAccept);

			// Ŭ���̾�Ʈ ���� �� �ش� Ŭ���̾�Ʈ���� �����带 �Ҵ��� client �Լ� ����
			threadClient = gcnew Thread(gcnew ParameterizedThreadStart(Chatting::MyForm1::client));
			threadClient->IsBackground = true;
			threadClient->Start(clientAccept);

			// Ŭ���̾�Ʈ ������ �˸�
			String^ textTemp = "Ŭ���̾�Ʈ�� �����߽��ϴ�." + clientAccept->RemoteEndPoint->ToString();
			addTextToMainText(textTemp);
		}

	}
	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (backgroundWorker1->IsBusy)
		{
			backgroundWorker1->CancelAsync();
		}
	}

	};
}
