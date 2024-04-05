#include "function.h"
// ȫ�ֱ���
StudentInfo* studentsList = NULL;
AdminInfo* adminsList = NULL;
// ��¼ϵͳ
void loginSystem() {
    int choice;
    printf("��ѡ���¼���ͣ�\n1. ѧ��\n2. ����Ա\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        studentLogin();
        break;
    case 2:
        adminLogin();
        break;
    default:
        printf("��Ч��ѡ��\n");
        exit(1);
    }
}

// ѧ����¼
void studentLogin() {
    char studentID[15], password[15];
    printf("������ѧ�ź����룺\n");
    scanf("%s %s", studentID, password);
    // ��֤ѧ����Ϣ
    StudentInfo* student = findStudentByID(studentID);
    if (student && strcmp(student->password, password) == 0) {
        // ��¼�ɹ�
        printf("ѧ����¼�ɹ���\n");
        // ��ʾѧ���˵�
        displayStudentMenu();
    }
    else {
        // ��¼ʧ��
        printf("ѧ�Ż��������\n");
    }
}

// ����Ա��¼
void adminLogin() {
    char username[15];
    printf("���������Ա�û�����\n");
    scanf("%s", username);
    char password[15];
    printf("���������Ա���룺\n");
    scanf("%s", password);
    AdminInfo* adminByUsername = findAdminByUsername(username);
    // ��֤����Ա����
    if (adminByUsername && strcmp(adminByUsername->password, password) == 0) {
        // ��¼�ɹ�
        printf("����Ա��¼�ɹ���\n");
        // ��ʾ����Ա�˵�
        displayAdminMenu();
    }
    else {
        // ��¼ʧ��
        printf("�������\n");
        exit(1);
    }
}

// ���ѧ���˺�
void addStudentAccount() {
    StudentInfo* newStudent = createStudent();
    // ����GPA
    calculateGPA(newStudent);
    // ����ѧ���б�
    insertStudent(&studentsList, newStudent);
    printf("ѧ���˺Ŵ����ɹ���\n");
}

// ��ӿγ�
void addCourse(StudentInfo* student) {
    AcademicScoreNode* newCourse = createAcademicScore();
    printf("������γ���Ϣ��\n");
    printf("�γ�����: ");
    scanf("%s", newCourse->courseName);
    printf("����: ");
    scanf("%f", &newCourse->score);
    printf("ѧ��: ");
    scanf("%f", &newCourse->credit);
    newCourse->gpa = calculateSingleGPA(&newCourse->score);
    // ���¿γ���ӵ�ָ��ѧ���Ŀγ�����
    insertAcademicScore(findStudentByID(student->studentID), newCourse);
    printf("�γ���ӳɹ���\n");
}

// ������ʼӷ���Ŀ
void addQualityProject(StudentInfo* student) {
    QualityScoreNode* newProject = createQualityScore();
    printf("������ӷ���Ŀ��Ϣ��\n");
    printf("��Ŀ����: ");
    scanf("%s", newProject->projectTitle);
    printf("�ӷ�: ");
    scanf("%f", &newProject->gpaContribution);
    // ������Ŀ��ӵ�ָ��ѧ���ļӷ�����
    insertQualityScore(findStudentByID(student->studentID), newProject);
    printf("�ӷ���Ŀ��ӳɹ���\n");
}

// �༭ѧ���ɼ���ɾ��ѧ��
void modifyScoreMenu() {
    char studentID[8];
    printf("������ѧ��ѧ��: ");
    scanf("%s", studentID);
    StudentInfo* student = findStudentByID(studentID);
    if (student != NULL) {
        int choice;
        printf("��ѡ���޸����ͣ�\n");
        printf("1. �޸�ѧҵ�ɼ�\n");
        printf("2. ���ѧҵ�ɼ�\n");
        printf("3. �޸����ʼӷ�\n");
        printf("4. ������ʼӷ�\n");
        printf("5. ɾ��ѧ��\n");
        printf("6. ����\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            // �༭ѧҵ�ɼ�
            modifyAcademicScore(student);
            break;
        case 2:
            // ���ѧҵ�ɼ�
            addCourse(student);
            break;
        case 3:
            // �༭���ʼӷ�
            modifyQualityScore(student);
            break;
        case 4:
            // ������ʼӷ�
            addQualityProject(student);
            break;
        case 5:
            // ɾ��ѧ��
            deleteStudentRecord(&studentsList, studentID);
            break;
        case 6:
            printf("���ء�\n");
            // ������һ���˵�
            break;
        default:
            printf("��Ч��ѡ�\n");
        }
        // ����GPA����ѧ�֡���Ȩƽ���֡��ܼ���
        calculateGPA(student);
        printf("�ɼ��޸ĳɹ���\n");
    }
    else {
        printf("δ�ҵ�ѧ����Ϣ��\n");
    }
}

