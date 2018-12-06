// HeadFirst.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <array>
#include <list>
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
*/
class CoffeBase {
public:
	typedef enum {
		TCap = 1,
		NCap,
		VCap
	}CAPSIZE;

	CoffeBase() : size(NCap) {}	
	CAPSIZE GetCapSize() { return size; }
	void SetCapSize(CAPSIZE size=NCap) { this->size = size; }
	virtual void Getdescribe() = 0;
	virtual float cost() = 0;
	float ExtralCost() {
		float cost = 0.0;
		switch (size) {
		case TCap:
			cost = 1.0;
			break;
		case NCap:
			cost = 1.5;
			break;
		case VCap:
			cost = 2.0;
			break;
		default:
			break;
		}
		return cost;
	}
protected:
	CAPSIZE  size;
};

class HouseCoofe :public CoffeBase{
public:
	void Getdescribe() override { std::cout << "HoseCoffe coffe "; }
	float cost() override { return 12.7; }
};

class Espresso :public CoffeBase {
public:
	void Getdescribe() override { std::cout << "Espresso coffe "; }
	float cost() override { return 13.2; }
};

class Condiment :public CoffeBase {
public:
	Condiment( CoffeBase *coffe):base (coffe) { }
protected:
	
	CoffeBase *base;
};

class Milk :public Condiment {
public:
	Milk(CoffeBase *coffe):Condiment(coffe) {}
	void Getdescribe() override { base->Getdescribe(); std::cout << " add Milk "; }
	float cost() override { return 2.5 + base->cost()+base->ExtralCost(); }
};

class Mocha :public Condiment {
public:
	Mocha(CoffeBase *coffe) :Condiment(coffe) {}
	void Getdescribe() override { base->Getdescribe(); std::cout << " add Mocha "; }
	float cost() override { return 3.6 + base->cost() + base->ExtralCost(); }
};


int main()
{
	Weather wea;
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
