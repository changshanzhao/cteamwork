#include "function.h"
// 全局变量
StudentInfo* studentsList = NULL;
AdminInfo* adminsList = NULL;
// 登录系统
void loginSystem() {
    int choice;
    printf("请选择登录类型：\n1. 学生\n2. 管理员\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        studentLogin();
        break;
    case 2:
        adminLogin();
        break;
    default:
        printf("无效的选择。\n");
        exit(1);
    }
}

// 学生登录
void studentLogin() {
    char studentID[15], password[15];
    printf("请输入学号和密码：\n");
    scanf("%s %s", studentID, password);
    // 验证学生信息
    StudentInfo* student = findStudentByID(studentID);
    if (student && strcmp(student->password, password) == 0) {
        // 登录成功
        printf("学生登录成功。\n");
        // 显示学生菜单
        displayStudentMenu();
    }
    else {
        // 登录失败
        printf("学号或密码错误。\n");
    }
}

// 管理员登录
void adminLogin() {
    char username[15];
    printf("请输入管理员用户名：\n");
    scanf("%s", username);
    char password[15];
    printf("请输入管理员密码：\n");
    scanf("%s", password);
    AdminInfo* adminByUsername = findAdminByUsername(username);
    // 验证管理员密码
    if (adminByUsername && strcmp(adminByUsername->password, password) == 0) {
        // 登录成功
        printf("管理员登录成功。\n");
        // 显示管理员菜单
        displayAdminMenu();
    }
    else {
        // 登录失败
        printf("密码错误。\n");
        exit(1);
    }
}

// 添加学生账号
void addStudentAccount() {
    StudentInfo* newStudent = createStudent();
    // 计算GPA
    calculateGPA(newStudent);
    // 插入学生列表
    insertStudent(&studentsList, newStudent);
    printf("学生账号创建成功。\n");
}

// 添加课程
void addCourse(StudentInfo* student) {
    AcademicScoreNode* newCourse = createAcademicScore();
    printf("请输入课程信息：\n");
    printf("课程名称: ");
    scanf("%s", newCourse->courseName);
    printf("分数: ");
    scanf("%f", &newCourse->score);
    printf("学分: ");
    scanf("%f", &newCourse->credit);
    newCourse->gpa = calculateSingleGPA(&newCourse->score);
    // 将新课程添加到指定学生的课程链表
    insertAcademicScore(findStudentByID(student->studentID), newCourse);
    printf("课程添加成功。\n");
}

// 添加素质加分项目
void addQualityProject(StudentInfo* student) {
    QualityScoreNode* newProject = createQualityScore();
    printf("请输入加分项目信息：\n");
    printf("项目名称: ");
    scanf("%s", newProject->projectTitle);
    printf("加分: ");
    scanf("%f", &newProject->gpaContribution);
    // 将新项目添加到指定学生的加分链表
    insertQualityScore(findStudentByID(student->studentID), newProject);
    printf("加分项目添加成功。\n");
}

// 编辑学生成绩或删除学生
void modifyScoreMenu() {
    char studentID[8];
    printf("请输入学生学号: ");
    scanf("%s", studentID);
    StudentInfo* student = findStudentByID(studentID);
    if (student != NULL) {
        int choice;
        printf("请选择修改类型：\n");
        printf("1. 修改学业成绩\n");
        printf("2. 添加学业成绩\n");
        printf("3. 修改素质加分\n");
        printf("4. 添加素质加分\n");
        printf("5. 删除学生\n");
        printf("6. 返回\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            // 编辑学业成绩
            modifyAcademicScore(student);
            break;
        case 2:
            // 添加学业成绩
            addCourse(student);
            break;
        case 3:
            // 编辑素质加分
            modifyQualityScore(student);
            break;
        case 4:
            // 添加素质加分
            addQualityProject(student);
            break;
        case 5:
            // 删除学生
            deleteStudentRecord(&studentsList, studentID);
            break;
        case 6:
            printf("返回。\n");
            // 返回上一级菜单
            break;
        default:
            printf("无效的选项。\n");
        }
        // 更新GPA、总学分、加权平均分、总绩点
        calculateGPA(student);
        printf("成绩修改成功。\n");
    }
    else {
        printf("未找到学生信息。\n");
    }
}

