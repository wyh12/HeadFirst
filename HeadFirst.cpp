// HeadFirst.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <array>
#include <list>
#include <vector>
// 设计模式 策略模式
class WeaponBehavor {
public:
	virtual void useWeapon() = 0;
};

class Knief :public WeaponBehavor {
	virtual void useWeapon() { std::cout << "use knief\n"; }
};

class Bow2Arrow :public WeaponBehavor {
	virtual void useWeapon() { std::cout << "use Bow and Arrow\n"; }
};

class Axe :public WeaponBehavor {
	virtual void useWeapon() { std::cout << "use Axe\n"; }
};

class Swod :public WeaponBehavor {
	virtual void useWeapon() { std::cout << "use Swod\n"; }
};


class character  {
public:
	character(WeaponBehavor * weapon):behavor(weapon) {}
	void SetWeapon(WeaponBehavor *weapon) { behavor = weapon; }
	virtual void fight() {
		behavor->useWeapon();
	}

private:
	WeaponBehavor *behavor;
};

// 设计模式 观察者模式
/*
* 在对象之间定义一个一对多的依赖，
* 这样一来，当一个对象的状态改变时，
* 依赖它的对象都会收到通知并更新状态。
*/

// 气象台
class Weather;

class BordBase{
public:
	BordBase(const  Weather * ref) :weatherIns(ref) {}
	virtual void Updata(float T, float H, float P) = 0;
	virtual void Show() = 0;	

protected:
	float temperature;
	float pressure;
	float humidity;
	const  Weather *weatherIns;
};

class Weather {
public:
	void WeatherDataUpdata(float T, float H, float P) {
		temperature = T;
		pressure = P;
		humidity = H;
		notify();
	}

	float GetT() { return temperature; }
	float GetH() { return humidity; }
	float GetP() { return pressure; }

	void SubcriberObj(BordBase * bord) {
		subscriber.push_front(bord);
	}

	void removeObj(BordBase *bord) {
		subscriber.remove(bord);
	}

	void notify() {
		std::list<BordBase*>::const_iterator iter = subscriber.begin();
		for (; iter != subscriber.end(); iter++)
			(*iter)->Updata(temperature, humidity, pressure);
	}
private:
	// 订阅者
	std::list<BordBase *> subscriber;

	float temperature;
	float pressure;
	float humidity;
};


class Bord_Mode1 :public BordBase {
public:
	Bord_Mode1(const Weather * ref) :BordBase(ref) { }
	void Updata(float T, float H, float P) override{
		temperature = T;
		pressure = P;
		humidity = H;
		Show();
	}

	void Show() override {
		std::cout << "Bord_Mode1 Now T: " << temperature << " H: " << humidity << " P: " << pressure << std::endl;
	}


};

class Bord_Mode2 : public BordBase {
public:
	Bord_Mode2(const Weather * ref) :BordBase(ref) { 
		MaxT = 0;
		MinT = 0;
		AvgY = 0;
		INIT = true;
	}

	void Updata(float T, float H, float P) override {
		temperature = T;
		pressure = P;
		humidity = H;
		
		if (INIT) {
			MaxT = T;
			MinT = T;
			AvgY = T;
			INIT = false;
		}
		else {
			if (T > MaxT)
				MaxT = T;

			if (MinT > T)
				MinT = T;

			AvgY = (AvgY + T) / 2;
		}

		Show();
	}

	void Show() override {
		std::cout << "Bord_Mode2 Max T: " << MaxT << " Min T: " << MinT << " Avg T: " << AvgY << std::endl;
	}

private:
	float MaxT, MinT,AvgY;
	bool INIT;
};
//装饰者模式 
/*
*  类应该对扩展开放，对修改关闭 
*  动态的将责任加到对象上，需要扩展功能，装饰者提供有别于继承的另一种选择
*/
class Stream {
public:
	virtual void Read(std::string &str) = 0;
	virtual void Write(std::string str) = 0;
	virtual void Seek(int postion) = 0;
	virtual ~Stream() {}
};

