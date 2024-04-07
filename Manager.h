#pragma once

#include "Student.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
struct Manager {
	std::vector<Student> students;						// ѧ������
};
bool read(const std::string& fileName, Manager* M);				// ��ȡ�ļ�������
void write(const std::string& fileName, Manager* M);		// д�����ݵ��ļ�
void addStudent(const Student& student, Manager* M);			// ���ѧ��
void sortById(Manager* M);									// ��ѧ������
void sortByScore(Manager* M);									// ���ܷ�����
const Student& getStudent(int index, Manager* M);			// ��ȡѧ������
void setStudent(int index, const Student& student, Manager* M);	// �޸�ѧ��
void deleteStudent(int index, Manager* M);						// ɾ��ѧ��
int size(Manager* M);									// ѧ������
int searchName(const wchar_t* searchTerms, Manager* M);		// ����������ѧ��
int searchId(int id, Manager* M);							// ��ѧ������ѧ��
void clear(Manager* M);										// �������ѧ��


