#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
// ��������ַ�������
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 15
#define STUDENT_ID_LENGTH 8
#define MAX_CREDIT 8

// �ض��ַ������ڶ�ȡ���
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

// ѧҵ�ɼ��ṹ��
typedef struct AcademicScoreNode {
    char courseName[MAX_NAME_LENGTH];
    float score;    // ����
    float credit; // ѧ��
    float gpa; // ���ſγ̼���
    struct AcademicScoreNode* next;
} AcademicScoreNode;

// ��ѧ�����´�ҵ�ƻ���Ŀ�ṹ��
typedef struct InnovationProject {
    char projectName[MAX_NAME_LENGTH]; // ��Ŀ����
    float gpa; // �ӷ�ֵ
    int isLeaderOrSecondLeader;// �Ƿ�Ϊ��Ŀ������,�Ƿ�Ϊ�ڶ������ˣ����Ҽ����������Ŀ�����˼�0.1 GPA���ڶ�����0.05 GPA
    char projectLevel[5];// ��Ŀ���𣬹��Ҽ���ʡ����У��
    int isFinished;    // �Ƿ����
} InnovationProject;

// ѧ�����Ľṹ��
typedef struct AcademicPaper {
    char title[MAX_NAME_LENGTH]; // ���ı���
    char journalName[MAX_NAME_LENGTH]; // �ڿ�����
    int isFirstAuthor; // �Ƿ�Ϊ��һ����

    //�ڿ����𣬶�����0.4��һ���ڿ���0.2 GPA�������ڿ���0.1 GPA�������ڿ���0.05 GPA���ļ��ڿ���0.02 GPA���弶�ڿ���0.01 GPA
    int journalLevel;

    float gpa; // �ӷ�ֵ
    struct AcademicPaper* next;
} AcademicPaper;

// �������ѧ�ƾ����ṹ��
typedef struct Competition {
    char competitionName[MAX_NAME_LENGTH]; // ��������
    int teamSize;   //������������
    char competitionLevel[5]; // ��������,���Ҽ���ʡ����У��
    int rank;   // �񽱵ȼ���1��ʾһ�Ƚ���2��ʾ���Ƚ���3��ʾ���Ƚ�
    char competitionType;   //�������A�࣬B�࣬C��
    float gpa; // �ӷ�ֵ
    struct Competition* next;
} Competition;

// ѧ����Ϣ�ṹ��
typedef struct StudentInfo {
    char studentID[STUDENT_ID_LENGTH + 1];// ѧ��
    char name[MAX_NAME_LENGTH];// ����
    char password[MAX_PASSWORD_LENGTH + 2];// ����
    int classNumber;// �༶
    int grade;      //�꼶����һ����������������ģ�
    float gpa;  // ѧҵGPA
    float totalCredit;// ��ѧ��
    float qualityGpa;// ���ʼӷ�GPA
    float averageScore;// ��Ȩƽ����
    float totalGPA;// �ܼ���
    AcademicScoreNode* academicScores;// ѧҵ�ɼ�
    InnovationProject* innovationProjects;// ��ѧ�����´�ҵ�ƻ���Ŀ
    AcademicPaper* academicPapers;// ѧ������
    Competition* competitions;// �������ѧ�ƾ���
    struct StudentInfo* next;// ָ����һ��ѧ����ָ��
} StudentInfo;

// ����Ա��Ϣ�ṹ��
typedef struct AdminInfo {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    struct AdminInfo* next;
} AdminInfo;


// ��������
void loginSystem();//��¼ϵͳ
void studentLogin();//ѧ����¼
void adminLogin();//����Ա��¼
void addStudentAccount();//���ѧ���˺�
void addCourse(StudentInfo* student);//��ӿγ�
void addQualityProject(StudentInfo* student);//������ʼӷ���Ŀ
void modifyScoreMenu();//�޸ĳɼ���ɾ��ѧ��ҳ��
void modifyAcademicScore(StudentInfo* student);//�޸�ѧҵ�ɼ�
void modifyQualityScore(StudentInfo* student);//�޸����ʼӷ�
void sortStudentsMenu();//����ѧ��ҳ��
void saveToFile();//���浽�ļ�
void loadFromFile();//���ļ�����
void displayStudentInfo(StudentInfo* student);//��ʾѧ����Ϣ�ſ�
void displayAcademicScore(StudentInfo* student);//��ʾ��ѧ��ȫ��ѧҵ�ɼ�
void displayQualityScore(StudentInfo* student);//��ʾ��ѧ��ȫ�����ʼӷ�
void displayAdminMenu(AdminInfo* admin);//��ʾ����Ա�˵�
void displaySelfMenu(StudentInfo* student);//ѧ���Լ���ʾ�˵�
void freeMemory(StudentInfo** head);//�ͷ��ڴ�
void freeAdminMemory(AdminInfo** head);//�ͷŹ���Ա�ڴ�
StudentInfo* createStudent();//������ѧ���ڵ�
StudentInfo* findStudentByID(const char* studentID);//����ѧ��
AdminInfo* findAdminByUsername(const char* username);//���ҹ���Ա
AcademicScoreNode* createAcademicScore();//������ѧҵ�ɼ��ڵ�
InnovationProject* createInnovationProject();//�����´�ѧ�����´�ҵ�ƻ���Ŀ�ڵ�
AcademicPaper* createAcademicPaper();//������ѧ�����Ľڵ�
Competition* createCompetition();//�����¼������ѧ�ƾ����ڵ�
void insertAcademicScore(StudentInfo* student, AcademicScoreNode* scoreNode);//����ѧҵ�ɼ�����
void insertInnovationProject(StudentInfo* student, InnovationProject* project);//�����ѧ�����´�ҵ�ƻ���Ŀ����β
void insertAcademicPaper(StudentInfo* student, AcademicPaper* paper);//����ѧ����������β
void insertCompetition(StudentInfo* student, Competition* competition);//����������ѧ�ƾ�������β
void insertStudent(StudentInfo** head, StudentInfo* newStudent);//����ѧ������ͷ
void calculateAcademics(StudentInfo* student);//����GPA����ѧ�֡���Ȩƽ���֡��ܼ���
float calculateSingleGPA(const float* score);//���㵥�ſγ̼���
void deleteStudentRecord(StudentInfo** head, char* studentID);//ɾ��ѧ����¼
void handleInputError(const char* message);//�����������
void displayAllStudents(StudentInfo* head);//��ʾ����ѧ����Ϣ�ſ�
void displayByClass(StudentInfo* head);//���༶��ʾѧ����Ϣ
void displayByGrade(StudentInfo* head);//���꼶��ʾѧ����Ϣ
void sortList(StudentInfo** headref, int (*compare)(const StudentInfo*, const StudentInfo*), int l);//����ѧ������
void sortList_admin(AdminInfo** headRef, int (*compare)(const AdminInfo*, const AdminInfo*), int l);//�������Ա����
int compareByStudentID(const StudentInfo* a, const StudentInfo* b);//��ѧ������
int compareByGPA(const StudentInfo* a, const StudentInfo* b);//��ѧҵGPA����
int compareByAdminID(const AdminInfo* a, const AdminInfo* b);//������Ա�˺���������
int compareByAdminID_inv(const AdminInfo* a, const AdminInfo* b);//������Ա�˺���������
int compareByAverageScore(const StudentInfo* a, const StudentInfo* b);//����Ȩƽ��������
int compareByTotalGPA(const StudentInfo* a, const StudentInfo* b);//���ܼ�������
void addAdminAccount();//��ӹ���Ա�˺�
float calculatePaperGPA(AcademicPaper* paper);//����ѧ�����ļӷ�
float calculateCompetitionGPA(Competition* competition);//����������ѧ�ƾ����ӷ�
float calculateInnovationProjectGPA(InnovationProject* project);//�����ѧ�����´�ҵ�ƻ���Ŀ�ӷ�
void calculateQualityGPA(StudentInfo* student);//�������ʼӷ�GPA
void displayInnovationProjects(StudentInfo* student);//��ʾ��ѧ�����´�ҵ�ƻ���Ŀ
void displayAcademicPapers(StudentInfo* student);//��ʾѧ������
void displayCompetitions(StudentInfo* student);//��ʾ�������ѧ�ƾ���
void modifyInnovationProject(StudentInfo* student);//�޸Ĵ�ѧ�����´�ҵ�ƻ���Ŀ
void modifyAcademicPaper(StudentInfo* student);//�޸�ѧ������
void modifyCompetition(StudentInfo* student);//�޸ļ������ѧ�ƾ���
void deleteInnovationProject(StudentInfo* student);//ɾ����ѧ�����´�ҵ�ƻ���Ŀ
void deleteAcademicPaper(StudentInfo* student);//ɾ��ѧ������
void deleteCompetition(StudentInfo* student);//ɾ���������ѧ�ƾ���
void displayStudentMenu();//��ʾѧ���Ĳ˵�
void sortByGrade(StudentInfo** head);//���꼶����
void sortByClass(StudentInfo** head);//���༶����
int isStudentIDValid(const char* studentID);//�ж�ѧ���Ƿ�Ϸ�
int isGradeValid(int grade);//�ж��꼶�Ƿ�Ϸ�
int isClassValid(int classNumber);//�жϰ༶�Ƿ�Ϸ�
int isScoreValid(float score);//�жϷ����Ƿ�Ϸ�
int isPasswordValid(const char* password);//�ж������Ƿ�Ϸ�
int isDigit(char c);//�ж��Ƿ�Ϊ����
int isCreditValid(float credit);//�ж�ѧ���Ƿ�Ϸ�
int isCompetitionLevelValid(const char* competitionLevel);//�жϾ��������Ƿ�Ϸ�
int isCompetitionTypeValid(char competitionType);//�жϾ�������Ƿ�Ϸ�
int isProjectLevelValid(const char* projectLevel);//�ж���Ŀ�����Ƿ�Ϸ�
int isRankValid(int rank);//�жϻ񽱵ȼ��Ƿ�Ϸ�
int isLeaderOrSecondLeaderValid(int isLeaderOrSecondLeader);//�ж��Ƿ�Ϊ�������Ƿ�Ϸ�
void calculateJournalLevel(AcademicPaper* paper);//����ѧ�������ڿ�����
void freeTmpMemory(StudentInfo** head);//�ͷ���ʱѧҵ�ɼ��ڴ�
void displayRank(StudentInfo* student);//ѧ���鿴�꼶���༶����
void displayClassRank(StudentInfo* student);//ѧ���鿴�༶����
void displayGradeRank(StudentInfo* student);//ѧ���鿴�꼶����
int compareByQualityGPA(const StudentInfo* a, const StudentInfo* b);//�����ʼӷ�GPA����
void displayAllQualityProjects(StudentInfo* head);//��ʾ����ѧ�������ʼӷ���Ŀ

extern StudentInfo* studentsList;
extern AdminInfo* adminsList;
extern int count;//��¼����������
extern int isSaved;//��¼�Ƿ񱣴浽�ļ