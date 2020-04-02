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


// 扩展模式，更完美的方法是将Stream* stream提取出来。使用时继承Decorater类
class Decorater :public Stream {
public:
	Decorater(Stream* _stream) :stream(_stream) {}
	virtual ~Decorater() {}
protected:
	Stream* stream;
};


// 继承Stream类是为了与其他的类似功能类进行组合
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