// ����ѧ��
void sortStudentsMenu() {
    // ����GPA��������׼��ѧ���б��������
    int choice;
    printf("��ѡ������ʽ��\n");
    printf("1. ��ѧ������\n");
    printf("2. ��ѧҵGPA����\n");
    printf("3. ����Ȩƽ��������\n");
    printf("4. �����ܼ�������\n");
    printf("5. ����\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        // ��ѧ������
        sortList(&studentsList, compareByStudentID);
        break;
    case 2:
        // ��ѧҵGPA����
        sortList(&studentsList, compareByGPA);
        break;
    case 3:
        // ����Ȩƽ��������
        sortList(&studentsList, compareByAverageScore);
        break;
    case 4:
        // �����ܼ�������
        sortList(&studentsList, compareByTotalGPA);
        break;
    case 5:
        printf("���ء�\n");
        // ������һ���˵�
        break;
    default:
        printf("��Ч��ѡ�\n");
    }
    printf("ѧ��������ɡ�\n");
}

// ��ʾѧ����Ϣ�ſ�
void displayStudentInfo(StudentInfo* student) {
    // ��ʾѧ���ĳɼ��ͼӷ���Ϣ
    if (student == NULL) {
        printf("ѧ����ϢΪ�ա�\n");
        return;
    }
    printf("ѧ��: %s\n", student->studentID);
    printf("����: %s\n", student->name);
    printf("�༶: %d\n", student->classNumber);
    printf("�ѻ���ѧ��: %.2f\n", student->totalCredit);
    printf("ѧҵGPA: %f\n", student->gpa);
    printf("���ʼӷ�GPA: %.2f\n", student->qualityGpa);
    printf("��Ȩƽ����: %.2f\n", student->averageScore);
    printf("�ܼ���: %.2f\n", student->totalGPA);
    printf("ѧ����Ϣ��ʾ��ɡ�\n");
    int choice;
    printf("�Ƿ�Ҫ������ʾ��ϸ��Ϣ��\n");
    printf("1. ��ʾ����ѧҵ�ɼ�\n");
    printf("2. ��ʾ�������ʼӷ�\n");
    printf("3. ����\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        displayAcademicScore(student);
        break;
    case 2:
        displayQualityScore(student);
        break;
    case 3:
        printf("���ء�\n");
        break;
    default:
        printf("��Ч��ѡ�\n");
    }
}

// ��ʾ����Ա�˵�
void displayAdminMenu() {
    int choice;
    do {
        printf("����Ա�˵���\n");
        printf("1. ���ѧ���˺�\n");
        printf("2. ��ӹ���Ա�˺�\n");
        printf("3. �༭ѧ���ɼ���ɾ��ѧ��\n");
        printf("4. ����ѧ��\n");
        printf("5. ��ʾѧ����Ϣ\n");
        printf("6. ����ѧ��\n");
        printf("7. ���浽�ļ�\n");
        printf("8. ���ļ�����\n");
        printf("9. �˳�\n");
        printf("��ѡ�������");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            addStudentAccount();
            break;
        case 2:
            // ��ӹ���Ա�˺�
            addAdminAccount();
            break;
        case 3:
            modifyScoreMenu();
            break;
        case 4:
            sortStudentsMenu();
            break;
        case 5:
            // ��ʾѧ����Ϣ
            displayAllStudent(studentsList);
            break;
        case 6:
            // ����
        {
            printf("��������Ҫ����ѧ����ѧ��\n");
            char studentID[8];
            scanf("%s", studentID);
            StudentInfo* student = findStudentByID(studentID);
            if (student != NULL) {
                displayStudentInfo(student);
            }
            else {
                printf("δ�ҵ�ѧ����Ϣ��\n");
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
            printf("����Ա�˳���¼��\n");
            freeMemory(&studentsList);//�ͷ��ڴ�
            freeAdminMemory(&adminsList);//�ͷ��ڴ�
            break;
        default:
            printf("��Ч��ѡ����������롣\n");
        }
    } while (choice != 9);
}

//��ʾѧ���˵�
void displayStudentMenu() {
    int choice;
    do {
        printf("ѧ���˵���\n");
        printf("1. �鿴�ɼ�\n");
        printf("2. �鿴�ӷ�\n");
        printf("3. �޸�����\n");
        printf("4. �˳�\n");
        printf("��ѡ�������");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            // �鿴�ɼ�
            break;
        case 2:
            // �鿴�ӷ�
            break;
        case 3:
            // �޸�����
            break;
        case 4:
            printf("ѧ���˳���¼��\n");
            freeMemory(&studentsList);//�ͷ��ڴ�
            freeAdminMemory(&adminsList);//�ͷ��ڴ�
            break;
        default:
            printf("��Ч��ѡ����������롣\n");
        }
    } while (choice != 4);
}
// �ͷ�ѧ���ڴ�
void freeMemory(StudentInfo** head) {
    // ���ѧ���б�ͷָ���Ƿ�Ϊ��
    if (*head == NULL) {
        return; // ���ͷָ��Ϊ�գ���û���ڴ���Ҫ�ͷ�
    }

    // �������ͷ�ÿ��ѧ���ڵ��ѧҵ�ɼ�����
    StudentInfo* currentStudent = *head;
    while (currentStudent != NULL) {
        // �ͷ�ѧҵ�ɼ������е�ÿ���ڵ�
        AcademicScoreNode* currentScore = currentStudent->academicScores;
        while (currentScore != NULL) {
            AcademicScoreNode* temp = currentScore;
            currentScore = currentScore->next;
            free(temp); // �ͷŽڵ��ڴ�
        }

        // �ͷ����ʼӷ������е�ÿ���ڵ�
        QualityScoreNode* currentQuality = currentStudent->qualityScores;
        while (currentQuality != NULL) {
            QualityScoreNode* temp = currentQuality;
            currentQuality = currentQuality->next;
            free(temp); // �ͷŽڵ��ڴ�
        }

        // �ͷŵ�ǰѧ���ڵ���ڴ�
        StudentInfo* tempStudent = currentStudent;
        currentStudent = currentStudent->next;
        free(tempStudent); // �ͷŽڵ��ڴ�
    }

    // ����ѧ���б�ͷָ��ΪNULL
    *head = NULL;
}

