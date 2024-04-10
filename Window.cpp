#include "Window.h"
#include <graphics.h>
#include "function.h"

void windowInit(Window* w,int width, int height)
{
	cleardevice();
	w->wid.height = height;
	w->wid.width = width;
	w->isEdit = false;
	w->hWnd = initgraph(width, height, EX_NOCLOSE);
	SetWindowText(w->hWnd, L"ѧ���ɼ�����ϵͳ");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(w->hWnd, SW_HIDE);

	// ���û�ͼ��ʽ
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	// ������ť
	

	w->mainWindow_view	 = new Button();
	buttonInit(w->mainWindow_view, (1024 - 200) / 2, 150, 170, 30, L"�鿴ѧ��");
	w->mainWindow_view_admin = new Button();
	buttonInit(w->mainWindow_view_admin, (1024 - 200) / 2, 200, 170, 30, L"�鿴����Ա");
	w->mainWindow_edit = new Button();
	buttonInit(w->mainWindow_edit, (1024 - 200) / 2, 250, 170, 30, L"�༭ѧ��");
	w->mainWindow_edit_admin = new Button();
	buttonInit(w->mainWindow_edit_admin, (1024 - 200) / 2, 300, 170, 30, L"�༭����Ա");
	w->mainWindow_clear = new Button();
	buttonInit(w->mainWindow_clear, (1024 - 200) / 2, 350, 170, 30, L"�������");
	w->mainWindow_exit = new Button();
	buttonInit(w->mainWindow_exit, (1024 - 200) / 2, 400, 170, 30, L"�˳�����");
	w->mainWindow_cmd = new Button();
	buttonInit(w->mainWindow_cmd, (1024 - 200) / 2, 450, 170, 30, L"��ʾ�ն˳���");
	w->viewStudents_pageUp = new Button();
	buttonInit(w->viewStudents_pageUp, 10, 380, 80, 30, L"��һҳ");
	w->viewStudents_pageDown = new Button();
	buttonInit(w->viewStudents_pageDown, 210, 380, 80, 30, L"��һҳ");
	w->viewStudents_back = new Button();
	buttonInit(w->viewStudents_back, 412, 380, 80, 30, L"����");
	w->viewStudents_sort = new Button();
	buttonInit(w->viewStudents_sort, 300, 380, 102, 30, L"���ܷ�����");
	w->editStudents_search = new Button();
	buttonInit(w->editStudents_search, 10, 380, 100, 30, L"����ѧ��");
	w->editStudents_add = new Button();
	buttonInit(w->editStudents_add, 137, 380, 100, 30, L"���ѧ��");
	w->editStudents_delete = new Button();
	buttonInit(w->editStudents_delete, 264, 380, 100, 30, L"ɾ��ѧ��");
	w->editStudents_back = new Button();
	buttonInit(w->editStudents_back, 392, 380, 100, 30, L"����");

	showMainWindow(w);	// ��ʾ������

	// �������
	w->table = new Table();

	tableInit(w->table, w->manager, 10, 10, 502 - 20, 420 - 60);
}

void windowDelete(Window* w)
{
	// ����
	delete w->mainWindow_view;
	delete w->mainWindow_view_admin;
	delete w->mainWindow_edit_admin;
	delete w->mainWindow_edit;
	delete w->mainWindow_clear;
	delete w->mainWindow_exit;

	delete w->viewStudents_pageUp;
	delete w->viewStudents_pageDown;
	delete w->viewStudents_sort;
	delete w->viewStudents_back;

	delete w->editStudents_search;
	delete w->editStudents_add;
	delete w->editStudents_delete;
	delete w->editStudents_back;

	delete w->table;
	delete w->mainWindow_cmd;
}

void windowShow(Window* w)
{
	ShowWindow(w->hWnd, SW_SHOW);
}
// ��ѧ�Ų���ѧ��
StudentInfo* findStudentByID_ui(const char* studentID, StudentInfo* studentsList);
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
// �༭ѧ���ɼ���ɾ��ѧ��
void modifyScoreMenu_ui(StudentInfo* studentList) {
	char studentID[8];
	printf("������ѧ��ѧ��: ");
	scanf("%s", studentID);
	StudentInfo* student = findStudentByID_ui(studentID, studentList);
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
// ������ѧ��
StudentInfo* createStudent_ui(StudentInfo* student) {
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
	newStudent->innovationProjects = NULL; // ��ʼ����ѧ�����´�ҵ�ƻ���Ŀ����
	newStudent->academicPapers = NULL; // ��ʼ��ѧ����������
	newStudent->competitions = NULL; // ��ʼ���������ѧ�ƾ�������
	newStudent->gpa = 0.00f; // ��ʼ��GPA
	newStudent->totalCredit = 0; // ��ʼ����ѧ��
	newStudent->qualityGpa = 0.00f; // ��ʼ�����ʼӷ�GPA
	newStudent->averageScore = 0.00f; // ��ʼ����Ȩƽ����
	strcpy(newStudent->name, "New Student");
	strcpy(newStudent->studentID, "00000000");
	newStudent->classNumber = 1; // ����ѧ���༶Ϊ1
	newStudent->grade = 1; // ȱʡֵѧ���꼶Ϊ1
	strcpy(newStudent->password, "123456"); // Ĭ������Ϊ123456
	// ����ѧ����Ϣ
	printf("������ѧ����Ϣ��\n");
	printf("ѧ��: ");
	scanf("%s", newStudent->studentID);
	// �ж�ѧ���Ƿ���8λ����
	while (!isStudentIDValid(newStudent->studentID)) {
		handleInputError("ѧ��ӦΪ8λ���֣����������롣\n");
		scanf("%s", newStudent->studentID);
	}
	// ���ѧ���Ƿ��Ѵ���
	if (findStudentByID_ui(newStudent->studentID, student) != NULL) {
		// ���ѧ���Ѵ��ڣ���ӡ������Ϣ���ͷ��ڴ沢������һ���˵�
		handleInputError("ѧ���Ѵ��ڣ����������롣");
		free(newStudent);
		return NULL;
	}
	printf("����: ");
	scanf("%s", newStudent->name);
	printf("�༶: ");
	scanf("%d", &(newStudent->classNumber));
	//�жϰ༶�Ƿ�Ϸ�
	while (!isClassValid(newStudent->classNumber)) {
		handleInputError("�༶ӦΪ����0���������������롣\n");
		scanf("%d", &newStudent->classNumber);
	}

	printf("�꼶: ");
	scanf("%d", &newStudent->grade);
	//�ж��꼶�Ƿ�Ϸ�
	while (!isGradeValid(newStudent->grade)) {
		handleInputError("�꼶ӦΪ1-4֮�����(1.��һ 2.��� 3.���� 4.����)�����������롣\n");
		scanf("%d", &newStudent->grade);
	}

	//¼��ѧҵ�ɼ�
	int choice1;
	printf("�Ƿ�����¼��γ̼�¼��(1. �� 2. ��): ");
	scanf("%d", &choice1);
	//�ж�ѡ���Ƿ�Ϸ�
	while (choice1 != 1 && choice1 != 2) {
		handleInputError("ѡ��ӦΪ1��2�����������롣\n");
		scanf("%d", &choice1);
	}
	if (choice1 == 1) {
		int numCourses;
		printf("������Ҫ����Ŀγ�������");
		scanf("%d", &numCourses);
		for (int i = 0; i < numCourses; i++) {
			printf("�������%d�ſγ���Ϣ��\n", i + 1);
			addCourse(newStudent);
		}
		calculateAcademics(newStudent);
	}

	int choice2;
	printf("�Ƿ�����¼�����ʼӷ���Ŀ��¼��(1. �� 2. ��): ");
	scanf("%d", &choice2);
	//�ж�ѡ���Ƿ�Ϸ�
	while (choice2 != 1 && choice2 != 2) {
		handleInputError("ѡ��ӦΪ1��2�����������롣\n");
		scanf("%d", &choice2);
	}
	if (choice2 == 1) {
		//¼�����ʼӷ���Ŀ
		addQualityProject(newStudent);
		calculateQualityGPA(newStudent);
		calculateAcademics(newStudent);
	}
	// �����´�����StudentInfoָ��
	return newStudent;
}
// ���ѧ���˺�
char* addStudentAccount_ui(StudentInfo* studentList) {
	StudentInfo* newStudent = createStudent_ui(studentList);
	// ����GPA
	calculateGPA(newStudent);
	// ����ѧ���б�
	insertStudent(&studentList, newStudent);
	printf("ѧ���˺Ŵ����ɹ���\n");
	return newStudent->name;
}
//���º�������Ҫ�޸ĳ�ǰ�˸�ʽ

void saveToFile_ui(StudentInfo* studensList) {
	FILE* file = fopen("student.txt", "w");
	if (file == NULL) {
		handleInputError("���ļ�ʧ��");
		return;
	}

	StudentInfo* currentStudent = studentsList;
	while (currentStudent != NULL) {
		// ѧ����¼��ʼ
		fprintf(file, "%s\n", STUDENT_START);

		//        char studentID[8];// ѧ��
		//        char name[15];// ����
		//        char password[15];// ����
		//        int classNumber;// �༶
		//        float gpa;  // ѧҵGPA
		//        float totalCredit;// ��ѧ��
		//        float qualityGpa;// ���ʼӷ�GPA
		//        float averageScore;// ��Ȩƽ����
		//        float totalGPA;// �ܼ���

				// д��ѧ��������Ϣ
		fprintf(file, "StudentID: %s\n", currentStudent->studentID);// ѧ��
		fprintf(file, "Name: %s\n", currentStudent->name);// ����
		fprintf(file, "Password: %s\n", currentStudent->password);// ����
		fprintf(file, "Grade: %d\n", currentStudent->grade);// �꼶
		fprintf(file, "ClassNumber: %d\n", currentStudent->classNumber);// �༶
		fprintf(file, "GPA: %f\n", currentStudent->gpa);// ѧҵGPA
		fprintf(file, "TotalCredit: %.2f\n", currentStudent->totalCredit);// ��ѧ��
		fprintf(file, "QualityGPA: %.2f\n", currentStudent->qualityGpa);// ���ʼӷ�GPA
		fprintf(file, "AverageScore: %f\n", currentStudent->averageScore);// ��Ȩƽ����
		fprintf(file, "TotalGPA: %f\n", currentStudent->totalGPA);// �ܼ���

//        char courseName[MAX_NAME_LENGTH];
//        float score;    // ����
//        float credit; // ѧ��
//        float gpa; // ���ſγ̼���
		// ѧҵ�ɼ�����
		if (currentStudent->academicScores != NULL) {
			fprintf(file, "%s\n", SCORE_START);
			AcademicScoreNode* currentScore = currentStudent->academicScores;
			while (currentScore != NULL) {
				fprintf(file, "CourseName: %s\n", currentScore->courseName);
				fprintf(file, "Score: %f\n", currentScore->score);
				fprintf(file, "Credit: %.2f\n", currentScore->credit);
				fprintf(file, "GPA: %.2f\n", currentScore->gpa);
				currentScore = currentScore->next;
			}
			fprintf(file, "%s\n", SCORE_END);
		}

		//        char projectName[MAX_NAME_LENGTH]; // ��Ŀ����
		//        float gpa; // �ӷ�ֵ
		//        int isLeaderOrSecondLeader;// �Ƿ�Ϊ��Ŀ������,�Ƿ�Ϊ�ڶ������ˣ����Ҽ����������Ŀ�����˼�0.1 GPA���ڶ�����0.05 GPA
		//        char projectLevel[10];// ��Ŀ���𣬹��Ҽ���ʡ����У��
		//        int isFinished;    // �Ƿ����
				// ��ѧ�����´�ҵ�ƻ���Ŀ����
		if (currentStudent->innovationProjects != NULL) {
			fprintf(file, "%s\n", PROJECT_START);
			InnovationProject* currentProject = currentStudent->innovationProjects;
			if (currentProject != NULL) {
				fprintf(file, "ProjectName: %s\n", currentProject->projectName);
				fprintf(file, "GPA: %.2f\n", currentProject->gpa);
				fprintf(file, "LeaderOrSecondLeader: %d\n", currentProject->isLeaderOrSecondLeader);
				fprintf(file, "ProjectLevel: %s\n", currentProject->projectLevel);
				fprintf(file, "IsFinished: %d\n", currentProject->isFinished);
			}
			fprintf(file, "%s\n", PROJECT_END);
		}

		//        char title[MAX_NAME_LENGTH]; // ���ı���
		//        char journalName[MAX_NAME_LENGTH]; // �ڿ�����
		//        int isFirstAuthor; // �Ƿ�Ϊ��һ����
		//
		//        //�ڿ����𣬶�����0.4��һ���ڿ���0.2 GPA�������ڿ���0.1 GPA�������ڿ���0.05 GPA���ļ��ڿ���0.02 GPA���弶�ڿ���0.01 GPA
		//        int journalLevel;
		//
		//        float gpa; // �ӷ�ֵ
				// ѧ����������
		if (currentStudent->academicPapers != NULL) {
			fprintf(file, "%s\n", PAPER_START);
			AcademicPaper* currentPaper = currentStudent->academicPapers;
			while (currentPaper != NULL) {
				fprintf(file, "Title: %s\n", currentPaper->title);
				fprintf(file, "JournalName: %s\n", currentPaper->journalName);
				fprintf(file, "IsFirstAuthor: %d\n", currentPaper->isFirstAuthor);
				fprintf(file, "JournalLevel: %d\n", currentPaper->journalLevel);
				fprintf(file, "GPA: %.2f\n", currentPaper->gpa);
				currentPaper = currentPaper->next;
			}
			fprintf(file, "%s\n", PAPER_END);
		}

		//        char competitionName[MAX_NAME_LENGTH]; // ��������
		//        int teamSize;   //������������
		//        char competitionLevel[10]; // ��������,���Ҽ���ʡ����У��
		//        int rank;   // �񽱵ȼ���1��ʾһ�Ƚ���2��ʾ���Ƚ���3��ʾ���Ƚ�
		//        char competitionType;   //�������A�࣬B�࣬C��
		//        float gpa; // �ӷ�ֵ
				// �������ѧ�ƾ�������
		if (currentStudent->competitions != NULL) {
			fprintf(file, "%s\n", COMPETITION_START);
			Competition* currentCompetition = currentStudent->competitions;
			while (currentCompetition != NULL) {
				fprintf(file, "CompetitionName: %s\n", currentCompetition->competitionName);
				fprintf(file, "TeamSize: %d\n", currentCompetition->teamSize);
				fprintf(file, "CompetitionLevel: %s\n", currentCompetition->competitionLevel);
				fprintf(file, "Rank: %d\n", currentCompetition->rank);
				fprintf(file, "CompetitionType: %c\n", currentCompetition->competitionType);
				fprintf(file, "GPA: %.2f\n", currentCompetition->gpa);
				currentCompetition = currentCompetition->next;
			}
			fprintf(file, "%s\n", COMPETITION_END);
		}

		// ѧ����¼����
		fprintf(file, "%s\n", STUDENT_END);

		currentStudent = currentStudent->next;
	}
	fclose(file);//�ر��ļ�

	// �������Ա��Ϣ
	FILE* adminFile = fopen("admin.txt", "w");
	if (adminFile == NULL) {
		handleInputError("���ļ�ʧ��");
		return;
	}
	AdminInfo* currentAdmin = adminsList;
	while (currentAdmin != NULL) {
		fprintf(adminFile, "%s\n", ADMIN_START);
		fprintf(adminFile, "Username: %s\n", currentAdmin->username);
		fprintf(adminFile, "Password: %s\n", currentAdmin->password);
		fprintf(adminFile, "%s\n", ADMIN_END);
		currentAdmin = currentAdmin->next;
	}
	fclose(adminFile);//�ر��ļ�

	printf("����ɹ���\n");
}


void messageLoop(Window* w)
{
	// ������Ϣѭ��
	ExMessage msg;
	while (true)
	{
		// ��ȡ���ж���Ϣ
		msg = getmessage();

		// �ж���ʾ����
		if (w->state == WindowState::mainWindow)		// ��������ʾ
		{
			if (state(msg, w->mainWindow_view))		// �鿴ѧ��
			{
				showViewStudents(w);
			}
			else if (state(msg, w->mainWindow_edit_admin))	// �༭ѧ��
			{
				showEditAdmins(w);
			}
			else if (state(msg, w->mainWindow_view_admin))	// �༭ѧ��
			{
				showViewAdmins(w);
			}
			else if (state(msg, w->mainWindow_edit))	// �༭ѧ��
			{
				showEditStudents(w);
			}
			else if (state(msg, w->mainWindow_clear))	// �������
			{
				if (MessageBox(GetHWnd(), L"ȷ��Ҫ�������ѧ�����ݣ�", L"�������", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					// ȷ�����
					FILE* file = fopen("student.txt", "w");
					freeMemory(&(w->manager.students));
				}
			}
			else if (state(msg, w->mainWindow_exit))	// �˳�����
			{
				if (MessageBox(GetHWnd(), L"ȷ���˳�������", L"�˳�����", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					if (close(w))
					{
						return;
					}
				}

			}
			else if (state(msg, w->mainWindow_cmd))
			{
				showCmd();
			}
			else
			{
				continue;
			}
		}
		else if (w->state == WindowState::viewStudents)	// �鿴ѧ��������ʾ
		{
			if (state(msg, w->viewStudents_pageUp) && msg.message != WM_LBUTTONUP)			// ��һҳ
			{
				pageUp(w->table);
			}
			else if (state(msg, w->viewStudents_pageDown) && msg.message != WM_LBUTTONUP)	// ��һҳ
			{
				pageDown(w->table);
			}
			else if (state(msg, w->viewStudents_back))	// ����
			{
				// ��ʾ������
				showMainWindow(w);
			}
			else if (state(msg, w->viewStudents_sort) && msg.message != WM_LBUTTONUP)	// ����
			{
				if (w->viewStudents_sort->text == L"���ܷ�����")
				{
					int l = sizeofList(w->manager.students);
					sortList(&((w->manager).students), compareByGPA, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"��ѧ������";
					state(msg, w->viewStudents_sort);
				}
				else
				{
					int l = sizeofList(w->manager.students);
					sortList(&(w->manager).students, compareByStudentID, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"���ܷ�����";
					state(msg, w->viewStudents_sort);
				}
			}
			else
			{
				continue;
			}
		}
		else if (w->state == WindowState::viewAdmins)	// �鿴ѧ��������ʾ
		{
			if (state(msg, w->viewStudents_pageUp) && msg.message != WM_LBUTTONUP)			// ��һҳ
			{
				pageUp(w->table);
			}
			else if (state(msg, w->viewStudents_pageDown) && msg.message != WM_LBUTTONUP)	// ��һҳ
			{
				pageDown(w->table);
			}
			else if (state(msg, w->viewStudents_back))	// ����
			{
				// ��ʾ������
				showMainWindow(w);
			}
			else if (state(msg, w->viewStudents_sort) && msg.message != WM_LBUTTONUP)	// ����
			{
				if (w->viewStudents_sort->text == L"���ܷ�����")
				{
					int l = sizeofList(w->manager.students);
					sortList(&((w->manager).students), compareByGPA, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"��ѧ������";
					state(msg, w->viewStudents_sort);
				}
				else
				{
					int l = sizeofList(w->manager.students);
					sortList(&(w->manager).students, compareByStudentID, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"���ܷ�����";
					state(msg, w->viewStudents_sort);
				}
			}
			else
			{
				continue;
			}
		}
		else if(w->state == WindowState::editAdmins)	// �༭ѧ��������ʾ
		{
		if (state(msg, w->editStudents_back))	// ����
		{
			// ��ʾ������
			showMainWindow(w);
		}
		else if (state(msg, w->editStudents_search) && msg.message != WM_LBUTTONUP)	// ����ѧ��
		{
			wchar_t ReceAcctID[20]{ L"StudentID" }; //��¼������û����ַ���
			TCHAR InputAcct[] = _T("������Ҫ���ҵ�ѧ��");
			InputBox(ReceAcctID, 20, InputAcct);
			int wideStrLen_3 = wcslen(ReceAcctID);
			//char* studentID = new char[wideStrLen_3 * 4];
			char* studentID = (char*)malloc(4 * sizeof(wideStrLen_3));
			// �����ַ���ת��Ϊ���ֽ��ַ���
			WideCharToMultiByte(CP_ACP, 0, ReceAcctID, -1, studentID, wideStrLen_3 * 4, NULL, NULL);
			StudentInfo* index = findStudentByID_ui(studentID, w->manager.students);
			if (index != NULL)
			{
				showTable(*w->table, index);
			}
			else
			{
				MessageBox(GetHWnd(), L"δ�ҵ�ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			}
		
		}
		else if (state(msg, w->editStudents_add) && msg.message != WM_LBUTTONUP)		// ���ѧ��
		{
			addAdminAccount();//��Ҫǰ�˻��޸�
			//������õ��ڲ�������Ҫ�õ�w->manager.students��Ϊ������Ӧ�����ʵ
			w->isEdit = true;

		}
		else if (state(msg, w->editStudents_delete) && msg.message != WM_LBUTTONUP)	// ɾ��ѧ��
		{
			modifyScoreMenu_ui(w->manager.students);//������Ҫ�޸�
			//��Ҫǰ�˻��޸�
		}
		else
		{
			continue;
		}
		}

		else if (w->state == WindowState::editStudents)	// �༭ѧ��������ʾ
		{
			if (state(msg, w->editStudents_back))	// ����
			{
				// ��ʾ������
				showMainWindow(w);
			}
			else if (state(msg, w->editStudents_search) && msg.message != WM_LBUTTONUP)	// ����ѧ��
			{
				wchar_t ReceAcctID[20]{ L"StudentID" }; //��¼������û����ַ���
				TCHAR InputAcct[] = _T("������Ҫ���ҵ�ѧ��");
				InputBox(ReceAcctID, 20, InputAcct);
				int wideStrLen_3 = wcslen(ReceAcctID);
				//char* studentID = new char[wideStrLen_3 * 4];
				char* studentID = (char*)malloc(4 * sizeof(wideStrLen_3));
				// �����ַ���ת��Ϊ���ֽ��ַ���
				WideCharToMultiByte(CP_ACP, 0, ReceAcctID, -1, studentID, wideStrLen_3 * 4, NULL, NULL);
				StudentInfo* index = findStudentByID_ui(studentID, w->manager.students);
				if (index != NULL)
				{
					showTable(*w->table, index);
				}
				else
				{
					MessageBox(GetHWnd(), L"δ�ҵ�ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
			}
			else if (state(msg, w->editStudents_add) && msg.message != WM_LBUTTONUP)		// ���ѧ��
			{
				addStudentAccount();//��Ҫǰ�˻��޸�
				w->isEdit = true;

			}
			else if (state(msg, w->editStudents_delete) && msg.message != WM_LBUTTONUP)	// ɾ��ѧ��
			{
				modifyScoreMenu();//������Ҫ�޸�
				//��Ҫǰ�˻��޸�
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
		
	}
}

bool close(Window* w)
{
	if (w->isEdit)
	{
		// ���б���
		int id = MessageBox(GetHWnd(), L"�Ƿ񱣴����еĲ�����", L"�˳�����", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
		{
			// д��ѧ������
			int l = sizeofList(w->manager.students);
			sortList(&((w->manager).students), compareByStudentID, l);
			saveToFile_ui((w->manager).students);
			closegraph();
			return true;
		}
		else if (id == IDNO)
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	return false;
}

void showMainWindow(Window* w)
{
	w->state = WindowState::mainWindow;
	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ������ʾ����
	RECT rect = { 0, 0, w->wid.width, 200 };
	settextstyle(50, 0, L"΢���ź�");
	drawtext(L"ѧ���ɼ�����ϵͳ", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	// ��ʾ��ť
	ButtonShow(w->mainWindow_view);
	ButtonShow(w->mainWindow_view_admin);
	ButtonShow(w->mainWindow_edit);
	ButtonShow(w->mainWindow_edit_admin);
	ButtonShow(w->mainWindow_exit);
	ButtonShow(w->mainWindow_clear);
	ButtonShow(w->mainWindow_cmd);
}

void showViewStudents(Window* w)
{
	w->state = WindowState::viewStudents;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
	tableShow_stu(*w->table);
	ButtonShow(w->viewStudents_pageUp);
	ButtonShow(w->viewStudents_pageDown);
	ButtonShow(w->viewStudents_back);
	ButtonShow(w->viewStudents_sort);
}
void showViewAdmins(Window* w)
{
	w->state = WindowState::viewAdmins;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
	tableShow_admin(*w->table);
	ButtonShow(w->viewStudents_pageUp);
	ButtonShow(w->viewStudents_pageDown);
	ButtonShow(w->viewStudents_back);
	ButtonShow(w->viewStudents_sort);
}

void showEditStudents(Window* w)
{
	w->state = WindowState::editStudents;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
	ButtonShow(w->editStudents_search);
	ButtonShow(w->editStudents_add);
	ButtonShow(w->editStudents_delete);
	ButtonShow(w->editStudents_back);
}

void showEditAdmins(Window* w)
{
	w->state = WindowState::editAdmins;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
	ButtonShow(w->editStudents_search);
	ButtonShow(w->editStudents_add);
	ButtonShow(w->editStudents_delete);
	ButtonShow(w->editStudents_back);
}

bool isNumber(Window* w, const std::wstring& string)
{
	if (_wtoi(string.c_str()) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


AdminInfo AdminUser;
StudentInfo StuArry[n];
int NowStudentNums = 0;
// ���ҹ���Ա
AdminInfo* findAdminByUsername_ui(const char* username, AdminInfo* adminsList) {
	// �Ƚϸ������û����͹���Ա���û���
	AdminInfo* currentAdmin = adminsList;
	while (currentAdmin != NULL) {
		// �Ƚϵ�ǰѧ����ѧ���������ѧ��
		if (strcmp(currentAdmin->username, username) == 0) {
			// ����ҵ�ƥ���ѧ�ţ����ص�ǰѧ������Ϣ
			return currentAdmin;
		}
		// �ƶ����������һ���ڵ�
		currentAdmin = currentAdmin->next;
	}
	// ��������������б�û���ҵ�ƥ���ѧ�ţ�����NULL
	return NULL;
}
//����Ա��¼
//����ȫ�ֱ��������ں�����������
Window* window = (Window*)malloc(sizeof(Window));
void AdminSignIn() {
	AdminInfo* tmp = window->manager.admins;
	AdminInfo* tmp1 = window->manager.admins;
	//�ж�ѧ���Ƿ����



	wchar_t ReceAcctNumber[20]{ L"admin" }; //��¼������û����ַ���
	TCHAR InputAcct[] = _T("�������û���");
	InputBox(ReceAcctNumber, 20, InputAcct);

	int wideStrLen_3 = wcslen(ReceAcctNumber);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
	tmp1 = findAdminByUsername_ui(ReceAcctNumber_s, tmp);
	while (tmp1 == NULL)
	{
		handleInputError("�˺Ų�����\n");
		wchar_t ReceAcctNumber[20]{ L"admin" }; //��¼������û����ַ���
		TCHAR InputAcct[] = _T("�������û���");
		InputBox(ReceAcctNumber, 20, InputAcct);
		int wideStrLen_3 = wcslen(ReceAcctNumber);
		// Ϊchar���͵��ַ��������㹻�Ŀռ�
		char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
		// �����ַ���ת��Ϊ���ֽ��ַ���
		WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
		tmp1 = findAdminByUsername_ui(ReceAcctNumber_s, tmp);
	}






	wchar_t ReceAcctpassword[30]{ L"admin" }; //��¼����������ַ���
	TCHAR InputPass[] = _T("����������");
	InputBox(ReceAcctpassword, 30, InputPass);

	int wideStrLen_4 = wcslen(ReceAcctpassword);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);

	while (!isPasswordValid(ReceAcctpassword_s)) {
		//��Ϊ��������
		handleInputError("����ӦΪ1-15λ���ֻ���ĸ�����������롣\n");

		wchar_t ReceAcctpassword[30]{ L"admin" }; //��¼����������ַ���
		TCHAR InputPass[] = _T("����������");
		InputBox(ReceAcctpassword, 20, InputPass);
		int wideStrLen_4 = wcslen(ReceAcctpassword);
		// Ϊchar���͵��ַ��������㹻�Ŀռ�
		char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
		// �����ַ���ת��Ϊ���ֽ��ַ���
		WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);
	}


	//����û��������붼��ȷ�Ž��ȵ�����Ա���棬���򵯴���ʾ����
	if (strcmp(tmp1->username, ReceAcctNumber_s) == 0 && strcmp(tmp1->password, ReceAcctpassword_s) == 0) {
		cleardevice();
		//window = new Window;
		windowInit(window, 1024, 640);
		windowShow(window);
		messageLoop(window);
		windowDelete(window);
		delete window;
	}
	//����������ʾ����Ҫ��ʵ����SignError����
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"�û������������!", L"��ʾ", MB_OK);
	}
	exit(0);
}

//ѧ����¼
void StuSignIn() {
	StudentInfo* tmp = window->manager.students;
	StudentInfo* tmp1 = window->manager.students;
	//�ж�ѧ���Ƿ����



	wchar_t ReceAcctNumber[20]{ L"admin" }; //��¼������û����ַ���
	TCHAR InputAcct[] = _T("�������û���");
	InputBox(ReceAcctNumber, 20, InputAcct);

	int wideStrLen_3 = wcslen(ReceAcctNumber);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
	tmp1 = findStudentByID_ui(ReceAcctNumber_s, tmp);
	while (tmp1 == NULL)
	{
		handleInputError("�˺Ų�����\n");
		wchar_t ReceAcctNumber[20]{ L"admin" }; //��¼������û����ַ���
		TCHAR InputAcct[] = _T("�������û���");
		InputBox(ReceAcctNumber, 20, InputAcct);
		int wideStrLen_3 = wcslen(ReceAcctNumber);
		// Ϊchar���͵��ַ��������㹻�Ŀռ�
		char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
		// �����ַ���ת��Ϊ���ֽ��ַ���
		WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
		tmp1 = findStudentByID_ui(ReceAcctNumber_s, tmp);
	}






	wchar_t ReceAcctpassword[30]{ L"admin" }; //��¼����������ַ���
	TCHAR InputPass[] = _T("����������");
	InputBox(ReceAcctpassword, 30, InputPass);

	int wideStrLen_4 = wcslen(ReceAcctpassword);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);

	while (!isPasswordValid(ReceAcctpassword_s)) {
		//��Ϊ��������
		handleInputError("����ӦΪ1-15λ���ֻ���ĸ�����������롣\n");

		wchar_t ReceAcctpassword[30]{ L"admin" }; //��¼����������ַ���
		TCHAR InputPass[] = _T("����������");
		InputBox(ReceAcctpassword, 20, InputPass);
		int wideStrLen_3 = wcslen(ReceAcctpassword);
		// Ϊchar���͵��ַ��������㹻�Ŀռ�
		char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
		// �����ַ���ת��Ϊ���ֽ��ַ���
		WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);
	}


	//����û��������붼��ȷ�Ž��ȵ�����Ա���棬���򵯴���ʾ����
	if (strcmp(tmp1->studentID, ReceAcctNumber_s) == 0 && strcmp(tmp1->password, ReceAcctpassword_s) == 0) {
		cleardevice();
		windowInit(window, 1024, 640);
		windowShow(window);
		messageLoop(window);
		windowDelete(window);
		free(window);
	}
	//����������ʾ����Ҫ��ʵ����SignError����
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"�û������������!", L"��ʾ", MB_OK);
	}
	exit(0);
}
//��ҳ
void FirstPage() {
	StudentInfo* news = (StudentInfo*)malloc(sizeof(StudentInfo));
	AdminInfo* newa = (AdminInfo*)malloc(sizeof(AdminInfo));
	(window->manager).students = NULL;
	(window->manager).admins = NULL;
	loadFromFile_all(&(window->manager));
	loadFromFile();//���ļ�����
	initgraph(1024, 640);//���ڴ�С
	MOUSEMSG m1;//������1
	cleardevice();
	IMAGE picture1;
	loadimage(&picture1, BACKGROUND_IMAGE, 1024, 640);
	putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	setfillcolor(GREEN);

	//�����
	settextstyle(60, 0,L"����");
	outtextxy(150, 100, L"ѧ���ɼ�����ϵͳ");

	//����ѡ��ı���
	fillrectangle(0, 445, 300, 490);
	fillrectangle(0, 505, 300, 550);
	fillrectangle(0, 565, 300, 610);

	setbkmode(TRANSPARENT);

	//����ѡ�������
	LOGFONT f;//������ʽָ��
	gettextstyle(&f);					//��ȡ������ʽ
	_tcscpy_s(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    //�������Ч��Ϊ����ݣ�������ôģ��
	f.lfHeight = 35;					//���������С
	settextstyle(&f);                     // ����������ʽ

	RECT R[3] = { {0, 445, 300, 490},{0, 505, 300, 550},{0, 565, 300, 610} };
	//��drawtext������outtextxy������ʵ�����ֵľ���
	drawtext(L"����Ա��������", &R[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"ѧ����������", &R[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"�˳�����", &R[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//����������ѡ���������
	while (1) {
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 0 && m1.x <= 300 && m1.y >= 445 && m1.y <= 490)//����Ա����
		{
			setlinecolor(RED);
			rectangle(0, 445, 300, 490);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //������������ʱ�����¼�
				AdminSignIn(); //����Ա��¼���棬ֻ���˺�������ȷ��ִ��AdminPage����
				break;
			}
		}
		else if (m1.x >= 0 && m1.x <= 300 && m1.y >= 505 && m1.y <= 550)//ѧ���û�����
		{
			setlinecolor(RED);
			rectangle(0, 505, 300, 550);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //������������ʱ�����¼�
				StuSignIn();
				break;
			}
		}
		else if (m1.x >= 0 && m1.x <= 300 && m1.y >= 565 && m1.y <= 610)//�˳�
		{
			setlinecolor(RED);
			rectangle(0, 565, 300, 610);
			if (m1.uMsg == WM_LBUTTONDOWN) {
				exit(0);
			}
		}
		//��겻��������ͣ
		else {
			setlinecolor(WHITE);
			rectangle(0, 445, 300, 490);
			rectangle(0, 505, 300, 550);
			rectangle(0, 565, 300, 610);
		}
	}

}

void showCmd()
{
	loadFromFile();//���ļ�����

	if (adminsList == NULL) {
		AdminInfo* admin = (AdminInfo*)malloc(sizeof(AdminInfo));
		if (admin == NULL) {
			// ����ڴ����ʧ�ܣ���ӡ������Ϣ���˳�����
			fprintf(stderr, "�ڴ����ʧ��\n");
			exit(EXIT_FAILURE);
		}
		strcpy(admin->username, "admin");
		strcpy(admin->password, "admin");
		admin->next = NULL;
		adminsList = admin;
	}
	// ��ʼ������Ա��Ϣ,�û����������Ϊadmin

	loginSystem();// ����ϵͳ

	if (!isSaved)saveToFile();//���浽�ļ�

	freeMemory(&studentsList);//�ͷ��ڴ�
	freeAdminMemory(&adminsList);//�ͷ��ڴ�
	return;
}