// 排序学生
void sortStudentsMenu() {
    // 根据GPA或其他标准对学生列表进行排序
    int choice;
    printf("请选择排序方式：\n");
    printf("1. 按学号排序\n");
    printf("2. 按学业GPA排序\n");
    printf("3. 按加权平均分排序\n");
    printf("4. 按照总绩点排序\n");
    printf("5. 返回\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        // 按学号排序
        sortList(&studentsList, compareByStudentID);
        break;
    case 2:
        // 按学业GPA排序
        sortList(&studentsList, compareByGPA);
        break;
    case 3:
        // 按加权平均分排序
        sortList(&studentsList, compareByAverageScore);
        break;
    case 4:
        // 按照总绩点排序
        sortList(&studentsList, compareByTotalGPA);
        break;
    case 5:
        printf("返回。\n");
        // 返回上一级菜单
        break;
    default:
        printf("无效的选项。\n");
    }
    printf("学生排序完成。\n");
}

// 显示学生信息概况
void displayStudentInfo(StudentInfo* student) {
    // 显示学生的成绩和加分信息
    if (student == NULL) {
        printf("学生信息为空。\n");
        return;
    }
    printf("学号: %s\n", student->studentID);
    printf("姓名: %s\n", student->name);
    printf("班级: %d\n", student->classNumber);
    printf("已获总学分: %.2f\n", student->totalCredit);
    printf("学业GPA: %f\n", student->gpa);
    printf("素质加分GPA: %.2f\n", student->qualityGpa);
    printf("加权平均分: %.2f\n", student->averageScore);
    printf("总绩点: %.2f\n", student->totalGPA);
    printf("学生信息显示完成。\n");
    int choice;
    printf("是否要继续显示详细信息：\n");
    printf("1. 显示所有学业成绩\n");
    printf("2. 显示所有素质加分\n");
    printf("3. 返回\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        displayAcademicScore(student);
        break;
    case 2:
        displayQualityScore(student);
        break;
    case 3:
        printf("返回。\n");
        break;
    default:
        printf("无效的选项。\n");
    }
}

// 显示管理员菜单
void displayAdminMenu() {
    int choice;
    do {
        printf("管理员菜单：\n");
        printf("1. 添加学生账号\n");
        printf("2. 添加管理员账号\n");
        printf("3. 编辑学生成绩或删除学生\n");
        printf("4. 排序学生\n");
        printf("5. 显示学生信息\n");
        printf("6. 查找学生\n");
        printf("7. 保存到文件\n");
        printf("8. 从文件加载\n");
        printf("9. 退出\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            addStudentAccount();
            break;
        case 2:
            // 添加管理员账号
            addAdminAccount();
            break;
        case 3:
            modifyScoreMenu();
            break;
        case 4:
            sortStudentsMenu();
            break;
        case 5:
            // 显示学生信息
            displayAllStudent(studentsList);
            break;
        case 6:
            // 查找
        {
            printf("请输入需要查找学生的学号\n");
            char studentID[8];
            scanf("%s", studentID);
            StudentInfo* student = findStudentByID(studentID);
            if (student != NULL) {
                displayStudentInfo(student);
            }
            else {
                printf("未找到学生信息。\n");
            }
        }
            break;
        case 7:
            saveToFile();
            break;
        case 8:
            loadFromFile();
            break;
        case 9:
            printf("管理员退出登录。\n");
            freeMemory(&studentsList);//释放内存
            freeAdminMemory(&adminsList);//释放内存
            break;
        default:
            printf("无效的选项，请重新输入。\n");
        }
    } while (choice != 9);
}

//显示学生菜单
void displayStudentMenu() {
    int choice;
    do {
        printf("学生菜单：\n");
        printf("1. 查看成绩\n");
        printf("2. 查看加分\n");
        printf("3. 修改密码\n");
        printf("4. 退出\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            // 查看成绩
            break;
        case 2:
            // 查看加分
            break;
        case 3:
            // 修改密码
            break;
        case 4:
            printf("学生退出登录。\n");
            freeMemory(&studentsList);//释放内存
            freeAdminMemory(&adminsList);//释放内存
            break;
        default:
            printf("无效的选项，请重新输入。\n");
        }
    } while (choice != 4);
}
// 释放学生内存
void freeMemory(StudentInfo** head) {
    // 检查学生列表头指针是否为空
    if (*head == NULL) {
        return; // 如果头指针为空，则没有内存需要释放
    }

    // 遍历并释放每个学生节点的学业成绩链表
    StudentInfo* currentStudent = *head;
    while (currentStudent != NULL) {
        // 释放学业成绩链表中的每个节点
        AcademicScoreNode* currentScore = currentStudent->academicScores;
        while (currentScore != NULL) {
            AcademicScoreNode* temp = currentScore;
            currentScore = currentScore->next;
            free(temp); // 释放节点内存
        }

        // 释放素质加分链表中的每个节点
        QualityScoreNode* currentQuality = currentStudent->qualityScores;
        while (currentQuality != NULL) {
            QualityScoreNode* temp = currentQuality;
            currentQuality = currentQuality->next;
            free(temp); // 释放节点内存
        }

        // 释放当前学生节点的内存
        StudentInfo* tempStudent = currentStudent;
        currentStudent = currentStudent->next;
        free(tempStudent); // 释放节点内存
    }

    // 重置学生列表头指针为NULL
    *head = NULL;
}

