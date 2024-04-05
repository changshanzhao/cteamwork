#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100000

// 学业成绩结构体
typedef struct AcademicScoreNode {
    char courseName[MAX_NAME_LENGTH];
    float score;    // 分数
    float credit; // 学分
    float gpa; // 单门课程绩点
    struct AcademicScoreNode* next;
} AcademicScoreNode;

// 综合素质加分结构体
typedef struct QualityScoreNode {
    char projectTitle[MAX_NAME_LENGTH];
    float gpaContribution; // 加分
    struct QualityScoreNode* next;
} QualityScoreNode;

// 学生信息结构体
typedef struct StudentInfo {
    char studentID[8];// 学号
    char name[15];// 姓名
    char password[15];// 密码
    int classNumber;// 班级
    AcademicScoreNode* academicScores;// 学业成绩
    QualityScoreNode* qualityScores;// 素质加分项目
    float gpa;  // 学业GPA
    float totalCredit;// 总学分
    float qualityGpa;// 素质加分GPA
    float averageScore;// 加权平均分
    float totalGPA;// 总绩点
    struct StudentInfo* next;// 指向下一个学生的指针
} StudentInfo;

// 管理员信息结构体
typedef struct AdminInfo {
    char username[15];
    char password[15];
    struct AdminInfo* next;
} AdminInfo;


// 函数声明
void loginSystem();//登录系统
void studentLogin();//学生登录
void adminLogin();//管理员登录
void addStudentAccount();//添加学生账号
void addCourse(StudentInfo* student);//添加课程
void addQualityProject(StudentInfo* student);//添加素质加分项目
void modifyScoreMenu();//修改成绩、删除学生页面
void modifyAcademicScore(StudentInfo* student);//修改学业成绩
void modifyQualityScore(StudentInfo* student);//修改素质加分
void sortStudentsMenu();//排序学生页面
void saveToFile();//保存到文件
void loadFromFile();//从文件加载
void displayStudentInfo(StudentInfo* student);//显示学生信息概况
void displayAcademicScore(StudentInfo* student);//显示该学生全部学业成绩
void displayQualityScore(StudentInfo* student);//显示该学生全部素质加分
void displayAdminMenu();//显示管理员菜单
void displayStudentMenu();//显示学生菜单
void freeMemory(StudentInfo** head);//释放内存
void freeAdminMemory(AdminInfo** head);//释放管理员内存
StudentInfo* createStudent();//创建新学生节点
StudentInfo* findStudentByID(const char* studentID);//查找学生
AdminInfo* findAdminByUsername(const char* username);//查找管理员
AcademicScoreNode* createAcademicScore();//创建新学业成绩节点
QualityScoreNode* createQualityScore();//创建新素质加分节点
void insertAcademicScore(StudentInfo* student, AcademicScoreNode* scoreNode);//插入学业成绩链表尾
void insertQualityScore(StudentInfo* student, QualityScoreNode* scoreNode);//插入素质加分链表尾
void insertStudent(StudentInfo** head, StudentInfo* newStudent);//插入学生链表头
void calculateGPA(StudentInfo* student);//计算GPA、总学分、加权平均分、总绩点
float calculateSingleGPA(const float* score);//计算单门课程绩点
void deleteStudentRecord(StudentInfo** head, char* studentID);//删除学生记录
void handleInputError(const char* message);//处理输入错误
void displayAllStudent(StudentInfo* head);//显示所有学生信息概况
void sortList(StudentInfo** head, int (*compare)(const StudentInfo*, const StudentInfo*));//排序学生链表
int compareByStudentID(const StudentInfo* a, const StudentInfo* b);//按学号排序
int compareByGPA(const StudentInfo* a, const StudentInfo* b);//按学业GPA排序
int compareByAverageScore(const StudentInfo* a, const StudentInfo* b);//按加权平均分排序
int compareByTotalGPA(const StudentInfo* a, const StudentInfo* b);//按总绩点排序
void addAdminAccount();//添加管理员账号