// ����ѧ����¼
void insertStudent(StudentInfo** head, StudentInfo* newStudent) {
    // ����ѧ�����뵽ѧ���б��ͷ��
    if (head == NULL || newStudent == NULL) {
        return; // ���ͷָ�����ѧ���ڵ�Ϊ�գ���ִ�в���
    }

    // ����ѧ���ڵ��nextָ��ָ��ǰ��ͷ�ڵ�
    newStudent->next = *head;

    // ����ͷָ��Ϊ��ѧ���ڵ�
    *head = newStudent;
}

// ����ѧҵ�ɼ�
void insertAcademicScore(StudentInfo* student, AcademicScoreNode* scoreNode) {
    // ���¿γ���ӵ�ѧ����ѧҵ�ɼ�����
    if (student == NULL || scoreNode == NULL) {
        return; // ���ѧ����ɼ��ڵ�Ϊ�գ���ִ�в���
    }

    AcademicScoreNode* current = student->academicScores;
    if (current == NULL) {
        // ���ѧ���ĳɼ�����Ϊ�գ����½ڵ��Ϊ��һ���ڵ�
        student->academicScores = scoreNode;
    }
    else {
        // ��������ֱ���ҵ����һ���ڵ�
        while (current->next != NULL) {
            current = current->next;
        }
        // ���½ڵ���ӵ������ĩβ
        current->next = scoreNode;
    }
}

// �������ʼӷ�
void insertQualityScore(StudentInfo* student, QualityScoreNode* scoreNode) {
    // ���¼ӷ���Ŀ��ӵ�ѧ�������ʼӷ�����
    if (student == NULL || scoreNode == NULL) {
        return; // ���ѧ����ӷֽڵ�Ϊ�գ���ִ�в���
    }

    QualityScoreNode* current = student->qualityScores;
    if (current == NULL) {
        // ���ѧ�������ʼӷ�����Ϊ�գ����½ڵ��Ϊ��һ���ڵ�
        student->qualityScores = scoreNode;
    }
    else {
        // ��������ֱ���ҵ����һ���ڵ�
        while (current->next != NULL) {
            current = current->next;
        }
        // ���½ڵ���ӵ������ĩβ
        current->next = scoreNode;
    }
}

// ����GPA����ѧ�֡���Ȩƽ���֡��ܼ���
void calculateGPA(StudentInfo* student) {
    // ���㲢����ѧ����GPA
    if (student == NULL) {
        return; // ��������ѧ��ָ��Ϊ�գ���ֱ�ӷ���
    }
    float totalQualityPoints = 0.00f; // �����ۼӿγ̵�GPAֵ
    int numCourses = 0; // ���ڼ����γ�����
    float totalCredit = 0.00f;// �����ۼ�ѧ��
    float totalScore = 0.00f; // ���ڼ����Ȩƽ����


    // ����ѧ����ѧҵ�ɼ�����
    AcademicScoreNode* currentScore = student->academicScores;
    while (currentScore != NULL) {
        totalQualityPoints += currentScore->gpa * currentScore->credit; // �ۼ�ÿ���γ̵�GPAֵ��ѧ��
        numCourses++;     // �γ���������
        totalCredit += currentScore->credit;    // �ۼ�ѧ��
        totalScore += currentScore->score * currentScore->credit; // �ۼӷ���
        currentScore = currentScore->next; // �ƶ�����һ���γ̽ڵ�
    }

    // ��ѧ��
    student->totalCredit = totalCredit;

    // �����ȨѧҵGPA
    if (numCourses > 0) {
        student->gpa = totalQualityPoints / totalCredit; // ����ѧҵGPA
    }
    else {
        student->gpa = 0.00f; // ���û�пγ̣�GPAΪ0
    }

    // �ܼ���
    student->totalGPA = student->gpa + student->qualityGpa;

    // �����Ȩƽ����
    student->averageScore = totalScore / totalCredit;
}

// ���㵥�ſγ̼���
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