// 插入学生记录
void insertStudent(StudentInfo** head, StudentInfo* newStudent) {
    // 将新学生插入到学生列表的头部
    if (head == NULL || newStudent == NULL) {
        return; // 如果头指针或新学生节点为空，则不执行操作
    }

    // 将新学生节点的next指针指向当前的头节点
    newStudent->next = *head;

    // 更新头指针为新学生节点
    *head = newStudent;
}

// 插入学业成绩
void insertAcademicScore(StudentInfo* student, AcademicScoreNode* scoreNode) {
    // 将新课程添加到学生的学业成绩链表
    if (student == NULL || scoreNode == NULL) {
        return; // 如果学生或成绩节点为空，则不执行操作
    }

    AcademicScoreNode* current = student->academicScores;
    if (current == NULL) {
        // 如果学生的成绩链表为空，则新节点成为第一个节点
        student->academicScores = scoreNode;
    }
    else {
        // 遍历链表直到找到最后一个节点
        while (current->next != NULL) {
            current = current->next;
        }
        // 将新节点添加到链表的末尾
        current->next = scoreNode;
    }
}

// 插入素质加分
void insertQualityScore(StudentInfo* student, QualityScoreNode* scoreNode) {
    // 将新加分项目添加到学生的素质加分链表
    if (student == NULL || scoreNode == NULL) {
        return; // 如果学生或加分节点为空，则不执行操作
    }

    QualityScoreNode* current = student->qualityScores;
    if (current == NULL) {
        // 如果学生的素质加分链表为空，则新节点成为第一个节点
        student->qualityScores = scoreNode;
    }
    else {
        // 遍历链表直到找到最后一个节点
        while (current->next != NULL) {
            current = current->next;
        }
        // 将新节点添加到链表的末尾
        current->next = scoreNode;
    }
}

// 计算GPA、总学分、加权平均分、总绩点
void calculateGPA(StudentInfo* student) {
    // 计算并更新学生的GPA
    if (student == NULL) {
        return; // 如果传入的学生指针为空，则直接返回
    }
    float totalQualityPoints = 0.00f; // 用于累加课程的GPA值
    int numCourses = 0; // 用于计数课程数量
    float totalCredit = 0.00f;// 用于累加学分
    float totalScore = 0.00f; // 用于计算加权平均分


    // 遍历学生的学业成绩链表
    AcademicScoreNode* currentScore = student->academicScores;
    while (currentScore != NULL) {
        totalQualityPoints += currentScore->gpa * currentScore->credit; // 累加每个课程的GPA值和学分
        numCourses++;     // 课程数量计数
        totalCredit += currentScore->credit;    // 累加学分
        totalScore += currentScore->score * currentScore->credit; // 累加分数
        currentScore = currentScore->next; // 移动到下一个课程节点
    }

    // 总学分
    student->totalCredit = totalCredit;

    // 计算加权学业GPA
    if (numCourses > 0) {
        student->gpa = totalQualityPoints / totalCredit; // 计算学业GPA
    }
    else {
        student->gpa = 0.00f; // 如果没有课程，GPA为0
    }

    // 总绩点
    student->totalGPA = student->gpa + student->qualityGpa;

    // 计算加权平均分
    student->averageScore = totalScore / totalCredit;
}

// 计算单门课程绩点
float calculateSingleGPA(const float* score) {
    if (*score >= 90) {
        return 4.0f;
    }
    else if (*score >= 87) {
        return 3.7f;
    }
    else if (*score >= 83) {
        return 3.3f;
    }
    else if (*score >= 80) {
        return 3.0f;
    }
    else if (*score >= 77) {
        return 2.7f;
    }
    else if (*score >= 73) {
        return 2.3f;
    }
    else if (*score >= 70) {
        return 2.0f;
    }
    else if (*score >= 67) {
        return 1.7f;
    }
    else if (*score >= 63) {
        return 1.3f;
    }
    else if (*score >= 60) {
        return 1.0f;
    }
    else {
        return 0.0f;
    }
}

// 删除学生记录
void deleteStudentRecord(StudentInfo** head, char* studentID) {
    // 根据学号删除学生记录
    // 使用findStudentByID函数查找学生
    StudentInfo* studentToDelete = findStudentByID(studentID);
    if (studentToDelete != NULL) {
        // 如果找到了学生，从链表中删除
        if (*head == studentToDelete) {
            // 如果要删除的是头节点
            *head = (*head)->next;
        }
        else {
            // 如果要删除的是链表中间或尾部的节点
            StudentInfo* current = *head;
            while (current->next != studentToDelete) {
                current = current->next;
            }
            current->next = current->next->next;
        }
        free(studentToDelete); // 释放学生记录的内存
        printf("学生记录删除成功。\n");
    }
    else {
        // 如果没有找到学生ID匹配的节点，打印错误信息
        printf("未找到学号为 %s 的学生记录。\n", studentID);
    }
}

// 处理输入错误
void handleInputError(const char* message) {
    // 显示错误信息
    printf("%s\n", message);
}

// 创建新学生
StudentInfo* createStudent() {
    // 分配内存给新的StudentInfo实例
    StudentInfo* newStudent = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (newStudent == NULL) {
        // 如果内存分配失败，打印错误信息并退出程序
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }

    // 初始化新学生信息
    newStudent->next = NULL; // 初始化链表指针
    newStudent->academicScores = NULL; // 初始化学业成绩链表
    newStudent->qualityScores = NULL; // 初始化素质加分链表
    newStudent->gpa = 0.00f; // 初始化GPA
    newStudent->totalCredit = 0; // 初始化总学分
    newStudent->qualityGpa = 0.00f; // 初始化素质加分GPA
    newStudent->averageScore = 0.00f; // 初始化加权平均分
    strcpy(newStudent->name, "New Student");
    strcpy(newStudent->studentID, "00000000");
    newStudent->classNumber = 1; // 假设学生班级为1
    strcpy(newStudent->password, "123456"); // 默认密码为123456

    // 输入学生信息
    printf("请输入学生信息：\n");
    printf("学号: ");
    scanf("%s", newStudent->studentID);
    // 检查学号是否已存在
    if (findStudentByID(newStudent->studentID) != NULL) {
        // 如果学号已存在，打印错误信息、释放内存并返回上一级菜单
        handleInputError("学号已存在，请重新输入。");
        free(newStudent);
        return NULL;
    }
    printf("姓名: ");
    scanf("%s", newStudent->name);
    printf("班级: ");
    scanf("%d", &newStudent->classNumber);
    //    printf("密码: ");
    //    scanf("%s", newStudent->password);
        //录入学业成绩
    int choice1;
    printf("是否现在录入课程记录？(1. 是 2. 否): ");
    scanf("%d", &choice1);
    if (choice1 == 1) {
        int numCourses;
        printf("请输入学生的课程数量：");
        scanf("%d", &numCourses);
        for (int i = 0; i < numCourses; i++) {
            AcademicScoreNode* newCourse = createAcademicScore();
            printf("请输入第%d门课程信息：\n", i + 1);
            addCourse(newStudent);
        }
    }

    int choice2;
    printf("是否现在录入素质加分项目记录？(1. 是 2. 否): ");
    scanf("%d", &choice2);
    if (choice2 == 1) {
        //录入素质加分项目
        int numProjects;
        printf("请输入学生的加分项目数量：");
        scanf("%d", &numProjects);
        for (int i = 0; i < numProjects; i++) {
            QualityScoreNode* newProject = createQualityScore();
            printf("请输入第%d个加分项目信息：\n", i + 1);
            addQualityProject(newStudent);
        }
    }

    // 返回新创建的StudentInfo指针
    return newStudent;
}

// 创建新学业成绩
AcademicScoreNode* createAcademicScore() {
    // 分配内存给新的AcademicScoreNode实例
    AcademicScoreNode* newCourse = (AcademicScoreNode*)malloc(sizeof(AcademicScoreNode));
    if (newCourse == NULL) {
        // 如果内存分配失败，打印错误信息并退出程序
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    // 初始化新课程信息
    newCourse->next = NULL; // 初始化链表指针
    strcpy(newCourse->courseName, "Unknown Course"); // 初始化课程名称
    newCourse->score = 0.00f; // 初始化课程分数
    newCourse->credit = 0.0f; // 初始化课程学分
    newCourse->gpa = 0.0f; // 初始化课程绩点
    printf("请输入课程信息：\n");
    printf("课程名称: ");
    scanf("%s", newCourse->courseName);
    printf("分数: ");
    scanf("%f", &newCourse->score);
    printf("学分: ");
    scanf("%f", &newCourse->credit);
    newCourse->gpa = calculateSingleGPA(&newCourse->score); // 计算课程绩点
    // 返回新创建的AcademicScoreNode指针
    return newCourse;
}

// 创建新素质加分
QualityScoreNode* createQualityScore() {
    // 分配内存给新的QualityScoreNode实例
    QualityScoreNode* newProject = (QualityScoreNode*)malloc(sizeof(QualityScoreNode));
    if (newProject == NULL) {
        // 如果内存分配失败，打印错误信息并退出程序
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    newProject->gpaContribution = 0.0; // 默认加分值初始化为0.0
    printf("请输入加分项目信息：\n");
    printf("项目名称: ");
    scanf("%s", newProject->projectTitle);
    printf("加分: ");
    scanf("%f", &newProject->gpaContribution);
    newProject->next = NULL;
    // 返回新创建的QualityScoreNode指针
    return newProject;
}

// 查找学生
StudentInfo* findStudentByID(const char* studentID) {
    // 遍历学生列表，查找指定学号的学生
    // 从学生列表的头部开始遍历
    StudentInfo* currentStudent = studentsList;

    // 遍历整个学生列表
    while (currentStudent != NULL) {
        // 比较当前学生的学号与给定的学号
        if (strcmp(currentStudent->studentID, studentID) == 0) {
            // 如果找到匹配的学号，返回当前学生的信息
            return currentStudent;
        }
        // 移动到链表的下一个节点
        currentStudent = currentStudent->next;
    }
    // 如果遍历完整个列表都没有找到匹配的学号，返回NULL
    return NULL;
}

// 查找管理员
AdminInfo* findAdminByUsername(const char* username) {
    // 比较给定的用户名和管理员的用户名
    if (strcmp(adminsList->username, username) == 0) {
        // 如果找到匹配的用户名，返回管理员信息
        return adminsList;
    }
    // 如果没有找到匹配的用户名，返回NULL
    return NULL;
}


// 编辑学生学业成绩
void modifyAcademicScore(StudentInfo* student) {
    // 修改学业成绩
    int choice;
    printf("请选择修改类型：\n");
    printf("1. 修改课程名称\n");
    printf("2. 修改分数\n");
    printf("3. 修改学分\n");
    printf("4. 删除课程\n");
    printf("5. 返回上一级菜单\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        // 修改课程名称
    {
        if (student->academicScores == NULL) {
            printf("当前没有课程可以修改。\n");
            break;
        }
        AcademicScoreNode* current = student->academicScores;
        printf("请输入要修改的课程名称（输入q退出）：");
        char courseName[MAX_NAME_LENGTH];
        scanf("%s", courseName);
        if (strcmp(courseName, "q") == 0) {
            break;
        }
        while (current != NULL) {
            if (strcmp(current->courseName, courseName) == 0) {
                printf("找到课程: %s, 当前分数: %.2f\n", current->courseName, current->score);
                printf("请输入新的课程名称: ");
                scanf("%s", current->courseName);
                printf("课程名称修改成功。\n");
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("未找到指定的课程。\n");
        }
    }
        break;
    case 2:
        // 修改分数
    {
        if (student->academicScores == NULL) {
            printf("当前没有课程可以修改。\n");
            break;
        }
        AcademicScoreNode* currentScore = student->academicScores;
        printf("请输入要修改的课程名称（输入q退出）：");
        char scoreCourseName[MAX_NAME_LENGTH];
        scanf("%s", scoreCourseName);
        if (strcmp(scoreCourseName, "q") == 0) {
            break;
        }
        while (currentScore != NULL) {
            if (strcmp(currentScore->courseName, scoreCourseName) == 0) {
                printf("找到课程: %s, 当前分数: %.2f\n", currentScore->courseName, currentScore->score);
                printf("请输入新的分数: ");
                scanf("%2f", &currentScore->score);
                currentScore->gpa = calculateSingleGPA(&currentScore->score);//重新计算当前课程绩点
                calculateGPA(student);//重新计算GPA\总学分\加权平均分\总绩点
                printf("分数修改成功。\n");
                break;
            }
            currentScore = currentScore->next;
        }
        if (currentScore == NULL) {
            printf("未找到指定的课程。\n");
        }
    }
        break;
    case 3:
        // 修改学分
    {
        if (student->academicScores == NULL) {
            printf("当前没有课程可以修改。\n");
            break;
        }
        AcademicScoreNode* currentCredit = student->academicScores;
        printf("请输入要修改的课程名称（输入q退出）：");
        char creditCourseName[MAX_NAME_LENGTH];
        scanf("%s", creditCourseName);
        if (strcmp(creditCourseName, "q") == 0) {
            break;
        }
        while (currentCredit != NULL) {
            if (strcmp(currentCredit->courseName, creditCourseName) == 0) {
                printf("找到课程: %s, 当前学分: %.2f\n", currentCredit->courseName, currentCredit->credit);
                printf("请输入新的学分: ");
                scanf("%2f", &currentCredit->credit);
                calculateGPA(student);  //重新计算GPA\总学分\加权平均分\总绩点
                printf("学分修改成功。\n");
                break;
            }
            currentCredit = currentCredit->next;
        }
        if (currentCredit == NULL) {
            printf("未找到指定的课程。\n");
        }
    }
        break;
    case 4:
        // 删除课程
    {
        if (student->academicScores == NULL) {
            printf("当前没有课程可以删除。\n");
            break;
        }
        AcademicScoreNode* currentDelete = student->academicScores;
        AcademicScoreNode* prev = NULL;
        printf("请输入要删除的课程名称（输入q退出）：");
        char deleteCourseName[MAX_NAME_LENGTH];
        scanf("%s", deleteCourseName);
        if (strcmp(deleteCourseName, "q") == 0) {
            break;
        }
        while (currentDelete != NULL) {
            if (strcmp(currentDelete->courseName, deleteCourseName) == 0) {
                if (prev == NULL) {
                    // 要删除的是头节点
                    student->academicScores = currentDelete->next;
                }
                else {
                    // 要删除的是中间或尾节点
                    prev->next = currentDelete->next;
                }
                AcademicScoreNode* temp = currentDelete;
                currentDelete = currentDelete->next;
                free(temp); // 释放被删除节点的内存
                calculateGPA(student);  //重新计算GPA\总学分\加权平均分\总绩点
                printf("课程删除成功。\n");
                break;
            }
            prev = currentDelete;
            currentDelete = currentDelete->next;
        }
        if (currentDelete == NULL) {
            printf("未找到指定的课程。\n");
        }
    }
        break;
    case 5:
        printf("返回上一级菜单。\n");
        // 返回上一级菜单
        break;
    default:
        printf("无效的选项。\n");
    }
}


// 编辑学生素质加分
void modifyQualityScore(StudentInfo* student) {
    // 修改素质加分
    if (student == NULL) {
        handleInputError("学生信息不能为空。\n");
        return;
    }

    int choice;
    printf("请选择修改类型：\n");
    printf("1. 修改加分项目\n");
    printf("2. 删除加分项目\n");
    printf("3. 返回上一级菜单\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        // 修改加分项目
    {
        if (student->qualityScores == NULL) {
            printf("当前没有加分项目可以修改。\n");
            break;
        }
        QualityScoreNode* current = student->qualityScores;
        printf("请输入要修改的加分项目名称（输入q退出）：");
        char projectTitle[MAX_NAME_LENGTH];
        scanf("%s", projectTitle);
        if (strcmp(projectTitle, "q") == 0) {
            break;
        }
        while (current != NULL) {
            if (strcmp(current->projectTitle, projectTitle) == 0) {
                printf("找到加分项目: %s, 当前加分: %.2f\n", current->projectTitle, current->gpaContribution);
                printf("请输入新的加分: ");
                scanf("%f", &current->gpaContribution);
                calculateGPA(student);  //重新计算GPA\总学分\加权平均分\总绩点
                printf("加分项目修改成功。\n");
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("未找到指定的加分项目。\n");
        }
    }
        break;
    case 2:
        // 删除加分项目
    {
        if (student->qualityScores == NULL) {
            printf("当前没有加分项目可以删除。\n");
            break;
        }
        QualityScoreNode* currentDelete = student->qualityScores;
        QualityScoreNode* prev = NULL;
        printf("请输入要删除的加分项目名称（输入q退出）：");
        char deleteTitle[MAX_NAME_LENGTH];
        scanf("%s", deleteTitle);
        if (strcmp(deleteTitle, "q") == 0) {
            break;
        }
        while (currentDelete != NULL) {
            if (strcmp(currentDelete->projectTitle, deleteTitle) == 0) {
                if (prev == NULL) {
                    // 要删除的是头节点
                    student->qualityScores = currentDelete->next;
                }
                else {
                    // 要删除的是中间或尾节点
                    prev->next = currentDelete->next;
                }
                QualityScoreNode* temp = currentDelete;
                currentDelete = currentDelete->next;
                free(temp); // 释放被删除节点的内存
                calculateGPA(student);  //重新计算GPA\总学分\加权平均分\总绩点
                printf("加分项目删除成功。\n");
                break;
            }
            prev = currentDelete;
            currentDelete = currentDelete->next;
        }
        if (currentDelete == NULL) {
            printf("未找到指定的加分项目。\n");
        }
    }
        break;
    case 3:
        printf("返回上一级菜单。\n");
        // 返回上一级菜单
        break;
    default:
        printf("无效的选项。\n");
    }
}

// 显示学生的全部学业成绩
void displayAcademicScore(StudentInfo* student) {
    // 显示学生的学业成绩
    if (student == NULL) {
        printf("学生信息为空。\n");
        return;
    }
    AcademicScoreNode* current = student->academicScores;
    if (current == NULL) {
        printf("学生没有学业成绩。\n");
        return;
    }
    printf("学业成绩：\n");
    while (current != NULL) {
        printf("课程名称: %s, 学分: %.2f, 分数: %.2f, 绩点: %.2f\n", current->courseName, current->credit, current->score, current->gpa);
        current = current->next;
    }
    printf("所有学业成绩已全部显示完成。\n");
}

// 显示学生的全部素质加分
void displayQualityScore(StudentInfo* student) {
    // 显示学生的素质加分
    if (student == NULL) {
        printf("学生信息为空。\n");
        return;
    }
    QualityScoreNode* current = student->qualityScores;
    if (current == NULL) {
        printf("学生没有素质加分。\n");
        return;
    }
    printf("素质加分：\n");
    while (current != NULL) {
        printf("项目名称: %s, 加分: %.2f\n", current->projectTitle, current->gpaContribution);
        current = current->next;
    }
    printf("所有素质加分已全部显示完成。\n");
}

//释放管理员内存
void freeAdminMemory(AdminInfo** head) {
    // 检查管理员列表头指针是否为空
    if (*head == NULL) {
        return; // 如果头指针为空，则没有内存需要释放
    }
    // 释放当前管理员节点的内存
    AdminInfo* tempAdmin = *head;
    *head = NULL;
    free(tempAdmin); // 释放节点内存
}

//显示所有学生概况
void displayAllStudent(StudentInfo* head) {
    // 显示所有学生的信息
    if (head == NULL) {
        printf("学生信息为空。\n");
        return;
    }
    StudentInfo* current = head;
    while (current != NULL) {
        printf("学号: %s\n", current->studentID);
        printf("姓名: %s\n", current->name);
        printf("班级: %d\n", current->classNumber);
        printf("已获总学分: %.2f\n", current->totalCredit);
        printf("学业GPA: %f\n", current->gpa);
        printf("素质加分GPA: %.2f\n", current->qualityGpa);
        printf("加权平均分: %.2f\n", current->averageScore);
        printf("总绩点: %.2f\n", current->totalGPA);
        printf("\n\n");
        current = current->next;
    }
    printf("\n");
    printf("所有学生信息已全部显示完成。\n");
}

//排序学生链表
void sortList(StudentInfo** head, int (*compare)(const StudentInfo*, const StudentInfo*)) {
    int swapped;
    StudentInfo* current;
    StudentInfo* prev = NULL;
    do {
        swapped = 0;
        current = *head;
        while (current && current->next) {
            if ((*compare)(current, current->next) > 0) {
                // 交换两个节点的数据
                StudentInfo temp = *current;
                *current = *(current->next);
                *(current->next) = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// 比较函数：按学号排序
int compareByStudentID(const StudentInfo* a, const StudentInfo* b) {
    return strcmp(a->studentID, b->studentID);
}

// 比较函数：按学业GPA排序
int compareByGPA(const StudentInfo* a, const StudentInfo* b) {
    if (a->gpa > b->gpa) return -1;
    if (a->gpa < b->gpa) return 1;
    return 0;
}

// 比较函数：按加权平均分排序
int compareByAverageScore(const StudentInfo* a, const StudentInfo* b) {
    if (a->averageScore > b->averageScore) return -1;
    if (a->averageScore < b->averageScore) return 1;
    return 0;
}

// 比较函数：按总绩点排序
int compareByTotalGPA(const StudentInfo* a, const StudentInfo* b) {
    if (a->totalGPA > b->totalGPA) return -1;
    if (a->totalGPA < b->totalGPA) return 1;
    return 0;
}

// 添加管理员账号
void addAdminAccount() {
    AdminInfo* newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo)); // 分配新管理员内存
    if (newAdmin == NULL) {
        handleInputError("内存分配失败，无法添加管理员账号。\n");
        return;
    }

    printf("请输入管理员用户名: ");
    scanf("%s", newAdmin->username);
    // 检查用户名是否已存在
    while (findAdminByUsername(newAdmin->username) != NULL) {
        printf("用户名已存在，请重新输入: ");
        scanf("%s", newAdmin->username);
    }

    printf("请输入管理员密码: ");
    scanf("%s", newAdmin->password);

    // 将新管理员添加到链表头部
    newAdmin->next = adminsList;
    adminsList = newAdmin;

    printf("管理员账号添加成功。\n");
}

// 保存到文件
void saveToFile() {
    //写入学生信息到文件
    FILE* file = fopen("students.txt", "w"); // 打开文件用于文本写入
    if (file == NULL) {
        perror("无法打开文件进行写入");
        return;
    }

    StudentInfo* current = studentsList;
    while (current != NULL) {
        fprintf(file, "%s\n", current->studentID);
        fprintf(file, "%s\n", current->name);
        fprintf(file, "%d\n", current->classNumber);
        fprintf(file, "%f\n", current->gpa);
        fprintf(file, "%.2f\n", current->totalCredit);
        fprintf(file, "%.2f\n", current->qualityGpa);
        fprintf(file, "%f\n", current->averageScore);
        fprintf(file, "%f\n", current->totalGPA);

        // 遍历学业成绩链表并写入
        AcademicScoreNode* score = current->academicScores;
        while (score != NULL) {
            fprintf(file, "%s %f %f %f\n", score->courseName, score->score, score->credit, score->gpa);
            score = score->next;
        }

        // 遍历素质加分链表并写入
        QualityScoreNode* project = current->qualityScores;
        while (project != NULL) {
            fprintf(file, "%s %f\n", project->projectTitle, project->gpaContribution);
            project = project->next;
        }

        current = current->next; // 移动到下一个学生
    }
    fclose(file); // 关闭文件

    //写入管理员信息到文件
    FILE* adminFile = fopen("admins.txt", "w"); // 打开文件用于文本写入
    if (adminFile == NULL) {
        perror("无法打开文件进行写入");
        return;
    }

    AdminInfo* currentAdmin = adminsList;
    while (currentAdmin != NULL) {
        fprintf(adminFile, "%s %s\n", currentAdmin->username, currentAdmin->password);
        currentAdmin = currentAdmin->next; // 移动到下一个管理员
    }
    fclose(adminFile); // 关闭文件
}

// 从文件加载
void loadFromFile() {
    // 从文件加载学生信息
    FILE* file = fopen("students.txt", "r"); // 打开文件用于文本读取
    if (file == NULL) {
        perror("无法打开文件进行读取");
        return;
    }

    // 清空当前学生列表
    freeMemory(&studentsList);

    StudentInfo* newStudent;
    AcademicScoreNode* newScore{};
    QualityScoreNode* newProject{};

    // 临时变量用于读取
    char tempID[8], tempName[15], tempPassword[15];
    int tempClassNumber;
    float tempGPA, tempTotalCredit, tempQualityGPA, tempAverageScore, tempTotalGPA;
    char courseName[MAX_NAME_LENGTH], projectTitle[MAX_NAME_LENGTH];

    while (!feof(file)) {
        // 读取学生基本信息
        fscanf(file, "%s %s %d %f %f %f %f %f", tempID, tempName, &tempClassNumber, &tempGPA, &tempTotalCredit, &tempQualityGPA, &tempAverageScore, &tempTotalGPA);
        newStudent = createStudent();
        strcpy(newStudent->studentID, tempID);
        strcpy(newStudent->name, tempName);
        newStudent->classNumber = tempClassNumber;
        newStudent->gpa = tempGPA;
        newStudent->totalCredit = tempTotalCredit;
        newStudent->qualityGpa = tempQualityGPA;
        newStudent->averageScore = tempAverageScore;
        newStudent->totalGPA = tempTotalGPA;

        // 读取学业成绩并添加到学生记录
        while (!feof(file)) {
            fscanf(file, "%s %f %f %f", courseName, &newScore->score, &newScore->credit, &newScore->gpa);
            newScore = createAcademicScore();
            insertAcademicScore(newStudent, newScore);
        }

        // 读取素质加分并添加到学生记录
        while (!feof(file)) {
            fscanf(file, "%s %f", projectTitle, &newProject->gpaContribution);
            newProject = createQualityScore();
            insertQualityScore(newStudent, newProject);
        }

        // 将新学生添加到列表头部
        insertStudent(&studentsList, newStudent);
    }

    fclose(file); // 关闭文件

    // 从文件加载管理员信息
    FILE* adminFile = fopen("admins.txt", "r"); // 打开文件用于文本读取
    if (adminFile == NULL) {
        perror("无法打开文件进行读取");
        return;
    }

    // 清空当前管理员列表
    freeAdminMemory(&adminsList);

    AdminInfo* newAdmin;
    char tempAdminName[15];
    char tempAdminPassword[15];

    while (!feof(adminFile)) {
        // 读取管理员信息
        fscanf(adminFile, "%s %s", tempAdminName, tempAdminPassword);
        newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo));
        strcpy(newAdmin->username, tempAdminName);
        strcpy(newAdmin->password, tempAdminPassword);
        newAdmin->next = adminsList;
        adminsList = newAdmin;
    }

    fclose(adminFile); // 关闭文件
}