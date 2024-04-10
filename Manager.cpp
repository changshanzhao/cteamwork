#include "Manager.h"
#include<string.h>
#include<stdbool.h>
#include"Window.h"


int calculatelen(StudentInfo** head)
{
    return 0;
}


// ���ļ�����
void loadFromFile_all(Manager* M) {
    FILE* file = fopen("student.txt", "r");
    if (file == NULL) {
        handleInputError("���ļ�ʧ��");
        return;
    }

    freeMemory(&M->students); // ���ѧ������

    char buffer[MAX_NAME_LENGTH];// ���ڴ洢��ȡ��ÿ������
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, STUDENT_START, strlen(STUDENT_START)) == 0) {
            // �����µ�ѧ���ڵ�
            StudentInfo* newStudent = (StudentInfo*)malloc(sizeof(StudentInfo));
            if (newStudent == NULL) {
                handleInputError("�ڴ����ʧ��");
                break;
            }
            memset(newStudent, 0, sizeof(StudentInfo));
            newStudent->next = NULL;
            newStudent->academicScores = NULL;
            newStudent->innovationProjects = NULL;
            newStudent->academicPapers = NULL;
            newStudent->competitions = NULL;

            // ��ȡѧ��������Ϣ
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "StudentID: %s", newStudent->studentID);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Name: %s", newStudent->name);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Password: %s", newStudent->password);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Grade: %d", &newStudent->grade);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "ClassNumber: %d", &newStudent->classNumber);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "GPA: %f", &newStudent->gpa);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "TotalCredit: %2f", &newStudent->totalCredit);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "QualityGPA: %f", &newStudent->qualityGpa);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "AverageScore: %f", &newStudent->averageScore);
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "TotalGPA: %f", &newStudent->totalGPA);

            // ���½ڵ���ӵ�ѧ��������
            insertStudent(&M->students, newStudent);
            while (fgets(buffer, sizeof(buffer), file))
            {
                // ��ȡѧҵ�ɼ�����������##ScoreStart##ʱ��ʼ�ɼ�¼�룬����##ScoreEnd##ʱ����
                if (strncmp(buffer, SCORE_START, strlen(SCORE_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, SCORE_END, strlen(SCORE_END)) != 0) {
                        AcademicScoreNode* newScore = (AcademicScoreNode*)malloc(sizeof(AcademicScoreNode));
                        if (newScore == NULL) {
                            handleInputError("�ڴ����ʧ��");
                            break;
                        }
                        memset(newScore, 0, sizeof(AcademicScoreNode));
                        //fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "CourseName: %s", newScore->courseName);

                        fgets(buffer, sizeof(buffer), file);

                        sscanf(buffer, "Score: %f", &newScore->score);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "Credit: %f", &newScore->credit);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "GPA: %f", &newScore->gpa);
                        insertAcademicScore(newStudent, newScore);
                    }
                }
                // ��ȡ��ѧ�����´�ҵ�ƻ���Ŀ����
                if (strncmp(buffer, PROJECT_START, strlen(PROJECT_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PROJECT_END, strlen(PROJECT_END)) != 0) {
                        InnovationProject* newProject = (InnovationProject*)malloc(sizeof(InnovationProject));
                        if (newProject == NULL) {
                            handleInputError("�ڴ����ʧ��");
                            break;
                        }
                        memset(newProject, 0, sizeof(InnovationProject));
                        //fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "ProjectName: %s", newProject->projectName);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "GPA: %f", &newProject->gpa);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "LeaderOrSecondLeader: %d", &newProject->isLeaderOrSecondLeader);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "ProjectLevel: %s", newProject->projectLevel);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "IsFinished: %d", &newProject->isFinished);
                        insertInnovationProject(newStudent, newProject);
                    }
                }

                // ��ȡѧ����������
                if (strncmp(buffer, PAPER_START, strlen(PAPER_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PAPER_END, strlen(PAPER_END)) != 0) {
                        AcademicPaper* newPaper = (AcademicPaper*)malloc(sizeof(AcademicPaper));
                        if (newPaper == NULL) {
                            handleInputError("�ڴ����ʧ��");
                            break;
                        }
                        memset(newPaper, 0, sizeof(AcademicPaper));
                        //fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "Title: %s", newPaper->title);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "JournalName: %s", newPaper->journalName);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "IsFirstAuthor: %d", &newPaper->isFirstAuthor);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "JournalLevel: %d", &newPaper->journalLevel);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "GPA: %f", &newPaper->gpa);
                        insertAcademicPaper(newStudent, newPaper);
                    }
                }

                // ��ȡ�������ѧ�ƾ�������
                if (strncmp(buffer, COMPETITION_START, strlen(COMPETITION_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, COMPETITION_END, strlen(COMPETITION_END)) != 0) {
                        Competition* newCompetition = (Competition*)malloc(sizeof(Competition));
                        if (newCompetition == NULL) {
                            handleInputError("�ڴ����ʧ��");
                            break;
                        }
                        memset(newCompetition, 0, sizeof(Competition));
                        //fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "CompetitionName: %s", newCompetition->competitionName);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "TeamSize: %d", &newCompetition->teamSize);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "CompetitionLevel: %s", newCompetition->competitionLevel);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "Rank: %d", &newCompetition->rank);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "CompetitionType: %c", &newCompetition->competitionType);
                        fgets(buffer, sizeof(buffer), file);
                        sscanf(buffer, "GPA: %f", &newCompetition->gpa);
                        insertCompetition(newStudent, newCompetition);
                    }
                }
                if (strncmp(buffer, STUDENT_END, strlen(STUDENT_END)) == 0) {
                    break;
                }
            }
        }
    }
    fclose(file); // �ر��ļ�

    // ���ع���Ա��Ϣ
    FILE* adminFile = fopen("admin.txt", "r");
    if (adminFile == NULL) {
        handleInputError("���ļ�ʧ��");
        return;
    }
    //freeAdminMemory(&adminsList); // ��չ���Ա����

    while (fgets(buffer, sizeof(buffer), adminFile)) {
        if (strncmp(buffer, ADMIN_START, strlen(ADMIN_START)) == 0) {
            AdminInfo* newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo));
            if (newAdmin == NULL) {
                handleInputError("�ڴ����ʧ��");
                break;
            }
            memset(newAdmin, 0, sizeof(AdminInfo));
            fgets(buffer, sizeof(buffer), adminFile);
            sscanf(buffer, "Username: %s", newAdmin->username);
            fgets(buffer, sizeof(buffer), adminFile);
            sscanf(buffer, "Password: %s", newAdmin->password);
            newAdmin->next = M->admins;
            M->admins = newAdmin;
        }
    }
    fclose(adminFile); // �ر��ļ�
}

