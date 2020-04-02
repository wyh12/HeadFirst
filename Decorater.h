#pragma once
class Stream
{
public:
	virtual ~Stream() {}
	virtual int Read() = 0;
	virtual int Write() = 0;
	virtual int Seek() = 0;
};


class  FileStream:public Stream
{
public:
	FileStream() {}
	virtual ~FileStream() {}
public:
	virtual int Read() override;
	virtual int Write() override;
	virtual int Seek() override;
};


class  NetStream :public Stream
{
public:
	NetStream() {}
	virtual ~NetStream() {}
public:
	virtual int Read() override;
	virtual int Write() override;
	virtual int Seek() override;
};


// ��չģʽ���������ķ����ǽ�Stream* stream��ȡ������ʹ��ʱ�̳�Decorater��
class Decorater :public Stream {
public:
	Decorater(Stream* _stream) :stream(_stream) {}
	virtual ~Decorater() {}
protected:
	Stream* stream;
};


// �̳�Stream����Ϊ�������������ƹ�����������
class CryptoStream :public Decorater {
public:
	CryptoStream(Stream* _stream):Decorater(_stream)  {}
	virtual int Read() override;
	virtual int Write() override;
	virtual int Seek() override;

};

class BufferStream :public Decorater {	
public:
	BufferStream(Stream* _stream) :Decorater(_stream) {}
	~BufferStream() {}

public:
	virtual int Read() override;
	virtual int Write() override;
	virtual int Seek() override;
};