// ɾ��ѧ����¼
void deleteStudentRecord(StudentInfo** head, char* studentID) {
    // ����ѧ��ɾ��ѧ����¼
    // ʹ��findStudentByID��������ѧ��
    StudentInfo* studentToDelete = findStudentByID(studentID);
    if (studentToDelete != NULL) {
        // ����ҵ���ѧ������������ɾ��
        if (*head == studentToDelete) {
            // ���Ҫɾ������ͷ�ڵ�
            *head = (*head)->next;
        }
        else {
            // ���Ҫɾ�����������м��β���Ľڵ�
            StudentInfo* current = *head;
            while (current->next != studentToDelete) {
                current = current->next;
            }
            current->next = current->next->next;
        }
        free(studentToDelete); // �ͷ�ѧ����¼���ڴ�
        printf("ѧ����¼ɾ���ɹ���\n");
    }
    else {
        // ���û���ҵ�ѧ��IDƥ��Ľڵ㣬��ӡ������Ϣ
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����¼��\n", studentID);
    }
}

// �����������
void handleInputError(const char* message) {
    // ��ʾ������Ϣ
    printf("%s\n", message);
}

// ������ѧ��
StudentInfo* createStudent() {
    // �����ڴ���µ�StudentInfoʵ��
    StudentInfo* newStudent = (StudentInfo*)malloc(sizeof(StudentInfo));
    if (newStudent == NULL) {
        // ����ڴ����ʧ�ܣ���ӡ������Ϣ���˳�����
        fprintf(stderr, "�ڴ����ʧ��\n");
        exit(EXIT_FAILURE);
    }

    // ��ʼ����ѧ����Ϣ
    newStudent->next = NULL; // ��ʼ������ָ��
    newStudent->academicScores = NULL; // ��ʼ��ѧҵ�ɼ�����
    newStudent->qualityScores = NULL; // ��ʼ�����ʼӷ�����
    newStudent->gpa = 0.00f; // ��ʼ��GPA
    newStudent->totalCredit = 0; // ��ʼ����ѧ��
    newStudent->qualityGpa = 0.00f; // ��ʼ�����ʼӷ�GPA
    newStudent->averageScore = 0.00f; // ��ʼ����Ȩƽ����
    strcpy(newStudent->name, "New Student");
    strcpy(newStudent->studentID, "00000000");
    newStudent->classNumber = 1; // ����ѧ���༶Ϊ1
    strcpy(newStudent->password, "123456"); // Ĭ������Ϊ123456

    // ����ѧ����Ϣ
    printf("������ѧ����Ϣ��\n");
    printf("ѧ��: ");
    scanf("%s", newStudent->studentID);
    // ���ѧ���Ƿ��Ѵ���
    if (findStudentByID(newStudent->studentID) != NULL) {
        // ���ѧ���Ѵ��ڣ���ӡ������Ϣ���ͷ��ڴ沢������һ���˵�
        handleInputError("ѧ���Ѵ��ڣ����������롣");
        free(newStudent);
        return NULL;
    }
    printf("����: ");
    scanf("%s", newStudent->name);
    printf("�༶: ");
    scanf("%d", &newStudent->classNumber);
    //    printf("����: ");
    //    scanf("%s", newStudent->password);
        //¼��ѧҵ�ɼ�
    int choice1;
    printf("�Ƿ�����¼��γ̼�¼��(1. �� 2. ��): ");
    scanf("%d", &choice1);
    if (choice1 == 1) {
        int numCourses;
        printf("������ѧ���Ŀγ�������");
        scanf("%d", &numCourses);
        for (int i = 0; i < numCourses; i++) {
            AcademicScoreNode* newCourse = createAcademicScore();
            printf("�������%d�ſγ���Ϣ��\n", i + 1);
            addCourse(newStudent);
        }
    }

    int choice2;
    printf("�Ƿ�����¼�����ʼӷ���Ŀ��¼��(1. �� 2. ��): ");
    scanf("%d", &choice2);
    if (choice2 == 1) {
        //¼�����ʼӷ���Ŀ
        int numProjects;
        printf("������ѧ���ļӷ���Ŀ������");
        scanf("%d", &numProjects);
        for (int i = 0; i < numProjects; i++) {
            QualityScoreNode* newProject = createQualityScore();
            printf("�������%d���ӷ���Ŀ��Ϣ��\n", i + 1);
            addQualityProject(newStudent);
        }
    }

    // �����´�����StudentInfoָ��
    return newStudent;
}

// ������ѧҵ�ɼ�
AcademicScoreNode* createAcademicScore() {
    // �����ڴ���µ�AcademicScoreNodeʵ��
    AcademicScoreNode* newCourse = (AcademicScoreNode*)malloc(sizeof(AcademicScoreNode));
    if (newCourse == NULL) {
        // ����ڴ����ʧ�ܣ���ӡ������Ϣ���˳�����
        fprintf(stderr, "�ڴ����ʧ��\n");
        exit(EXIT_FAILURE);
    }
    // ��ʼ���¿γ���Ϣ
    newCourse->next = NULL; // ��ʼ������ָ��
    strcpy(newCourse->courseName, "Unknown Course"); // ��ʼ���γ�����
    newCourse->score = 0.00f; // ��ʼ���γ̷���
    newCourse->credit = 0.0f; // ��ʼ���γ�ѧ��
    newCourse->gpa = 0.0f; // ��ʼ���γ̼���
    printf("������γ���Ϣ��\n");
    printf("�γ�����: ");
    scanf("%s", newCourse->courseName);
    printf("����: ");
    scanf("%f", &newCourse->score);
    printf("ѧ��: ");
    scanf("%f", &newCourse->credit);
    newCourse->gpa = calculateSingleGPA(&newCourse->score); // ����γ̼���
    // �����´�����AcademicScoreNodeָ��
    return newCourse;
}

