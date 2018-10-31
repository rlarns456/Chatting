using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::Serialization::Formatters::Binary;
using namespace System::Runtime::Serialization::Formatters;

namespace FormatterText {
	[Serializable]
	public ref class StructChat
	{

	public:
		String^ textChat;

		// �⺻ ������ ����
	public: StructChat()
	{
		textChat = "";
	}

	public: StructChat(String^ text)
	{
		textChat = text;
	}

			// ������ ��ü �����͸� ������ �Լ�
	public: void GetObjectData(SerializationInfo^ info, StreamingContext^ context)
	{
		info->AddValue("text", textChat);
	}

			// Serialization ������ �̿��� �ʱ�ȭ�ϴ� ������
	public: StructChat(SerializationInfo^ info, StreamingContext^ context)
	{
		textChat = (String^)info->GetValue("text", String::typeid);
	}
	};
}
