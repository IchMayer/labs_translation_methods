#pragma once

#include <vector>
#include <string>
#include <functional>

using namespace std;

class Hash
{
public:
	Hash();
	~Hash();

	struct Indint;
	struct Const;
	struct Struct;

	struct Tocken
	{
		int nTable;						//����� �������
		int nString;					//������ � ���-�������
		int nPos;						//������� � ���-�������

		operator bool();
	};

	struct Indint						//��������� � ���������������
	{
		string name;					//��� ���������������
		union
		{
			float f;
			int i;
		} value;
		int type;						//0 - int, 1 - float
		bool isInitialized;
		
		operator Hash::Const();
		operator Hash::Struct();
		operator bool();

		Indint(string name);			//�����������
	};

	struct Const						//��������� � ���������
	{
		string name;
		int type;
		int value;

		operator Hash::Indint();
		operator Hash::Struct();
		operator bool();
		Const(string name);				//�����������
	};
	//�������� ����� ����� ���� �������� ������ ���������������

	struct Struct
	{
		string name;					//�������� ���������
		int nInt;						//���������� ����� �����
		int nFloat;						//���������� ������������ �����
		vector<string> valueName;		//�������� ���������������� � ���������
		vector<int> valueI;				//������������ ������ ����� �����(����� ������ �������)
		vector<float> valueF;			//������������ ������ ������������ �����

		operator Hash::Indint();
		operator Hash::Const();
		operator bool();
		Struct(string name);
	};

	Tocken Find(string a);				//�����
	bool Push(string b);				//���������� �������� � ������������ �������

	template<class T>
	bool SetArg(Tocken tocken, T arg)					//���������� ����������
	{
		if (is_same<T, Hash::Indint>::value)
			return SetArgIndint(tocken, arg);
		if (is_same<T, Hash::Const>::value)
			return SetArgConst(tocken, arg);
		if (is_same<T, Hash::Struct>::value)
			return SetArgStruct(tocken, arg);

		return false;
	}

	template<class T>
	T GetArg(Tocken tocken)				//��������� ���������
	{
		if (is_same<T, Hash::Indint>::value)
			return GetArgIndint(tocken);
		if (is_same<T, Hash::Const>::value)
			return GetArgConst(tocken);
		if (is_same<T, Hash::Struct>::value)
			return GetArgStruct(tocken);

		return T(0);
	}

	void SetHeshFunc(function<int(string)> func);		//������� ���-�������

private:
	static const int Nkw = 10;			//���������� ����� � ���-������� �������� ����
	static const int No = 15;			//���������� ����� � ���-������� ��������
	static const int Nd = 10;			//���������� ����� � ���-������� ������������
	static const int Ni = 255;			//���������� ����� � ���-������� ����������������
	static const int Nc = 63;			//���������� ����� � ���-������� ��������
	static const int Ns = 15;			//���������� ����� � ���-������� ��������
	static const int n = 6;				//���������� ���-������

	enum Table
	{
		Keywords = 0,
		Operation = 1,
		Delimiters = 2,
		Indintificator = 3,
		Constant = 4,
		Structures = 5
	};

	bool SetArgIndint(Tocken tocken, Indint ind);		//���������� ���������� � ����������������
	bool SetArgConst(Tocken tocken, Const con);		//���������� ���������� � ��������
	bool SetArgStruct(Tocken tocken, Struct str);		//���������� ���������� � ��������

	Indint GetArgIndint(Tocken name);	//�������� ��������� � ���������������
	Const GetArgConst(Tocken name);		//�������� ��������� � ���������
	Struct GetArgStruct(Tocken name);	//�������� ��������� � ���������

	void Add(int nTable, string name);		//���������� �������� � �������
	Tocken Check(int nTable, string name);	//�������� ������� �������� � �������

	vector<string> keywords[Nkw];			//�������� �����
	vector<string> operation[No];			//����� ��������
	vector<string> delimiters[Nd];			//�����������
	vector<Indint> indintificator[Ni];		//��������������
	vector<Const> constant[Nc];				//���������
	vector<Struct> structures[Ns];			//���������

	function<int(string)> hashFunc;		//��� �������
};