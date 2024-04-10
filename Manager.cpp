#include "Manager.h"
#include<string.h>
#include<stdbool.h>
#include"Window.h"


int calculatelen(StudentInfo** head)
{
    return 0;
}


// 从文件加载
void loadFromFile_all(Manager* M) {
    FILE* file = fopen("student.txt", "r");
    if (file == NULL) {
        handleInputError("打开文件失败");
        return;
    }

    freeMemory(&M->students); // 清空学生链表

    char buffer[MAX_NAME_LENGTH];// 用于存储读取的每行数据
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, STUDENT_START, strlen(STUDENT_START)) == 0) {
            // 创建新的学生节点
            StudentInfo* newStudent = (StudentInfo*)malloc(sizeof(StudentInfo));
            if (newStudent == NULL) {
                handleInputError("内存分配失败");
                break;
            }
            memset(newStudent, 0, sizeof(StudentInfo));
            newStudent->next = NULL;
            newStudent->academicScores = NULL;
            newStudent->innovationProjects = NULL;
            newStudent->academicPapers = NULL;
            newStudent->competitions = NULL;

            // 读取学生个人信息
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

            // 将新节点添加到学生链表中
            insertStudent(&M->students, newStudent);
            while (fgets(buffer, sizeof(buffer), file))
            {
                // 读取学业成绩链表，当读到##ScoreStart##时开始成绩录入，读到##ScoreEnd##时结束
                if (strncmp(buffer, SCORE_START, strlen(SCORE_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, SCORE_END, strlen(SCORE_END)) != 0) {
                        AcademicScoreNode* newScore = (AcademicScoreNode*)malloc(sizeof(AcademicScoreNode));
                        if (newScore == NULL) {
                            handleInputError("内存分配失败");
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
                // 读取大学生创新创业计划项目链表
                if (strncmp(buffer, PROJECT_START, strlen(PROJECT_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PROJECT_END, strlen(PROJECT_END)) != 0) {
                        InnovationProject* newProject = (InnovationProject*)malloc(sizeof(InnovationProject));
                        if (newProject == NULL) {
                            handleInputError("内存分配失败");
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

                // 读取学术论文链表
                if (strncmp(buffer, PAPER_START, strlen(PAPER_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PAPER_END, strlen(PAPER_END)) != 0) {
                        AcademicPaper* newPaper = (AcademicPaper*)malloc(sizeof(AcademicPaper));
                        if (newPaper == NULL) {
                            handleInputError("内存分配失败");
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

                // 读取计算机类学科竞赛链表
                if (strncmp(buffer, COMPETITION_START, strlen(COMPETITION_START)) == 0) {
                    while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, COMPETITION_END, strlen(COMPETITION_END)) != 0) {
                        Competition* newCompetition = (Competition*)malloc(sizeof(Competition));
                        if (newCompetition == NULL) {
                            handleInputError("内存分配失败");
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
    fclose(file); // 关闭文件

    // 加载管理员信息
    FILE* adminFile = fopen("admin.txt", "r");
    if (adminFile == NULL) {
        handleInputError("打开文件失败");
        return;
    }
    //freeAdminMemory(&adminsList); // 清空管理员链表

    while (fgets(buffer, sizeof(buffer), adminFile)) {
        if (strncmp(buffer, ADMIN_START, strlen(ADMIN_START)) == 0) {
            AdminInfo* newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo));
            if (newAdmin == NULL) {
                handleInputError("内存分配失败");
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
    fclose(adminFile); // 关闭文件
}

//void loadFromFile_all(Manager* M) {
//    FILE* file = fopen("student.txt", "r");
//    if (file == NULL) {
//        handleInputError("打开文件失败");
//        return;
//    }
//
//    freeMemory(&M->students); // 清空学生链表
//
//    char buffer[1024];// 用于存储读取的每行数据
//    while (fgets(buffer, sizeof(buffer), file)) {
//        if (strncmp(buffer, STUDENT_START, strlen(STUDENT_START)) == 0) {
//            // 创建新的学生节点
//            StudentInfo* newStudent = (StudentInfo*)malloc(sizeof(StudentInfo));
//            if (newStudent == NULL) {
//                handleInputError("内存分配失败");
//                break;
//            }
//            memset(newStudent, 0, sizeof(StudentInfo));
//         /*   newStudent->next = NULL;
//            newStudent->academicScores = NULL;
//            newStudent->innovationProjects = NULL;
//            newStudent->academicPapers = NULL;
//            newStudent->competitions = NULL;*/
//
//            // 读取学生个人信息
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
//            // 将新节点添加到学生链表中
//            insertStudent(&M->students, newStudent);
//            // 读取学业成绩链表，当读到##ScoreStart##时开始成绩录入，读到##ScoreEnd##时结束
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, SCORE_START, strlen(SCORE_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, SCORE_END, strlen(SCORE_END)) != 0) {
//                    AcademicScoreNode* newScore = (AcademicScoreNode*)malloc(sizeof(AcademicScoreNode));
//                    if (newScore == NULL) {
//                        handleInputError("内存分配失败");
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
//                //多读了一行，回退一行
//                  fseek(file, -1*strlen(buffer), SEEK_CUR);
//               
//               
//            }
//
//            // 读取大学生创新创业计划项目链表
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PROJECT_START, strlen(PROJECT_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PROJECT_END, strlen(PROJECT_END)) != 0) {
//                    InnovationProject* newProject = (InnovationProject*)malloc(sizeof(InnovationProject));
//                    if (newProject == NULL) {
//                        handleInputError("内存分配失败");
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
//                //回退一行
//                fseek(file, -1*strlen(buffer), SEEK_CUR);
//              
//         
//            }
//
//
//            // 读取学术论文链表
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PAPER_START, strlen(PAPER_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, PAPER_END, strlen(PAPER_END)) != 0) {
//                    AcademicPaper* newPaper = (AcademicPaper*)malloc(sizeof(AcademicPaper));
//                    if (newPaper == NULL) {
//                        handleInputError("内存分配失败");
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
//                //回退一行
//                fseek(file, -1*strlen(buffer), SEEK_CUR);
//              
//               
//            }
//
//            // 读取计算机类学科竞赛链表
//            if (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, COMPETITION_START, strlen(COMPETITION_START)) == 0) {
//                while (fgets(buffer, sizeof(buffer), file) && strncmp(buffer, COMPETITION_END, strlen(COMPETITION_END)) != 0) {
//                    Competition* newCompetition = (Competition*)malloc(sizeof(Competition));
//                    if (newCompetition == NULL) {
//                        handleInputError("内存分配失败");
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
//                //回退一行
//                fseek(file, -1*strlen(buffer), SEEK_CUR);
//            }
//            // 跳过学生记录结束标记
//            fgets(buffer, sizeof(buffer), file);
//        }
//    }
//    fclose(file); // 关闭文件
//
//    // 加载管理员信息
//    FILE* adminFile = fopen("admin.txt", "r");
//    if (adminFile == NULL) {
//        handleInputError("打开文件失败");
//        return;
//    }
//    //freeAdminMemory(&adminsList); // 清空管理员链表
//
//    while (fgets(buffer, sizeof(buffer), adminFile)) {
//        if (strncmp(buffer, ADMIN_START, strlen(ADMIN_START)) == 0) {
//            AdminInfo* newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo));
//            if (newAdmin == NULL) {
//                handleInputError("内存分配失败");
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
//    fclose(adminFile); // 关闭文件
//}


int sizeofList_stu(StudentInfo* studentList)
{
    // TODO: 在此处插入 return 语句
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
    // TODO: 在此处插入 return 语句
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
    // TODO: 在此处插入 return 语句
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
//    // TODO: 在此处插入 return 语句
//    std::vector<Student>::const_iterator iter;
//    iter = std::find(M.students.begin(), M.students.end(), searchTerms);
//    if (iter != M.students.end())
//    {
//        // 搜索成功，返回索引
//        return (int)(iter - M.students.begin());
//    }
//    else
//    {
//        // 搜索失败，返回 -1 表示错误
//        return -1;
//    }
//}


//int searchId(int id, Manager M)
//{
//    std::vector<Student>::const_iterator iter;
//    iter = std::find(M.students.begin(), M.students.end(), id);
//    if (iter != M.students.end())
//    {
//        // 搜索成功，返回索引
//        return (int)(iter - M.students.begin());
//    }
//    else
//    {
//        // 搜索失败，返回 -1 表示错误
//        return -1;
//    }
//}

//void clear(Manager* M)
//{
//    (M->students).clear();
//}