class FileStream :public Stream {
public:
	virtual void Read(std::string &str) override{}
	virtual void Write(std::string str) override {}
	virtual void Seek(int postion) override {}
	virtual ~FileStream() {}
};

class NetWorkStream :public Stream {
public:
	virtual void Read(std::string &str) override {}
	virtual void Write(std::string str) override {}
	virtual void Seek(int postion) override {}
	virtual ~NetWorkStream() {}
};

class DecoratorStream :public Stream {
protected:
	Stream *stream;

	DecoratorStream(Stream *st) :stream(st) {}
public:
	virtual ~DecoratorStream() {}
};

class CryptoStream :public DecoratorStream {
public:
	virtual void Read(std::string &str) override{
		// do something
		stream->Read(str);
	}

	virtual void Write(std::string str) override {
		// do something
		stream->Write(str);
	}

	virtual void Seek(int Postion) override {
		// do something
		stream->Seek(Postion);
	}

	virtual ~CryptoStream() {}

	CryptoStream(Stream *st) :DecoratorStream(st) {}
};

class BufferStream :public DecoratorStream {
public:
	virtual void Read(std::string &str) override {
		// do something
		stream->Read(str);
	}

	virtual void Write(std::string str) override {
		// do something
		stream->Write(str);
	}

	virtual void Seek(int Postion) override {
		// do something
		stream->Seek(Postion);
	}

	virtual ~BufferStream() {}

	BufferStream(Stream *st) :DecoratorStream(st) {}
};


void RunStream() {
	FileStream *s1 = new FileStream;
	CryptoStream *sc = new CryptoStream(s1);
	BufferStream *sb = new BufferStream(s1);
	BufferStream *sb2 = new BufferStream(sc);
}
// 工厂模式
/*
* 
*/

class Pizza{
public:
	virtual void Order()=0;
protected:
	void prepare() {}
};


class PizzaStore {
public:
	virtual Pizza *CreatePizza(std::string type)=0;
};

class NYcheetPizza :public Pizza {
public:
	void Order() override { std::cout << "NYcheet Pizaa\n"; }
};

class ChicagocheetPizza :public Pizza {
public:
	void Order() { std::cout << "Chicagocheet Pizza\n\n"; }
};

class NYveggiePizza :public Pizza {
public:
	void Order() { std::cout << "NYveggie Pizza\n"; }
};

class ChicagoveggiePizza :public Pizza {
public:
	void Order() { std::cout << "Chicagoveggie Pizza\n"; }
};

class NYPizzaStore :public PizzaStore {
public:
	Pizza *CreatePizza(std::string type) override{
		if (type == "cheet")
			return new NYcheetPizza();
		else if (type == "veggie")
			return new NYveggiePizza();
	}
};

class ChicagoStore :public PizzaStore {
public:
	Pizza *CreatePizza(std::string type) override{
		if (type == "cheet")
			return new ChicagocheetPizza();
		else if (type == "veggie")
			return new ChicagoveggiePizza();
	}
};


//单例模式
class ChocolateBoiler {
private:
	ChocolateBoiler() :isempty(true),isboil(false){ }
	ChocolateBoiler(const ChocolateBoiler &)= delete;
	ChocolateBoiler &operator=(const ChocolateBoiler &)= delete;
public:
	static ChocolateBoiler *GetIns() { 
		
		return &_ins;
	}
	~ChocolateBoiler() { std::cout << "ins destruct\n"; } 
public:
	void fill() {
		if (IsEmpty()) {
			isempty = false;
			isboil = false;
		}
	}
	void drain() {
		if (!IsEmpty() && IsBoiled()) {
			isempty = true;		
		}
	}
	void boil() {
		if (!IsEmpty() && !IsBoiled()) {
			isboil = true;
		}
	}
	bool IsEmpty() { return isempty; }
	bool IsBoiled() { return isboil; }
private:
	bool isempty;
	bool isboil;
	static  ChocolateBoiler _ins;
};
ChocolateBoiler ChocolateBoiler::_ins;


// 命令模式 --- 将请求封装成对象，这可以让你使用不同的请求
// 队列,或者日志请求来序列化其他对象。命令模式也支持撤销操作。

