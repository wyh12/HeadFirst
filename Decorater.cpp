#include "Decorater.h"
#include <iostream>
int CryptoStream::Read()
{
	stream->Read();
	std::cout << "Read ���ݼ��ܲ���\n";
	return 0;
}

int CryptoStream::Write()
{
	stream->Write();
	std::cout << "Write ���ݼ��ܲ���\n";
	return 0;
}

int CryptoStream::Seek()
{
	stream->Seek();
	std::cout << "Seek ���ݼ��ܲ���\n";
	return 0;
}

int FileStream::Read()
{
	std::cout << "�ļ��� \n";
	return 0;
}

int FileStream::Write()
{
	std::cout << "�ļ�д\n";
	return 0;
}

int FileStream::Seek()
{
	std::cout << "�ļ���ת\n";
	return 0;
}

int NetStream::Read()
{
	std::cout << "�����ļ���\n";
	return 0;
}

int NetStream::Write()
{
	std::cout << "�����ļ�д\n";
	return 0;
}

int NetStream::Seek()
{
	std::cout << "�����ļ���ת\n";
	return 0;
}

int BufferStream::Read()
{
	stream->Read();
	std::cout << "�����ȡ\n";
	return 0;
}

int BufferStream::Write()
{
	stream->Write();
	std::cout << "����д\n";
	return 0;
}

int BufferStream::Seek()
{
	stream->Seek();
	std::cout << "������ת\n";
	return 0;
}
