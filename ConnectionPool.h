#pragma once
#include<iostream>
#include<string>
#include<queue>
#include"Connection.h"
#include<mutex>
#include<atomic>
#include<thread>
#include<memory>
#include<functional>
#include<condition_variable>
using namespace std;


class ConnectionPool
{
public:
	static ConnectionPool* getConnnectionPool();

	shared_ptr<Connection> getConnection();

private:
	ConnectionPool();

	// �������ļ��м���������
	bool loadConfigFile();

	// �����ڶ������߳��У�ר�Ÿ�������������
	void produceConnectionTask();


	string _ip; // mysql��ip��ַ
	unsigned short _port; // mysql�Ķ˿ں� 3306
	string _username; // mysql��¼�û���
	string _password; // mysql��¼����
	string _dbname; // ���ӵ����ݿ�����
	int _initSize; // ���ӳصĳ�ʼ������
	int _maxSize; // ���ӳص����������
	int _maxIdleTime; // ���ӳ�������ʱ��
	int _connectionTimeout; // ���ӳػ�ȡ���ӵĳ�ʱʱ��

	queue<Connection*> _connectionQue; // �洢mysql���ӵĶ���
	mutex _queueMutex; // ά�����Ӷ��е��̰߳�ȫ������
	
	// ɨ�賬��maxIdleTimeʱ��Ŀ������ӣ����ж��ڵ����ӻ���
	void scannerConnectionTask();


	atomic_int _connectionCnt; /// ��¼������������connection���ӵ�������
	condition_variable cv; // ���������������������������̺߳����������̵߳�ͨ��
	  
};