// OO原则 
/*
*	将请求对象与执行对象解耦，通过命令进行沟通
*	调用者通过统一的接口执行命令，无需知道具体的实现细节。
*/

class Command {
public:
	virtual void execute() = 0;
	//	virtual void SetCommand(Command *cmd) = 0;
	virtual void Undo() = 0;
};

class Fans {
public:
	Fans() :spd(off) {}
	enum Speed {
		low = 1, medium, hight, off
	};

	Speed GetSpeed() { return spd; }

	void SpeedH() { spd = hight; std::cout << "set fan Speed Hight\n"; }
	void SpeedM() { spd = medium; std::cout << "set Fan Speed Medium\n"; }
	void SpeedL() { spd = low; std::cout << "set Fan Speed Low\n"; }
	void SpeedOff() { spd = off; std::cout << "set Fan Speed Off\n"; }
protected:
	Speed spd;
};

class Light {
public:
	void On() { std::cout << "light is On\n"; }
	void Off() { std::cout << "light is Off\n"; }
};

class FanHWithUndo :public Command {
protected:
	Fans *fan;
	Fans::Speed spd;
public:
	FanHWithUndo(Fans *fan) {
		this->fan = fan;
	}
	void execute()override {
		spd = this->fan->GetSpeed();
		fan->SpeedH();

	}

	void Undo() {
		if (spd == Fans::hight) {
			fan->SpeedH();
		}
		else if (spd == Fans::medium) {
			fan->SpeedM();
		}
		else if (spd == Fans::low) {
			fan->SpeedL();
		}
		else {
			fan->SpeedOff();
		}
	}
};


class FanMWithUndo :public FanHWithUndo {
public:
	FanMWithUndo(Fans *fan) :FanHWithUndo(fan) {	}
	void execute() override {
		spd = fan->GetSpeed();
		fan->SpeedM();

	}
};

class FanLWithUndo :public FanHWithUndo {
public:
	FanLWithUndo(Fans *fan) :FanHWithUndo(fan) {	}
	void execute() override {
		spd = fan->GetSpeed();
		fan->SpeedL();

	}
};


class FanOffWithUndo :public FanHWithUndo {
public:
	FanOffWithUndo(Fans *fan) :FanHWithUndo(fan) {	}
	void execute() override {
		spd = fan->GetSpeed();
		fan->SpeedOff();

	}
};

class LightOnCmd :public Command {
protected:
	Light *light;
public:
	LightOnCmd(Light *li) :light(li) {	}
	void execute() override {
		light->On();
		std::cout << "light is On\n";
	}

	void Undo() override {
		light->Off();
		std::cout << "light is off\n";
	}
};

class LightOffCmd :public Command {
protected:
	Light *light;
public:
	LightOffCmd(Light *li) :light(li) {	}
	void execute() override {
		light->Off();
		std::cout << "light is Off\n";
	}

	void Undo() override {
		light->On();
		std::cout << "light is on\n";
	}
};

class Nocommand :public Command {
public:
	void execute() override { std::cout << "NoCommand\n"; }
	void Undo() override { std::cout << "Undo is Nothing\n"; }
};


class Controller {
	Command *cmdDo[7];
	Command *cmdUndo[7];
	Command *last;
public:
	void setCommadPair(int index, Command *ins1, Command *ins2) {
		if (index > 7)
			return;
		cmdDo[index] = ins1;
		cmdUndo[index] = ins2;
	}

	void OnPress(int index) {
		if (index < 7) {
			cmdDo[index]->execute();
			last = cmdDo[index];
		}
	}

	void OffPress(int index) {
		if (index < 7) {
			cmdUndo[index]->execute();
			last = cmdUndo[index];
		}
	}

	void Undo() {
		last->Undo();
	}
};

struct MuneItem
{
	MuneItem() {}
	MuneItem(std::string name, std::string description, bool veg, double price) :
		_name(name),
		_description(description),
		_vegetarian(veg),
		_price(price)
	{

	}
	std::string _name;
	std::string _description;
	bool _vegetarian;
	double _price;
};



