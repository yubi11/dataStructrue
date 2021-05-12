// HashTable.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


template <typename T >
class HashTable {
public:
	class Node {
		T key;
		string value;
		public:
			Node() {};

			Node(T key, string value) :key(key), value(value) {};
	
			T getKey() {
				return key;
			}
			string getValue() {
				return value;
			}
	};

	vector<Node*> list[5];


HashTable(int size=5) {
	list->resize(size);
}

	int convertKey (const T& key) const{
		int converted=0;
		for (char character : key) {
			converted = character + converted;
		}
		return converted;
	}

	int convertIndex(const int& key) const{
		int index = key % (sizeof(list)/sizeof(vector<Node*>));
		return index;
	}



	string searchData(const T& key) const{
		int newKey = convertKey(key);
		int Index = convertIndex(newKey);

		for (Node* Data : list[Index]) {
			if (Data->getKey() == key) {
				return Data->getValue();
			}
		};
		return "찾는 값이 없습니다";
	}

	
	void put(T key, string value){
		int newKey=convertKey(key);
		int Index = convertIndex(newKey);
		list[Index].push_back(new Node(key,value));
	}

	

};











int main()
{
	HashTable<string> *tester = new HashTable<string>();

	tester->put("HyoHoon","is genius");
	cout<<tester->searchData("HyoHoon");
	tester->put("myeongcheol", "is byeongsin");
	cout << tester->searchData("myeongcheol");


}
