#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
// 定义最大字符串长度
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 15
#define STUDENT_ID_LENGTH 8
#define MAX_CREDIT 8

// 特定字符串用于读取标记
#define STUDENT_START "##StudentStart##"
#define STUDENT_END "##StudentEnd##"
#define SCORE_START "##ScoreStart##"
#define SCORE_END "##ScoreEnd##"
#define PROJECT_START "##ProjectStart##"
#define PROJECT_END "##ProjectEnd##"
#define PAPER_START "##PaperStart##"
#define PAPER_END "##PaperEnd##"
#define COMPETITION_START "##CompetitionStart##"
#define COMPETITION_END "##CompetitionEnd##"
#define ADMIN_START "##AdminStart##"
#define ADMIN_END "##AdminEnd##"

// 学业成绩结构体
typedef struct AcademicScoreNode {
    char courseName[MAX_NAME_LENGTH];
    float score;    // 分数
    float credit; // 学分
    float gpa; // 单门课程绩点
    struct AcademicScoreNode* next;
} AcademicScoreNode;

// 大学生创新创业计划项目结构体
typedef struct InnovationProject {
    char projectName[MAX_NAME_LENGTH]; // 项目名称
    float gpa; // 加分值
    int isLeaderOrSecondLeader;// 是否为项目负责人,是否为第二负责人，国家级优秀结题项目负责人加0.1 GPA，第二名加0.05 GPA
    char projectLevel[5];// 项目级别，国家级，省级，校级
    int isFinished;    // 是否结题
} InnovationProject;

// 学术论文结构体
typedef struct AcademicPaper {
    char title[MAX_NAME_LENGTH]; // 论文标题
    char journalName[MAX_NAME_LENGTH]; // 期刊类名
    int isFirstAuthor; // 是否为第一作者

    //期刊级别，顶级加0.4，一级期刊加0.2 GPA，二级期刊加0.1 GPA，三级期刊加0.05 GPA，四级期刊加0.02 GPA，五级期刊加0.01 GPA
    int journalLevel;

    float gpa; // 加分值
    struct AcademicPaper* next;
} AcademicPaper;

// 计算机类学科竞赛结构体
typedef struct Competition {
    char competitionName[MAX_NAME_LENGTH]; // 竞赛名称
    int teamSize;   //参赛队伍人数
    char competitionLevel[5]; // 竞赛级别,国家级，省级，校级
    int rank;   // 获奖等级，1表示一等奖，2表示二等奖，3表示三等奖
    char competitionType;   //竞赛类别，A类，B类，C类
    float gpa; // 加分值
    struct Competition* next;
} Competition;

// 学生信息结构体
typedef struct StudentInfo {
    char studentID[STUDENT_ID_LENGTH + 1];// 学号
    char name[MAX_NAME_LENGTH];// 姓名
    char password[MAX_PASSWORD_LENGTH + 2];// 密码
    int classNumber;// 班级
    int grade;      //年级（大一、大二、大三、大四）
    float gpa;  // 学业GPA
    float totalCredit;// 总学分
    float qualityGpa;// 素质加分GPA
    float averageScore;// 加权平均分
    float totalGPA;// 总绩点
    AcademicScoreNode* academicScores;// 学业成绩
    InnovationProject* innovationProjects;// 大学生创新创业计划项目
    AcademicPaper* academicPapers;// 学术论文
    Competition* competitions;// 计算机类学科竞赛
    struct StudentInfo* next;// 指向下一个学生的指针
} StudentInfo;