// 迭代器与组合模式
template<class T>
class IteaMune {
public:
	virtual T* next() = 0;
	virtual bool HasNest() = 0;
};

class PancakeHouseMenu {
public:
	PancakeHouseMenu() {
		addItem("K&B's Pancake Breakfast","Panckaes with scrambled eggs", true,2.99);
		addItem("Regular Pancake Breakefast", "Panckaes with fried eggs ,sausage", false, 2.99);
		addItem("Blueberry", "Panckaes made with fresh bluerries", false, 2.99);
		addItem("Waffles", "Waffles with your choice of blueberries or strawberries", true, 3.49);
	}

	std::vector<MuneItem> getMenuItems() {
		return Mune;
	}
private:
	void addItem(std::string name, std::string description, bool veg, double price) {
		MuneItem item(name, description, veg, price );
		Mune.push_back(item);
	}
private:
	std::vector<MuneItem> Mune;

};

#define MaxItems 4
class DinerMune {
public:
	DinerMune():
		nowIndex(0)
	{
		addItem("Vegetarian BLT", "Bacon with lettuce &tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Suop of the day,with a side of potato salad ", false, 3.99);
		addItem("HotDog", "a hot dog ,with saurkraut,relish, onions, topped with chese", false, 3.99);
	}
	MuneItem* getMenuItems() {
		return Mune;
	}
private:
	void addItem(std::string name, std::string description, bool veg, double price) {
		if (nowIndex < MaxItems) {
			MuneItem item(name, description, veg, price);
			Mune[nowIndex] = item;
			nowIndex++;
		}
	}
private:
	MuneItem Mune[MaxItems];
	int nowIndex;
};

class Waiter {
public:
	Waiter() {
	
	}
	void listMune() {
	
	}
};


//模板方法
/*
*	定义到一个操作中的算法骨架（稳定），而将一些步骤延迟（变化的）到子类中。
*	模板方法（template Method）使得子类可以不改变结构的情况下重新定义（override 重写）该算法的某些步骤。
*	设置模式--GoF
*/
class Lib {
public:
	// 延迟绑定方式  可认为主题骨架所处的位置来确定的，lib中为延迟绑定
	//	若在application实现时实现骨干框架，则属于早绑定。
	void Run() {
	
		fun1();
		if (fun2()) {
			fun3();
		}

		for (int i(0); i < 10; i++) {
			fun4();
		}

		fun5();
	}
	void fun1() {}
	void fun3() {}
	void fun5() {}
	virtual ~Lib() {};

protected:
	
	virtual void fun4() = 0;
	virtual bool fun2() = 0;
};

class application :public Lib {
public:
	virtual ~application() {}
protected:
	virtual bool fun2() override{}
	virtual void fun4() override{}
};

//策略模式

int main()
{
	/*Fans fan;
	FanHWithUndo Fh(&fan);
	FanMWithUndo Fm(&fan);
	FanOffWithUndo Fo(&fan);

	Controller ctl;
	ctl.setCommadPair(0, &Fh, &Fo);
	ctl.setCommadPair(1, &Fm, &Fo);

	ctl.OnPress(0);
	ctl.OffPress(0);
	ctl.Undo();

	ctl.OnPress(1);
	ctl.Undo();
	ctl.OnPress(1);
	ctl.OffPress(1);*/

	/*Weather wea;
	Bord_Mode1 b1(&wea);
	Bord_Mode2 b2(&wea);

	wea.SubcriberObj(&b1);
	wea.SubcriberObj(&b2);
	
	wea.WeatherDataUpdata(80, 65, 30.4f);
	wea.WeatherDataUpdata(82, 70, 29.2f);
	wea.WeatherDataUpdata(78, 90, 29.2f);

    std::cout << "Hello World!\n"; 

	HouseCoofe order;
	Milk add1(&order);
	Mocha add2(&add1);
	add2.Getdescribe();
	std::cout << "coffe cost"<< add2.cost()<<std::endl;

	NYPizzaStore *nys = new NYPizzaStore();
	nys->CreatePizza("cheet")->Order();
	ChocolateBoiler *is = ChocolateBoiler::GetIns();*/
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
