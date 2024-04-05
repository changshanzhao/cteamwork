#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100000

// ѧҵ�ɼ��ṹ��
typedef struct AcademicScoreNode {
    char courseName[MAX_NAME_LENGTH];
    float score;    // ����
    float credit; // ѧ��
    float gpa; // ���ſγ̼���
    struct AcademicScoreNode* next;
} AcademicScoreNode;

// �ۺ����ʼӷֽṹ��
typedef struct QualityScoreNode {
    char projectTitle[MAX_NAME_LENGTH];
    float gpaContribution; // �ӷ�
    struct QualityScoreNode* next;
} QualityScoreNode;

// ѧ����Ϣ�ṹ��
typedef struct StudentInfo {
    char studentID[8];// ѧ��
    char name[15];// ����
    char password[15];// ����
    int classNumber;// �༶
    AcademicScoreNode* academicScores;// ѧҵ�ɼ�
    QualityScoreNode* qualityScores;// ���ʼӷ���Ŀ
    float gpa;  // ѧҵGPA
    float totalCredit;// ��ѧ��
    float qualityGpa;// ���ʼӷ�GPA
    float averageScore;// ��Ȩƽ����
    float totalGPA;// �ܼ���
    struct StudentInfo* next;// ָ����һ��ѧ����ָ��
} StudentInfo;

// ����Ա��Ϣ�ṹ��
typedef struct AdminInfo {
    char username[15];
    char password[15];
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
void displayAdminMenu();//��ʾ����Ա�˵�
void displayStudentMenu();//��ʾѧ���˵�
void freeMemory(StudentInfo** head);//�ͷ��ڴ�
void freeAdminMemory(AdminInfo** head);//�ͷŹ���Ա�ڴ�
StudentInfo* createStudent();//������ѧ���ڵ�
StudentInfo* findStudentByID(const char* studentID);//����ѧ��
AdminInfo* findAdminByUsername(const char* username);//���ҹ���Ա
AcademicScoreNode* createAcademicScore();//������ѧҵ�ɼ��ڵ�
QualityScoreNode* createQualityScore();//���������ʼӷֽڵ�
void insertAcademicScore(StudentInfo* student, AcademicScoreNode* scoreNode);//����ѧҵ�ɼ�����β
void insertQualityScore(StudentInfo* student, QualityScoreNode* scoreNode);//�������ʼӷ�����β
void insertStudent(StudentInfo** head, StudentInfo* newStudent);//����ѧ������ͷ
void calculateGPA(StudentInfo* student);//����GPA����ѧ�֡���Ȩƽ���֡��ܼ���
float calculateSingleGPA(const float* score);//���㵥�ſγ̼���
void deleteStudentRecord(StudentInfo** head, char* studentID);//ɾ��ѧ����¼
void handleInputError(const char* message);//�����������
void displayAllStudent(StudentInfo* head);//��ʾ����ѧ����Ϣ�ſ�
void sortList(StudentInfo** head, int (*compare)(const StudentInfo*, const StudentInfo*));//����ѧ������
int compareByStudentID(const StudentInfo* a, const StudentInfo* b);//��ѧ������
int compareByGPA(const StudentInfo* a, const StudentInfo* b);//��ѧҵGPA����
int compareByAverageScore(const StudentInfo* a, const StudentInfo* b);//����Ȩƽ��������
int compareByTotalGPA(const StudentInfo* a, const StudentInfo* b);//���ܼ�������
void addAdminAccount();//��ӹ���Ա�˺�
