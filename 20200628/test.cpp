#include <iostream>
using namespace std;

//class Person {
//public:
//	virtual void BuyTicket() {
//		cout << "全价票" << endl;
//	}
//};
//class Student :public Person {
//public:
//	virtual void BuyTicket() {
//		cout << "半价票" << endl;
//	}
//};
//
//void func(Person& p) {
//	p.BuyTicket();
//}
//
//void test() {
//	Person p;
//	Student s;
//	func(p);
//	func(s);
//}

//class A {
//
//};
//class B :public A {
//
//};
//
//class Person {
//public:
//	virtual A* BuyTicket() {
//		cout << "全价票" << endl;
//		return new A;
//	}
//	/*virtual A& BuyTicket() {
//		cout << "全价票" << endl;
//		return A();
//	}*/
//};
//class Student : public Person {
//public:
//	virtual B* BuyTicket() {
//		cout << "半价票" << endl;
//		return  new B;
//	}
//	//virtual B& BuyTicket() {
//	//	cout << "半价票" << endl;
//	//	return B;
//	//}
//};

//class Person {
//public:
//	virtual ~Person() {
//		cout << "~Person" << endl;
//	}
//};
//class Student : public Person {
//public:
//	virtual ~Student() {
//		cout << "~Student" << endl;
//	}
//};
//void test() {
//	Person* str1 = new Person;
//	Person* str2 = new Student;
//	delete str1;
//	delete str2;
//
//}

//class Car {
//public:
//	virtual void Drive() final{
//		cout << " 1 " << endl;
//	}
//};
//class Benz : public Car {
//public:
//	virtual void Drive() { //报错:无法重写"final"函数
//		cout << " 2 " << endl;
//	}
//};

//void func(Car c) {
//	c.Drive();
//}
//void test() {
//	Car c;
//	Benz b;
//	func(c);
//	func(b);
//}

//class Car {
//public:
//	virtual void Drive() {
//		cout << " 1 " << endl;
//	}
//};
//class Benz : public Car {
//public:
//	virtual void Drive() override{
//		cout << " 2 " << endl;
//	}
//};

//class Car {
//public:
//	virtual void Drive() = 0; // 纯虚函数
//};
//class  BMW :public Car {
//	virtual void Drive() {
//		cout << " 舒适 " << endl;
//	}
//};
//void test() {
//	Car c; //抽象类:不能实例化对象
//	BMW b; // 重写纯虚函数后,可以实例化对象
//}

//class Base {
//public:
//	virtual void func() {
//		cout << "1" << endl;
//	}
//};
//class Drive : public Base {
//public:
//	virtual void func() {
//		cout << "2" << endl;
//	}
//};
//void test() {
//	Base b;
//	Drive d;
//
//	Base& ra = b;
//	Base& rb = d;
//
//	ra.func();
//	rb.func();
//}
//void test() {
//	Base b;
//	cout << sizeof(b) << endl; //sizeof(b)=4
//}

class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1;
};
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2;
};
	
class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};


//定义 函数指针:void 函数()
typedef void(*vfPtr)();

void doVF(vfPtr* vftable) {
	cout << "虚表地址:" << vftable << endl;
	for (int i = 0; vftable[i] != nullptr; ++i) {
		vfPtr func = vftable[i];
		func();
	}
}

void test() {
	Base1 b1;
	Base2 b2;
	Derive d;

	cout << "Base1:" << &b1 << endl;
    vfPtr* vftable = (vfPtr*)(*((int*)&b1));
	doVF(vftable);

	cout << "Base2:" << &b2 << endl;
    vftable = (vfPtr*)(*((int*)&b2));
	doVF(vftable);     
	//访问Derive的第一个虚表:地址偏移
	cout << "Derive first vftable:" << &d << endl;
	vftable = (vfPtr*)(*((int*)&d));
	doVF(vftable);
	//访问Derive的第二个虚表:地址偏移
	cout << "Derive second vftable:" << (int*)((char*)&d + sizeof(Base1))<<endl;
	vftable = (vfPtr*)(*((int*)((char*)&d+sizeof(Base1))));
	doVF(vftable);
}


int main() {
	test();
	return 0;
}