// 管理员信息结构体
typedef struct AdminInfo {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
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
void displayAdminMenu(AdminInfo* admin);//显示管理员菜单
void displaySelfMenu(StudentInfo* student);//学生自己显示菜单
void freeMemory(StudentInfo** head);//释放内存
void freeAdminMemory(AdminInfo** head);//释放管理员内存
StudentInfo* createStudent();//创建新学生节点
StudentInfo* findStudentByID(const char* studentID);//查找学生
AdminInfo* findAdminByUsername(const char* username);//查找管理员
AcademicScoreNode* createAcademicScore();//创建新学业成绩节点
InnovationProject* createInnovationProject();//创建新大学生创新创业计划项目节点
AcademicPaper* createAcademicPaper();//创建新学术论文节点
Competition* createCompetition();//创建新计算机类学科竞赛节点
void insertAcademicScore(StudentInfo* student, AcademicScoreNode* scoreNode);//插入学业成绩链表
void insertInnovationProject(StudentInfo* student, InnovationProject* project);//插入大学生创新创业计划项目链表尾
void insertAcademicPaper(StudentInfo* student, AcademicPaper* paper);//插入学术论文链表尾
void insertCompetition(StudentInfo* student, Competition* competition);//插入计算机类学科竞赛链表尾
void insertStudent(StudentInfo** head, StudentInfo* newStudent);//插入学生链表头
void calculateAcademics(StudentInfo* student);//计算GPA、总学分、加权平均分、总绩点
float calculateSingleGPA(const float* score);//计算单门课程绩点
void deleteStudentRecord(StudentInfo** head, char* studentID);//删除学生记录
void handleInputError(const char* message);//处理输入错误
void displayAllStudents(StudentInfo* head);//显示所有学生信息概况
void displayByClass(StudentInfo* head);//按班级显示学生信息
void displayByGrade(StudentInfo* head);//按年级显示学生信息
void sortList(StudentInfo** headref, int (*compare)(const StudentInfo*, const StudentInfo*), int l);//排序学生链表
void sortList_admin(AdminInfo** headRef, int (*compare)(const AdminInfo*, const AdminInfo*), int l);//排序管理员链表
int compareByStudentID(const StudentInfo* a, const StudentInfo* b);//按学号排序
int compareByGPA(const StudentInfo* a, const StudentInfo* b);//按学业GPA排序
int compareByAdminID(const AdminInfo* a, const AdminInfo* b);//按管理员账号正序排序
int compareByAdminID_inv(const AdminInfo* a, const AdminInfo* b);//按管理员账号逆序排序
int compareByAverageScore(const StudentInfo* a, const StudentInfo* b);//按加权平均分排序
int compareByTotalGPA(const StudentInfo* a, const StudentInfo* b);//按总绩点排序
void addAdminAccount();//添加管理员账号
float calculatePaperGPA(AcademicPaper* paper);//计算学术论文加分
float calculateCompetitionGPA(Competition* competition);//计算计算机类学科竞赛加分
float calculateInnovationProjectGPA(InnovationProject* project);//计算大学生创新创业计划项目加分
void calculateQualityGPA(StudentInfo* student);//计算素质加分GPA
void displayInnovationProjects(StudentInfo* student);//显示大学生创新创业计划项目
void displayAcademicPapers(StudentInfo* student);//显示学术论文
void displayCompetitions(StudentInfo* student);//显示计算机类学科竞赛
void modifyInnovationProject(StudentInfo* student);//修改大学生创新创业计划项目
void modifyAcademicPaper(StudentInfo* student);//修改学术论文
void modifyCompetition(StudentInfo* student);//修改计算机类学科竞赛
void deleteInnovationProject(StudentInfo* student);//删除大学生创新创业计划项目
void deleteAcademicPaper(StudentInfo* student);//删除学术论文
void deleteCompetition(StudentInfo* student);//删除计算机类学科竞赛
void displayStudentMenu();//显示学生的菜单
void sortByGrade(StudentInfo** head);//按年级排序
void sortByClass(StudentInfo** head);//按班级排序
int isStudentIDValid(const char* studentID);//判断学号是否合法
int isGradeValid(int grade);//判断年级是否合法
int isClassValid(int classNumber);//判断班级是否合法
int isScoreValid(float score);//判断分数是否合法
int isPasswordValid(const char* password);//判断密码是否合法
int isDigit(char c);//判断是否为数字
int isCreditValid(float credit);//判断学分是否合法
int isCompetitionLevelValid(const char* competitionLevel);//判断竞赛级别是否合法
int isCompetitionTypeValid(char competitionType);//判断竞赛类别是否合法
int isProjectLevelValid(const char* projectLevel);//判断项目级别是否合法
int isRankValid(int rank);//判断获奖等级是否合法
int isLeaderOrSecondLeaderValid(int isLeaderOrSecondLeader);//判断是否为负责人是否合法
void calculateJournalLevel(AcademicPaper* paper);//计算学术论文期刊级别
void freeTmpMemory(StudentInfo** head);//释放临时学业成绩内存
void displayRank(StudentInfo* student);//学生查看年级、班级排名
void displayClassRank(StudentInfo* student);//学生查看班级排名
void displayGradeRank(StudentInfo* student);//学生查看年级排名
int compareByQualityGPA(const StudentInfo* a, const StudentInfo* b);//按素质加分GPA排序
void displayAllQualityProjects(StudentInfo* head);//显示所有学生的素质加分项目

extern StudentInfo* studentsList;
extern AdminInfo* adminsList;
extern int count;//记录密码错误次数
extern int isSaved;//记录是否保存到文件