// ���������ʼӷ�
QualityScoreNode* createQualityScore() {
    // �����ڴ���µ�QualityScoreNodeʵ��
    QualityScoreNode* newProject = (QualityScoreNode*)malloc(sizeof(QualityScoreNode));
    if (newProject == NULL) {
        // ����ڴ����ʧ�ܣ���ӡ������Ϣ���˳�����
        fprintf(stderr, "�ڴ����ʧ��\n");
        exit(EXIT_FAILURE);
    }
    newProject->gpaContribution = 0.0; // Ĭ�ϼӷ�ֵ��ʼ��Ϊ0.0
    printf("������ӷ���Ŀ��Ϣ��\n");
    printf("��Ŀ����: ");
    scanf("%s", newProject->projectTitle);
    printf("�ӷ�: ");
    scanf("%f", &newProject->gpaContribution);
    newProject->next = NULL;
    // �����´�����QualityScoreNodeָ��
    return newProject;
}

// ����ѧ��
StudentInfo* findStudentByID(const char* studentID) {
    // ����ѧ���б�����ָ��ѧ�ŵ�ѧ��
    // ��ѧ���б��ͷ����ʼ����
    StudentInfo* currentStudent = studentsList;

    // ��������ѧ���б�
    while (currentStudent != NULL) {
        // �Ƚϵ�ǰѧ����ѧ���������ѧ��
        if (strcmp(currentStudent->studentID, studentID) == 0) {
            // ����ҵ�ƥ���ѧ�ţ����ص�ǰѧ������Ϣ
            return currentStudent;
        }
        // �ƶ����������һ���ڵ�
        currentStudent = currentStudent->next;
    }
    // ��������������б�û���ҵ�ƥ���ѧ�ţ�����NULL
    return NULL;
}

// ���ҹ���Ա
AdminInfo* findAdminByUsername(const char* username) {
    // �Ƚϸ������û����͹���Ա���û���
    if (strcmp(adminsList->username, username) == 0) {
        // ����ҵ�ƥ����û��������ع���Ա��Ϣ
        return adminsList;
    }
    // ���û���ҵ�ƥ����û���������NULL
    return NULL;
}


