//#include "iostream"
//using namespace std;
//
//class base {
//public:
//	base() {}
//	virtual ~base()
//	{
//		print(this);
//	}
//	void echo() {
//		cout << "echo base" << endl;
//	}
//	virtual void simple() {
//		cout << "simple base" << endl;
//	}
//	void print(base* pbase);
//};
//
//class derive :public base {
//public:
//	derive() {}
//	virtual ~derive() {
//		print(this);
//	}
//	void echo() {
//		cout << "echo derive" << endl;
//	}
//	virtual void simple() {
//		cout << "simple derive" << endl;
//	}
//
//};
//
//void base::print(base* pbase) {
//	pbase->echo();
//	pbase->simple();
//}
//
//
//int main() {
//	base *pb = new derive;
//	delete pb;
//}