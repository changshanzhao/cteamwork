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
//    char projectName[MAX_NAME_LENGTH]; // 项目名称
//    float gpa; // 加分值
//    int isLeaderOrSecondLeader;// 是否为项目负责人,是否为第二负责人，国家级优秀结题项目负责人加0.1 GPA，第二名加0.05 GPA
//    char projectLevel[5];// 项目级别，国家级，省级，校级
//    int isFinished;    // 是否结题
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
void sortByScore(Manager M);									// 按总分排序
const struct StudentInfo* getStudent(int index, Manager M);			// 获取学生数据
void setStudent(int index, const struct StudentInfo* student, Manager M);	// 修改学生
void deleteStudent(int index, Manager M);						// 删除学生
int sizeofList_stu(StudentInfo* studentList);
int sizeofList_admin(AdminInfo* adminList);
int size(Manager M);// 学生数量
int searchName(char* searchTerms, Manager M);		// 按姓名搜索学生
int searchId(char* id, Manager M);							// 按学号搜索学生
void clear(Manager* M);	// 清空所有学生
int calculatelen(StudentInfo** head);