//void loadFromFile_all(Manager* M) {
//    FILE* file = fopen("student.txt", "r");
//    if (file == NULL) {
//        handleInputError("���ļ�ʧ��");
//        return;
//    }
//
//    freeMemory(&M->students); // ���ѧ������
//
//    char buffer[1024];// ���ڴ洢��ȡ��ÿ������
//    while (fgets(buffer, sizeof(buffer), file)) {
//        if (strncmp(buffer, STUDENT_START, strlen(STUDENT_START)) == 0) {
//            // �����µ�ѧ���ڵ�
//            StudentInfo* newStudent = (StudentInfo*)malloc(sizeof(StudentInfo));
//            if (newStudent == NULL) {
//                handleInputError("�ڴ����ʧ��");
//                break;
//            }
//            memset(newStudent, 0, sizeof(StudentInfo));
//         /*   newStudent->next = NULL;
//            newStudent->academicScores = NULL;
//            newStudent->innovationProjects = NULL;
//            newStudent->academicPapers = NULL;
//            newStudent->competitions = NULL;*/
//
//            // ��ȡѧ��������Ϣ
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "StudentID: %s", newStudent->studentID);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "Name: %s", newStudent->name);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "Password: %s", newStudent->password);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "Grade: %d", &newStudent->grade);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "ClassNumber: %d", &newStudent->classNumber);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "GPA: %f", &newStudent->gpa);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "TotalCredit: %2f", &newStudent->totalCredit);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "QualityGPA: %f", &newStudent->qualityGpa);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "AverageScore: %f", &newStudent->averageScore);
//            fgets(buffer, sizeof(buffer), file);
//            sscanf(buffer, "TotalGPA: %f", &newStudent->totalGPA);
//
//            // ���½ڵ���ӵ�ѧ��������
//            insertStudent(&M->students, newStudent);
//            // ��ȡѧҵ�ɼ�����������##ScoreStart##ʱ��ʼ�ɼ�¼�룬����##ScoreEnd##ʱ����
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, SCORE_START, strlen(SCORE_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, SCORE_END, strlen(SCORE_END)) != 0) {
//                    AcademicScoreNode* newScore = (AcademicScoreNode*)malloc(sizeof(AcademicScoreNode));
//                    if (newScore == NULL) {
//                        handleInputError("�ڴ����ʧ��");
//                        break;
//                    }
//                    memset(newScore, 0, sizeof(AcademicScoreNode));
//                    //fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "CourseName: %s", newScore->courseName);
//
//                    fgets(buffer, sizeof(buffer), file);
//
//                    sscanf(buffer, "Score: %f", &newScore->score);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "Credit: %f", &newScore->credit);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "GPA: %f", &newScore->gpa);
//                    insertAcademicScore(newStudent, newScore);
//                }
//            }
//            else {
//                //�����һ�У�����һ��
//                  fseek(file, -1*strlen(buffer), SEEK_CUR);
//               
//               
//            }
//
//            // ��ȡ��ѧ�����´�ҵ�ƻ���Ŀ����
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PROJECT_START, strlen(PROJECT_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PROJECT_END, strlen(PROJECT_END)) != 0) {
//                    InnovationProject* newProject = (InnovationProject*)malloc(sizeof(InnovationProject));
//                    if (newProject == NULL) {
//                        handleInputError("�ڴ����ʧ��");
//                        break;
//                    }
//                    memset(newProject, 0, sizeof(InnovationProject));
//                    //fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "ProjectName: %s", newProject->projectName);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "GPA: %f", &newProject->gpa);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "LeaderOrSecondLeader: %d", &newProject->isLeaderOrSecondLeader);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "ProjectLevel: %s", newProject->projectLevel);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "IsFinished: %d", &newProject->isFinished);
//                    insertInnovationProject(newStudent, newProject);
//                }
//            }
//            else {
//                //����һ��
//                fseek(file, -1*strlen(buffer), SEEK_CUR);
//              
//         
//            }
//
//
//            // ��ȡѧ����������
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PAPER_START, strlen(PAPER_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PAPER_END, strlen(PAPER_END)) != 0) {
//                    AcademicPaper* newPaper = (AcademicPaper*)malloc(sizeof(AcademicPaper));
//                    if (newPaper == NULL) {
//                        handleInputError("�ڴ����ʧ��");
//                        break;
//                    }
//                    memset(newPaper, 0, sizeof(AcademicPaper));
//                    //fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "Title: %s", newPaper->title);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "JournalName: %s", newPaper->journalName);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "IsFirstAuthor: %d", &newPaper->isFirstAuthor);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "JournalLevel: %d", &newPaper->journalLevel);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "GPA: %f", &newPaper->gpa);
//                    insertAcademicPaper(newStudent, newPaper);
//                }
//            }
//            else {
//                //����һ��
//                fseek(file, -1*strlen(buffer), SEEK_CUR);
//              
//               
//            }
//
//            // ��ȡ�������ѧ�ƾ�������
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, COMPETITION_START, strlen(COMPETITION_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, COMPETITION_END, strlen(COMPETITION_END)) != 0) {
//                    Competition* newCompetition = (Competition*)malloc(sizeof(Competition));
//                    if (newCompetition == NULL) {
//                        handleInputError("�ڴ����ʧ��");
//                        break;
//                    }
//                    memset(newCompetition, 0, sizeof(Competition));
//                    //fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "CompetitionName: %s", newCompetition->competitionName);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "TeamSize: %d", &newCompetition->teamSize);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "CompetitionLevel: %s", newCompetition->competitionLevel);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "Rank: %d", &newCompetition->rank);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "CompetitionType: %c", &newCompetition->competitionType);
//                    fgets(buffer, sizeof(buffer), file);
//                    sscanf(buffer, "GPA: %f", &newCompetition->gpa);
//                    insertCompetition(newStudent, newCompetition);
//                }
//            }
//            else {
//                //����һ��
//                fseek(file, -1*strlen(buffer), SEEK_CUR);
//            }
//            // ����ѧ����¼�������
//            fgets(buffer, sizeof(buffer), file);
//        }
//    }
//    fclose(file); // �ر��ļ�
//
//    // ���ع���Ա��Ϣ
//    FILE* adminFile = fopen("admin.txt", "r");
//    if (adminFile == NULL) {
//        handleInputError("���ļ�ʧ��");
//        return;
//    }
//    //freeAdminMemory(&adminsList); // ��չ���Ա����
//
//    while (fgets(buffer, sizeof(buffer), adminFile)) {
//        if (strncmp(buffer, ADMIN_START, strlen(ADMIN_START)) == 0) {
//            AdminInfo* newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo));
//            if (newAdmin == NULL) {
//                handleInputError("�ڴ����ʧ��");
//                break;
//            }
//            memset(newAdmin, 0, sizeof(AdminInfo));
//            fgets(buffer, sizeof(buffer), adminFile);
//            sscanf(buffer, "Username: %s", newAdmin->username);
//            fgets(buffer, sizeof(buffer), adminFile);
//            sscanf(buffer, "Password: %s", newAdmin->password);
//            newAdmin->next = M->admins;
//            M->admins = newAdmin;
//        }
//    }
//    fclose(adminFile); // �ر��ļ�
//}


int sizeofList_stu(StudentInfo* studentList)
{
    // TODO: �ڴ˴����� return ���
    int a = 0;
    StudentInfo* tmp = studentList;
    while (tmp != NULL)
    {
        a++;
        tmp = tmp->next;

    }
    return a;
}
int sizeofList_admin(AdminInfo* adminList)
{
    // TODO: �ڴ˴����� return ���
    int a = 0;
    AdminInfo* tmp = adminList;
    while (tmp != NULL)
    {
        a++;
        tmp = tmp->next;

    }
    return a;
}
int size(Manager M)
{
    // TODO: �ڴ˴����� return ���
    int a = 0;
    StudentInfo* tmp = M.students;
    while (tmp != NULL)
    {
        a++;
        tmp = tmp->next;

    }
    return a;
}

//int searchName(char* searchTerms, Manager M)
//{
//    // TODO: �ڴ˴����� return ���
//    std::vector<Student>::const_iterator iter;
//    iter = std::find(M.students.begin(), M.students.end(), searchTerms);
//    if (iter != M.students.end())
//    {
//        // �����ɹ�����������
//        return (int)(iter - M.students.begin());
//    }
//    else
//    {
//        // ����ʧ�ܣ����� -1 ��ʾ����
//        return -1;
//    }
//}


//int searchId(int id, Manager M)
//{
//    std::vector<Student>::const_iterator iter;
//    iter = std::find(M.students.begin(), M.students.end(), id);
//    if (iter != M.students.end())
//    {
//        // �����ɹ�����������
//        return (int)(iter - M.students.begin());
//    }
//    else
//    {
//        // ����ʧ�ܣ����� -1 ��ʾ����
//        return -1;
//    }
//}

//void clear(Manager* M)
//{
//    (M->students).clear();
//}