// �༭ѧ��ѧҵ�ɼ�
void modifyAcademicScore(StudentInfo* student) {
    // �޸�ѧҵ�ɼ�
    int choice;
    printf("��ѡ���޸����ͣ�\n");
    printf("1. �޸Ŀγ�����\n");
    printf("2. �޸ķ���\n");
    printf("3. �޸�ѧ��\n");
    printf("4. ɾ���γ�\n");
    printf("5. ������һ���˵�\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        // �޸Ŀγ�����
    {
        if (student->academicScores == NULL) {
            printf("��ǰû�пγ̿����޸ġ�\n");
            break;
        }
        AcademicScoreNode* current = student->academicScores;
        printf("������Ҫ�޸ĵĿγ����ƣ�����q�˳�����");
        char courseName[MAX_NAME_LENGTH];
        scanf("%s", courseName);
        if (strcmp(courseName, "q") == 0) {
            break;
        }
        while (current != NULL) {
            if (strcmp(current->courseName, courseName) == 0) {
                printf("�ҵ��γ�: %s, ��ǰ����: %.2f\n", current->courseName, current->score);
                printf("�������µĿγ�����: ");
                scanf("%s", current->courseName);
                printf("�γ������޸ĳɹ���\n");
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("δ�ҵ�ָ���Ŀγ̡�\n");
        }
    }
        break;
    case 2:
        // �޸ķ���
    {
        if (student->academicScores == NULL) {
            printf("��ǰû�пγ̿����޸ġ�\n");
            break;
        }
        AcademicScoreNode* currentScore = student->academicScores;
        printf("������Ҫ�޸ĵĿγ����ƣ�����q�˳�����");
        char scoreCourseName[MAX_NAME_LENGTH];
        scanf("%s", scoreCourseName);
        if (strcmp(scoreCourseName, "q") == 0) {
            break;
        }
        while (currentScore != NULL) {
            if (strcmp(currentScore->courseName, scoreCourseName) == 0) {
                printf("�ҵ��γ�: %s, ��ǰ����: %.2f\n", currentScore->courseName, currentScore->score);
                printf("�������µķ���: ");
                scanf("%2f", &currentScore->score);
                currentScore->gpa = calculateSingleGPA(&currentScore->score);//���¼��㵱ǰ�γ̼���
                calculateGPA(student);//���¼���GPA\��ѧ��\��Ȩƽ����\�ܼ���
                printf("�����޸ĳɹ���\n");
                break;
            }
            currentScore = currentScore->next;
        }
        if (currentScore == NULL) {
            printf("δ�ҵ�ָ���Ŀγ̡�\n");
        }
    }
        break;
    case 3:
        // �޸�ѧ��
    {
        if (student->academicScores == NULL) {
            printf("��ǰû�пγ̿����޸ġ�\n");
            break;
        }
        AcademicScoreNode* currentCredit = student->academicScores;
        printf("������Ҫ�޸ĵĿγ����ƣ�����q�˳�����");
        char creditCourseName[MAX_NAME_LENGTH];
        scanf("%s", creditCourseName);
        if (strcmp(creditCourseName, "q") == 0) {
            break;
        }
        while (currentCredit != NULL) {
            if (strcmp(currentCredit->courseName, creditCourseName) == 0) {
                printf("�ҵ��γ�: %s, ��ǰѧ��: %.2f\n", currentCredit->courseName, currentCredit->credit);
                printf("�������µ�ѧ��: ");
                scanf("%2f", &currentCredit->credit);
                calculateGPA(student);  //���¼���GPA\��ѧ��\��Ȩƽ����\�ܼ���
                printf("ѧ���޸ĳɹ���\n");
                break;
            }
            currentCredit = currentCredit->next;
        }
        if (currentCredit == NULL) {
            printf("δ�ҵ�ָ���Ŀγ̡�\n");
        }
    }
        break;
    case 4:
        // ɾ���γ�
    {
        if (student->academicScores == NULL) {
            printf("��ǰû�пγ̿���ɾ����\n");
            break;
        }
        AcademicScoreNode* currentDelete = student->academicScores;
        AcademicScoreNode* prev = NULL;
        printf("������Ҫɾ���Ŀγ����ƣ�����q�˳�����");
        char deleteCourseName[MAX_NAME_LENGTH];
        scanf("%s", deleteCourseName);
        if (strcmp(deleteCourseName, "q") == 0) {
            break;
        }
        while (currentDelete != NULL) {
            if (strcmp(currentDelete->courseName, deleteCourseName) == 0) {
                if (prev == NULL) {
                    // Ҫɾ������ͷ�ڵ�
                    student->academicScores = currentDelete->next;
                }
                else {
                    // Ҫɾ�������м��β�ڵ�
                    prev->next = currentDelete->next;
                }
                AcademicScoreNode* temp = currentDelete;
                currentDelete = currentDelete->next;
                free(temp); // �ͷű�ɾ���ڵ���ڴ�
                calculateGPA(student);  //���¼���GPA\��ѧ��\��Ȩƽ����\�ܼ���
                printf("�γ�ɾ���ɹ���\n");
                break;
            }
            prev = currentDelete;
            currentDelete = currentDelete->next;
        }
        if (currentDelete == NULL) {
            printf("δ�ҵ�ָ���Ŀγ̡�\n");
        }
    }
        break;
    case 5:
        printf("������һ���˵���\n");
        // ������һ���˵�
        break;
    default:
        printf("��Ч��ѡ�\n");
    }
}


// �༭ѧ�����ʼӷ�
void modifyQualityScore(StudentInfo* student) {
    // �޸����ʼӷ�
    if (student == NULL) {
        handleInputError("ѧ����Ϣ����Ϊ�ա�\n");
        return;
    }

    int choice;
    printf("��ѡ���޸����ͣ�\n");
    printf("1. �޸ļӷ���Ŀ\n");
    printf("2. ɾ���ӷ���Ŀ\n");
    printf("3. ������һ���˵�\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        // �޸ļӷ���Ŀ
    {
        if (student->qualityScores == NULL) {
            printf("��ǰû�мӷ���Ŀ�����޸ġ�\n");
            break;
        }
        QualityScoreNode* current = student->qualityScores;
        printf("������Ҫ�޸ĵļӷ���Ŀ���ƣ�����q�˳�����");
        char projectTitle[MAX_NAME_LENGTH];
        scanf("%s", projectTitle);
        if (strcmp(projectTitle, "q") == 0) {
            break;
        }
        while (current != NULL) {
            if (strcmp(current->projectTitle, projectTitle) == 0) {
                printf("�ҵ��ӷ���Ŀ: %s, ��ǰ�ӷ�: %.2f\n", current->projectTitle, current->gpaContribution);
                printf("�������µļӷ�: ");
                scanf("%f", &current->gpaContribution);
                calculateGPA(student);  //���¼���GPA\��ѧ��\��Ȩƽ����\�ܼ���
                printf("�ӷ���Ŀ�޸ĳɹ���\n");
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("δ�ҵ�ָ���ļӷ���Ŀ��\n");
        }
    }
        break;
    case 2:
        // ɾ���ӷ���Ŀ
    {
        if (student->qualityScores == NULL) {
            printf("��ǰû�мӷ���Ŀ����ɾ����\n");
            break;
        }
        QualityScoreNode* currentDelete = student->qualityScores;
        QualityScoreNode* prev = NULL;
        printf("������Ҫɾ���ļӷ���Ŀ���ƣ�����q�˳�����");
        char deleteTitle[MAX_NAME_LENGTH];
        scanf("%s", deleteTitle);
        if (strcmp(deleteTitle, "q") == 0) {
            break;
        }
        while (currentDelete != NULL) {
            if (strcmp(currentDelete->projectTitle, deleteTitle) == 0) {
                if (prev == NULL) {
                    // Ҫɾ������ͷ�ڵ�
                    student->qualityScores = currentDelete->next;
                }
                else {
                    // Ҫɾ�������м��β�ڵ�
                    prev->next = currentDelete->next;
                }
                QualityScoreNode* temp = currentDelete;
                currentDelete = currentDelete->next;
                free(temp); // �ͷű�ɾ���ڵ���ڴ�
                calculateGPA(student);  //���¼���GPA\��ѧ��\��Ȩƽ����\�ܼ���
                printf("�ӷ���Ŀɾ���ɹ���\n");
                break;
            }
            prev = currentDelete;
            currentDelete = currentDelete->next;
        }
        if (currentDelete == NULL) {
            printf("δ�ҵ�ָ���ļӷ���Ŀ��\n");
        }
    }
        break;
    case 3:
        printf("������һ���˵���\n");
        // ������һ���˵�
        break;
    default:
        printf("��Ч��ѡ�\n");
    }
}

// ��ʾѧ����ȫ��ѧҵ�ɼ�
void displayAcademicScore(StudentInfo* student) {
    // ��ʾѧ����ѧҵ�ɼ�
    if (student == NULL) {
        printf("ѧ����ϢΪ�ա�\n");
        return;
    }
    AcademicScoreNode* current = student->academicScores;
    if (current == NULL) {
        printf("ѧ��û��ѧҵ�ɼ���\n");
        return;
    }
    printf("ѧҵ�ɼ���\n");
    while (current != NULL) {
        printf("�γ�����: %s, ѧ��: %.2f, ����: %.2f, ����: %.2f\n", current->courseName, current->credit, current->score, current->gpa);
        current = current->next;
    }
    printf("����ѧҵ�ɼ���ȫ����ʾ��ɡ�\n");
}

// ��ʾѧ����ȫ�����ʼӷ�
void displayQualityScore(StudentInfo* student) {
    // ��ʾѧ�������ʼӷ�
    if (student == NULL) {
        printf("ѧ����ϢΪ�ա�\n");
        return;
    }
    QualityScoreNode* current = student->qualityScores;
    if (current == NULL) {
        printf("ѧ��û�����ʼӷ֡�\n");
        return;
    }
    printf("���ʼӷ֣�\n");
    while (current != NULL) {
        printf("��Ŀ����: %s, �ӷ�: %.2f\n", current->projectTitle, current->gpaContribution);
        current = current->next;
    }
    printf("�������ʼӷ���ȫ����ʾ��ɡ�\n");
}

//�ͷŹ���Ա�ڴ�
void freeAdminMemory(AdminInfo** head) {
    // ������Ա�б�ͷָ���Ƿ�Ϊ��
    if (*head == NULL) {
        return; // ���ͷָ��Ϊ�գ���û���ڴ���Ҫ�ͷ�
    }
    // �ͷŵ�ǰ����Ա�ڵ���ڴ�
    AdminInfo* tempAdmin = *head;
    *head = NULL;
    free(tempAdmin); // �ͷŽڵ��ڴ�
}

//��ʾ����ѧ���ſ�
void displayAllStudent(StudentInfo* head) {
    // ��ʾ����ѧ������Ϣ
    if (head == NULL) {
        printf("ѧ����ϢΪ�ա�\n");
        return;
    }
    StudentInfo* current = head;
    while (current != NULL) {
        printf("ѧ��: %s\n", current->studentID);
        printf("����: %s\n", current->name);
        printf("�༶: %d\n", current->classNumber);
        printf("�ѻ���ѧ��: %.2f\n", current->totalCredit);
        printf("ѧҵGPA: %f\n", current->gpa);
        printf("���ʼӷ�GPA: %.2f\n", current->qualityGpa);
        printf("��Ȩƽ����: %.2f\n", current->averageScore);
        printf("�ܼ���: %.2f\n", current->totalGPA);
        printf("\n\n");
        current = current->next;
    }
    printf("\n");
    printf("����ѧ����Ϣ��ȫ����ʾ��ɡ�\n");
}

//����ѧ������
void sortList(StudentInfo** head, int (*compare)(const StudentInfo*, const StudentInfo*)) {
    int swapped;
    StudentInfo* current;
    StudentInfo* prev = NULL;
    do {
        swapped = 0;
        current = *head;
        while (current && current->next) {
            if ((*compare)(current, current->next) > 0) {
                // ���������ڵ������
                StudentInfo temp = *current;
                *current = *(current->next);
                *(current->next) = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// �ȽϺ�������ѧ������
int compareByStudentID(const StudentInfo* a, const StudentInfo* b) {
    return strcmp(a->studentID, b->studentID);
}

// �ȽϺ�������ѧҵGPA����
int compareByGPA(const StudentInfo* a, const StudentInfo* b) {
    if (a->gpa > b->gpa) return -1;
    if (a->gpa < b->gpa) return 1;
    return 0;
}

// �ȽϺ���������Ȩƽ��������
int compareByAverageScore(const StudentInfo* a, const StudentInfo* b) {
    if (a->averageScore > b->averageScore) return -1;
    if (a->averageScore < b->averageScore) return 1;
    return 0;
}

// �ȽϺ��������ܼ�������
int compareByTotalGPA(const StudentInfo* a, const StudentInfo* b) {
    if (a->totalGPA > b->totalGPA) return -1;
    if (a->totalGPA < b->totalGPA) return 1;
    return 0;
}

// ��ӹ���Ա�˺�
void addAdminAccount() {
    AdminInfo* newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo)); // �����¹���Ա�ڴ�
    if (newAdmin == NULL) {
        handleInputError("�ڴ����ʧ�ܣ��޷���ӹ���Ա�˺š�\n");
        return;
    }

    printf("���������Ա�û���: ");
    scanf("%s", newAdmin->username);
    // ����û����Ƿ��Ѵ���
    while (findAdminByUsername(newAdmin->username) != NULL) {
        printf("�û����Ѵ��ڣ�����������: ");
        scanf("%s", newAdmin->username);
    }

    printf("���������Ա����: ");
    scanf("%s", newAdmin->password);

    // ���¹���Ա��ӵ�����ͷ��
    newAdmin->next = adminsList;
    adminsList = newAdmin;

    printf("����Ա�˺���ӳɹ���\n");
}

// ���浽�ļ�
void saveToFile() {
    //д��ѧ����Ϣ���ļ�
    FILE* file = fopen("students.txt", "w"); // ���ļ������ı�д��
    if (file == NULL) {
        perror("�޷����ļ�����д��");
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

        // ����ѧҵ�ɼ�����д��
        AcademicScoreNode* score = current->academicScores;
        while (score != NULL) {
            fprintf(file, "%s %f %f %f\n", score->courseName, score->score, score->credit, score->gpa);
            score = score->next;
        }

        // �������ʼӷ�����д��
        QualityScoreNode* project = current->qualityScores;
        while (project != NULL) {
            fprintf(file, "%s %f\n", project->projectTitle, project->gpaContribution);
            project = project->next;
        }

        current = current->next; // �ƶ�����һ��ѧ��
    }
    fclose(file); // �ر��ļ�

    //д�����Ա��Ϣ���ļ�
    FILE* adminFile = fopen("admins.txt", "w"); // ���ļ������ı�д��
    if (adminFile == NULL) {
        perror("�޷����ļ�����д��");
        return;
    }

    AdminInfo* currentAdmin = adminsList;
    while (currentAdmin != NULL) {
        fprintf(adminFile, "%s %s\n", currentAdmin->username, currentAdmin->password);
        currentAdmin = currentAdmin->next; // �ƶ�����һ������Ա
    }
    fclose(adminFile); // �ر��ļ�
}

// ���ļ�����
void loadFromFile() {
    // ���ļ�����ѧ����Ϣ
    FILE* file = fopen("students.txt", "r"); // ���ļ������ı���ȡ
    if (file == NULL) {
        perror("�޷����ļ����ж�ȡ");
        return;
    }

    // ��յ�ǰѧ���б�
    freeMemory(&studentsList);

    StudentInfo* newStudent;
    AcademicScoreNode* newScore{};
    QualityScoreNode* newProject{};

    // ��ʱ�������ڶ�ȡ
    char tempID[8], tempName[15], tempPassword[15];
    int tempClassNumber;
    float tempGPA, tempTotalCredit, tempQualityGPA, tempAverageScore, tempTotalGPA;
    char courseName[MAX_NAME_LENGTH], projectTitle[MAX_NAME_LENGTH];

    while (!feof(file)) {
        // ��ȡѧ��������Ϣ
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

        // ��ȡѧҵ�ɼ�����ӵ�ѧ����¼
        while (!feof(file)) {
            fscanf(file, "%s %f %f %f", courseName, &newScore->score, &newScore->credit, &newScore->gpa);
            newScore = createAcademicScore();
            insertAcademicScore(newStudent, newScore);
        }

        // ��ȡ���ʼӷֲ���ӵ�ѧ����¼
        while (!feof(file)) {
            fscanf(file, "%s %f", projectTitle, &newProject->gpaContribution);
            newProject = createQualityScore();
            insertQualityScore(newStudent, newProject);
        }

        // ����ѧ����ӵ��б�ͷ��
        insertStudent(&studentsList, newStudent);
    }

    fclose(file); // �ر��ļ�

    // ���ļ����ع���Ա��Ϣ
    FILE* adminFile = fopen("admins.txt", "r"); // ���ļ������ı���ȡ
    if (adminFile == NULL) {
        perror("�޷����ļ����ж�ȡ");
        return;
    }

    // ��յ�ǰ����Ա�б�
    freeAdminMemory(&adminsList);

    AdminInfo* newAdmin;
    char tempAdminName[15];
    char tempAdminPassword[15];

    while (!feof(adminFile)) {
        // ��ȡ����Ա��Ϣ
        fscanf(adminFile, "%s %s", tempAdminName, tempAdminPassword);
        newAdmin = (AdminInfo*)malloc(sizeof(AdminInfo));
        strcpy(newAdmin->username, tempAdminName);
        strcpy(newAdmin->password, tempAdminPassword);
        newAdmin->next = adminsList;
        adminsList = newAdmin;
    }

    fclose(adminFile); // �ر��ļ�
}