#include "Decorater.h"
#include <iostream>
int CryptoStream::Read()
{
	stream->Read();
	std::cout << "Read 数据加密操作\n";
	return 0;
}

int CryptoStream::Write()
{
	stream->Write();
	std::cout << "Write 数据加密操作\n";
	return 0;
}

int CryptoStream::Seek()
{
	stream->Seek();
	std::cout << "Seek 数据加密操作\n";
	return 0;
}

int FileStream::Read()
{
	std::cout << "文件读 \n";
	return 0;
}

int FileStream::Write()
{
	std::cout << "文件写\n";
	return 0;
}

int FileStream::Seek()
{
	std::cout << "文件跳转\n";
	return 0;
}

int NetStream::Read()
{
	std::cout << "网络文件读\n";
	return 0;
}

int NetStream::Write()
{
	std::cout << "网络文件写\n";
	return 0;
}

int NetStream::Seek()
{
	std::cout << "网络文件跳转\n";
	return 0;
}

int BufferStream::Read()
{
	stream->Read();
	std::cout << "缓冲读取\n";
	return 0;
}

int BufferStream::Write()
{
	stream->Write();
	std::cout << "缓冲写\n";
	return 0;
}

int BufferStream::Seek()
{
	stream->Seek();
	std::cout << "缓冲跳转\n";
	return 0;
}
