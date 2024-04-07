#pragma once

#include "Student.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
struct Manager {
	std::vector<Student> students;						// 学生数据
};
bool read(const std::string& fileName, Manager* M);				// 读取文件到数据
void write(const std::string& fileName, Manager* M);		// 写入数据到文件
void addStudent(const Student& student, Manager* M);			// 添加学生
void sortById(Manager* M);									// 按学号排序
void sortByScore(Manager* M);									// 按总分排序
const Student& getStudent(int index, Manager* M);			// 获取学生数据
void setStudent(int index, const Student& student, Manager* M);	// 修改学生
void deleteStudent(int index, Manager* M);						// 删除学生
int size(Manager* M);									// 学生数量
int searchName(const wchar_t* searchTerms, Manager* M);		// 按姓名搜索学生
int searchId(int id, Manager* M);							// 按学号搜索学生
void clear(Manager* M);										// 清空所有学生


