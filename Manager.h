#pragma once

#include "function.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// typedef struct InnovationProject
//{
//
//    char projectName[MAX_NAME_LENGTH]; // ��Ŀ����
//    float gpa; // �ӷ�ֵ
//    int isLeaderOrSecondLeader;// �Ƿ�Ϊ��Ŀ������,�Ƿ�Ϊ�ڶ������ˣ����Ҽ����������Ŀ�����˼�0.1 GPA���ڶ�����0.05 GPA
//    char projectLevel[5];// ��Ŀ���𣬹��Ҽ���ʡ����У��
//    int isFinished;    // �Ƿ����
//
//    struct InnovationProject* next;
//
//}InnovationProject;


typedef struct {

    StudentInfo* students;
    AdminInfo* admins;
}Manager;

//StudentInfo* studentsList;
//AdminInfo* adminsList;

void loadFromFile_all(Manager* M);
void sortByScore(Manager M);									// ���ܷ�����
const struct StudentInfo* getStudent(int index, Manager M);			// ��ȡѧ������
void setStudent(int index, const struct StudentInfo* student, Manager M);	// �޸�ѧ��
void deleteStudent(int index, Manager M);						// ɾ��ѧ��
int sizeofList_stu(StudentInfo* studentList);
int sizeofList_admin(AdminInfo* adminList);
int size(Manager M);// ѧ������
int searchName(char* searchTerms, Manager M);		// ����������ѧ��
int searchId(char* id, Manager M);							// ��ѧ������ѧ��
void clear(Manager* M);	// �������ѧ��
int calculatelen(StudentInfo** head);


