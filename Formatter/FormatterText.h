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

		// 기본 생성자 선언
	public: StructChat()
	{
		textChat = "";
	}

	public: StructChat(String^ text)
	{
		textChat = text;
	}

			// 현재의 객체 데이터를 얻어오는 함수
	public: void GetObjectData(SerializationInfo^ info, StreamingContext^ context)
	{
		info->AddValue("text", textChat);
	}

			// Serialization 정보를 이용해 초기화하는 생성자
	public: StructChat(SerializationInfo^ info, StreamingContext^ context)
	{
		textChat = (String^)info->GetValue("text", String::typeid);
	}
	};
}
