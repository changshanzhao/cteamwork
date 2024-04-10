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
	SetWindowText(w->hWnd, L"学生成绩管理系统");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(w->hWnd, SW_HIDE);

	// 设置绘图样式
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	// 创建按钮
	

	w->mainWindow_view	 = new Button();
	buttonInit(w->mainWindow_view, (1024 - 200) / 2, 150, 170, 30, L"查看学生");
	w->mainWindow_view_admin = new Button();
	buttonInit(w->mainWindow_view_admin, (1024 - 200) / 2, 200, 170, 30, L"查看管理员");
	w->mainWindow_edit = new Button();
	buttonInit(w->mainWindow_edit, (1024 - 200) / 2, 250, 170, 30, L"编辑学生");
	w->mainWindow_edit_admin = new Button();
	buttonInit(w->mainWindow_edit_admin, (1024 - 200) / 2, 300, 170, 30, L"编辑管理员");
	w->mainWindow_clear = new Button();
	buttonInit(w->mainWindow_clear, (1024 - 200) / 2, 350, 170, 30, L"清空数据");
	w->mainWindow_exit = new Button();
	buttonInit(w->mainWindow_exit, (1024 - 200) / 2, 400, 170, 30, L"退出程序");
	w->mainWindow_cmd = new Button();
	buttonInit(w->mainWindow_cmd, (1024 - 200) / 2, 450, 170, 30, L"显示终端程序");
	w->viewStudents_pageUp = new Button();
	buttonInit(w->viewStudents_pageUp, 10, 380, 80, 30, L"上一页");
	w->viewStudents_pageDown = new Button();
	buttonInit(w->viewStudents_pageDown, 210, 380, 80, 30, L"下一页");
	w->viewStudents_back = new Button();
	buttonInit(w->viewStudents_back, 412, 380, 80, 30, L"返回");
	w->viewStudents_sort = new Button();
	buttonInit(w->viewStudents_sort, 300, 380, 102, 30, L"按总分排序");
	w->editStudents_search = new Button();
	buttonInit(w->editStudents_search, 10, 380, 100, 30, L"搜索学生");
	w->editStudents_add = new Button();
	buttonInit(w->editStudents_add, 137, 380, 100, 30, L"添加学生");
	w->editStudents_delete = new Button();
	buttonInit(w->editStudents_delete, 264, 380, 100, 30, L"删除学生");
	w->editStudents_back = new Button();
	buttonInit(w->editStudents_back, 392, 380, 100, 30, L"返回");

	showMainWindow(w);	// 显示主界面

	// 创建表格
	w->table = new Table();

	tableInit(w->table, w->manager, 10, 10, 502 - 20, 420 - 60);
}

void windowDelete(Window* w)
{
	// 销毁
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
// 按学号查找学生
StudentInfo* findStudentByID_ui(const char* studentID, StudentInfo* studentsList);
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
// 编辑学生成绩或删除学生
void modifyScoreMenu_ui(StudentInfo* studentList) {
	char studentID[8];
	printf("请输入学生学号: ");
	scanf("%s", studentID);
	StudentInfo* student = findStudentByID_ui(studentID, studentList);
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
// 创建新学生
StudentInfo* createStudent_ui(StudentInfo* student) {
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
	newStudent->innovationProjects = NULL; // 初始化大学生创新创业计划项目链表
	newStudent->academicPapers = NULL; // 初始化学术论文链表
	newStudent->competitions = NULL; // 初始化计算机类学科竞赛链表
	newStudent->gpa = 0.00f; // 初始化GPA
	newStudent->totalCredit = 0; // 初始化总学分
	newStudent->qualityGpa = 0.00f; // 初始化素质加分GPA
	newStudent->averageScore = 0.00f; // 初始化加权平均分
	strcpy(newStudent->name, "New Student");
	strcpy(newStudent->studentID, "00000000");
	newStudent->classNumber = 1; // 假设学生班级为1
	newStudent->grade = 1; // 缺省值学生年级为1
	strcpy(newStudent->password, "123456"); // 默认密码为123456
	// 输入学生信息
	printf("请输入学生信息：\n");
	printf("学号: ");
	scanf("%s", newStudent->studentID);
	// 判断学号是否是8位数字
	while (!isStudentIDValid(newStudent->studentID)) {
		handleInputError("学号应为8位数字，请重新输入。\n");
		scanf("%s", newStudent->studentID);
	}
	// 检查学号是否已存在
	if (findStudentByID_ui(newStudent->studentID, student) != NULL) {
		// 如果学号已存在，打印错误信息、释放内存并返回上一级菜单
		handleInputError("学号已存在，请重新输入。");
		free(newStudent);
		return NULL;
	}
	printf("姓名: ");
	scanf("%s", newStudent->name);
	printf("班级: ");
	scanf("%d", &(newStudent->classNumber));
	//判断班级是否合法
	while (!isClassValid(newStudent->classNumber)) {
		handleInputError("班级应为大于0的数，请重新输入。\n");
		scanf("%d", &newStudent->classNumber);
	}

	printf("年级: ");
	scanf("%d", &newStudent->grade);
	//判断年级是否合法
	while (!isGradeValid(newStudent->grade)) {
		handleInputError("年级应为1-4之间的数(1.大一 2.大二 3.大三 4.大四)，请重新输入。\n");
		scanf("%d", &newStudent->grade);
	}

	//录入学业成绩
	int choice1;
	printf("是否现在录入课程记录？(1. 是 2. 否): ");
	scanf("%d", &choice1);
	//判断选择是否合法
	while (choice1 != 1 && choice1 != 2) {
		handleInputError("选项应为1或2，请重新输入。\n");
		scanf("%d", &choice1);
	}
	if (choice1 == 1) {
		int numCourses;
		printf("请输入要输入的课程数量：");
		scanf("%d", &numCourses);
		for (int i = 0; i < numCourses; i++) {
			printf("请输入第%d门课程信息：\n", i + 1);
			addCourse(newStudent);
		}
		calculateAcademics(newStudent);
	}

	int choice2;
	printf("是否现在录入素质加分项目记录？(1. 是 2. 否): ");
	scanf("%d", &choice2);
	//判断选择是否合法
	while (choice2 != 1 && choice2 != 2) {
		handleInputError("选项应为1或2，请重新输入。\n");
		scanf("%d", &choice2);
	}
	if (choice2 == 1) {
		//录入素质加分项目
		addQualityProject(newStudent);
		calculateQualityGPA(newStudent);
		calculateAcademics(newStudent);
	}
	// 返回新创建的StudentInfo指针
	return newStudent;
}
// 添加学生账号
char* addStudentAccount_ui(StudentInfo* studentList) {
	StudentInfo* newStudent = createStudent_ui(studentList);
	// 计算GPA
	calculateGPA(newStudent);
	// 插入学生列表
	insertStudent(&studentList, newStudent);
	printf("学生账号创建成功。\n");
	return newStudent->name;
}
//以下函数均需要修改成前端格式

void saveToFile_ui(StudentInfo* studensList) {
	FILE* file = fopen("student.txt", "w");
	if (file == NULL) {
		handleInputError("打开文件失败");
		return;
	}

	StudentInfo* currentStudent = studentsList;
	while (currentStudent != NULL) {
		// 学生记录开始
		fprintf(file, "%s\n", STUDENT_START);

		//        char studentID[8];// 学号
		//        char name[15];// 姓名
		//        char password[15];// 密码
		//        int classNumber;// 班级
		//        float gpa;  // 学业GPA
		//        float totalCredit;// 总学分
		//        float qualityGpa;// 素质加分GPA
		//        float averageScore;// 加权平均分
		//        float totalGPA;// 总绩点

				// 写入学生个人信息
		fprintf(file, "StudentID: %s\n", currentStudent->studentID);// 学号
		fprintf(file, "Name: %s\n", currentStudent->name);// 姓名
		fprintf(file, "Password: %s\n", currentStudent->password);// 密码
		fprintf(file, "Grade: %d\n", currentStudent->grade);// 年级
		fprintf(file, "ClassNumber: %d\n", currentStudent->classNumber);// 班级
		fprintf(file, "GPA: %f\n", currentStudent->gpa);// 学业GPA
		fprintf(file, "TotalCredit: %.2f\n", currentStudent->totalCredit);// 总学分
		fprintf(file, "QualityGPA: %.2f\n", currentStudent->qualityGpa);// 素质加分GPA
		fprintf(file, "AverageScore: %f\n", currentStudent->averageScore);// 加权平均分
		fprintf(file, "TotalGPA: %f\n", currentStudent->totalGPA);// 总绩点

//        char courseName[MAX_NAME_LENGTH];
//        float score;    // 分数
//        float credit; // 学分
//        float gpa; // 单门课程绩点
		// 学业成绩链表
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

		//        char projectName[MAX_NAME_LENGTH]; // 项目名称
		//        float gpa; // 加分值
		//        int isLeaderOrSecondLeader;// 是否为项目负责人,是否为第二负责人，国家级优秀结题项目负责人加0.1 GPA，第二名加0.05 GPA
		//        char projectLevel[10];// 项目级别，国家级，省级，校级
		//        int isFinished;    // 是否结题
				// 大学生创新创业计划项目链表
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

		//        char title[MAX_NAME_LENGTH]; // 论文标题
		//        char journalName[MAX_NAME_LENGTH]; // 期刊名称
		//        int isFirstAuthor; // 是否为第一作者
		//
		//        //期刊级别，顶级加0.4，一级期刊加0.2 GPA，二级期刊加0.1 GPA，三级期刊加0.05 GPA，四级期刊加0.02 GPA，五级期刊加0.01 GPA
		//        int journalLevel;
		//
		//        float gpa; // 加分值
				// 学术论文链表
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

		//        char competitionName[MAX_NAME_LENGTH]; // 竞赛名称
		//        int teamSize;   //参赛队伍人数
		//        char competitionLevel[10]; // 竞赛级别,国家级，省级，校级
		//        int rank;   // 获奖等级，1表示一等奖，2表示二等奖，3表示三等奖
		//        char competitionType;   //竞赛类别，A类，B类，C类
		//        float gpa; // 加分值
				// 计算机类学科竞赛链表
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

		// 学生记录结束
		fprintf(file, "%s\n", STUDENT_END);

		currentStudent = currentStudent->next;
	}
	fclose(file);//关闭文件

	// 保存管理员信息
	FILE* adminFile = fopen("admin.txt", "w");
	if (adminFile == NULL) {
		handleInputError("打开文件失败");
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
	fclose(adminFile);//关闭文件

	printf("保存成功。\n");
}


void messageLoop(Window* w)
{
	// 开启消息循环
	ExMessage msg;
	while (true)
	{
		// 获取并判断消息
		msg = getmessage();

		// 判断显示界面
		if (w->state == WindowState::mainWindow)		// 主窗口显示
		{
			if (state(msg, w->mainWindow_view))		// 查看学生
			{
				showViewStudents(w);
			}
			else if (state(msg, w->mainWindow_edit_admin))	// 编辑学生
			{
				showEditAdmins(w);
			}
			else if (state(msg, w->mainWindow_view_admin))	// 编辑学生
			{
				showViewAdmins(w);
			}
			else if (state(msg, w->mainWindow_edit))	// 编辑学生
			{
				showEditStudents(w);
			}
			else if (state(msg, w->mainWindow_clear))	// 清空数据
			{
				if (MessageBox(GetHWnd(), L"确定要清空所有学生数据？", L"清空数据", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					// 确定清空
					FILE* file = fopen("student.txt", "w");
					freeMemory(&(w->manager.students));
				}
			}
			else if (state(msg, w->mainWindow_exit))	// 退出程序
			{
				if (MessageBox(GetHWnd(), L"确定退出程序吗", L"退出程序", MB_YESNO | MB_ICONQUESTION) == IDYES)
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
		else if (w->state == WindowState::viewStudents)	// 查看学生窗口显示
		{
			if (state(msg, w->viewStudents_pageUp) && msg.message != WM_LBUTTONUP)			// 上一页
			{
				pageUp(w->table);
			}
			else if (state(msg, w->viewStudents_pageDown) && msg.message != WM_LBUTTONUP)	// 下一页
			{
				pageDown(w->table);
			}
			else if (state(msg, w->viewStudents_back))	// 返回
			{
				// 显示主窗口
				showMainWindow(w);
			}
			else if (state(msg, w->viewStudents_sort) && msg.message != WM_LBUTTONUP)	// 排序
			{
				if (w->viewStudents_sort->text == L"按总分排序")
				{
					int l = sizeofList(w->manager.students);
					sortList(&((w->manager).students), compareByGPA, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"按学号排序";
					state(msg, w->viewStudents_sort);
				}
				else
				{
					int l = sizeofList(w->manager.students);
					sortList(&(w->manager).students, compareByStudentID, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"按总分排序";
					state(msg, w->viewStudents_sort);
				}
			}
			else
			{
				continue;
			}
		}
		else if (w->state == WindowState::viewAdmins)	// 查看学生窗口显示
		{
			if (state(msg, w->viewStudents_pageUp) && msg.message != WM_LBUTTONUP)			// 上一页
			{
				pageUp(w->table);
			}
			else if (state(msg, w->viewStudents_pageDown) && msg.message != WM_LBUTTONUP)	// 下一页
			{
				pageDown(w->table);
			}
			else if (state(msg, w->viewStudents_back))	// 返回
			{
				// 显示主窗口
				showMainWindow(w);
			}
			else if (state(msg, w->viewStudents_sort) && msg.message != WM_LBUTTONUP)	// 排序
			{
				if (w->viewStudents_sort->text == L"按总分排序")
				{
					int l = sizeofList(w->manager.students);
					sortList(&((w->manager).students), compareByGPA, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"按学号排序";
					state(msg, w->viewStudents_sort);
				}
				else
				{
					int l = sizeofList(w->manager.students);
					sortList(&(w->manager).students, compareByStudentID, l);
					tableShow_stu(*w->table);
					w->viewStudents_sort->text = L"按总分排序";
					state(msg, w->viewStudents_sort);
				}
			}
			else
			{
				continue;
			}
		}
		else if(w->state == WindowState::editAdmins)	// 编辑学生窗口显示
		{
		if (state(msg, w->editStudents_back))	// 返回
		{
			// 显示主窗口
			showMainWindow(w);
		}
		else if (state(msg, w->editStudents_search) && msg.message != WM_LBUTTONUP)	// 搜索学生
		{
			wchar_t ReceAcctID[20]{ L"StudentID" }; //记录输入的用户名字符串
			TCHAR InputAcct[] = _T("请输入要查找的学号");
			InputBox(ReceAcctID, 20, InputAcct);
			int wideStrLen_3 = wcslen(ReceAcctID);
			//char* studentID = new char[wideStrLen_3 * 4];
			char* studentID = (char*)malloc(4 * sizeof(wideStrLen_3));
			// 将宽字符串转换为多字节字符串
			WideCharToMultiByte(CP_ACP, 0, ReceAcctID, -1, studentID, wideStrLen_3 * 4, NULL, NULL);
			StudentInfo* index = findStudentByID_ui(studentID, w->manager.students);
			if (index != NULL)
			{
				showTable(*w->table, index);
			}
			else
			{
				MessageBox(GetHWnd(), L"未找到学生！", L"提示", MB_OK | MB_ICONINFORMATION);
			}
		
		}
		else if (state(msg, w->editStudents_add) && msg.message != WM_LBUTTONUP)		// 添加学生
		{
			addAdminAccount();//需要前端化修改
			//这里调用的内部函数需要用的w->manager.students作为参数，应该如何实
			w->isEdit = true;

		}
		else if (state(msg, w->editStudents_delete) && msg.message != WM_LBUTTONUP)	// 删除学生
		{
			modifyScoreMenu_ui(w->manager.students);//函数需要修改
			//需要前端化修改
		}
		else
		{
			continue;
		}
		}

		else if (w->state == WindowState::editStudents)	// 编辑学生窗口显示
		{
			if (state(msg, w->editStudents_back))	// 返回
			{
				// 显示主窗口
				showMainWindow(w);
			}
			else if (state(msg, w->editStudents_search) && msg.message != WM_LBUTTONUP)	// 搜索学生
			{
				wchar_t ReceAcctID[20]{ L"StudentID" }; //记录输入的用户名字符串
				TCHAR InputAcct[] = _T("请输入要查找的学号");
				InputBox(ReceAcctID, 20, InputAcct);
				int wideStrLen_3 = wcslen(ReceAcctID);
				//char* studentID = new char[wideStrLen_3 * 4];
				char* studentID = (char*)malloc(4 * sizeof(wideStrLen_3));
				// 将宽字符串转换为多字节字符串
				WideCharToMultiByte(CP_ACP, 0, ReceAcctID, -1, studentID, wideStrLen_3 * 4, NULL, NULL);
				StudentInfo* index = findStudentByID_ui(studentID, w->manager.students);
				if (index != NULL)
				{
					showTable(*w->table, index);
				}
				else
				{
					MessageBox(GetHWnd(), L"未找到学生！", L"提示", MB_OK | MB_ICONINFORMATION);
				}
			}
			else if (state(msg, w->editStudents_add) && msg.message != WM_LBUTTONUP)		// 添加学生
			{
				addStudentAccount();//需要前端化修改
				w->isEdit = true;

			}
			else if (state(msg, w->editStudents_delete) && msg.message != WM_LBUTTONUP)	// 删除学生
			{
				modifyScoreMenu();//函数需要修改
				//需要前端化修改
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
		// 进行保存
		int id = MessageBox(GetHWnd(), L"是否保存所有的操作？", L"退出程序", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
		{
			// 写入学生数据
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
	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 绘制提示文字
	RECT rect = { 0, 0, w->wid.width, 200 };
	settextstyle(50, 0, L"微软雅黑");
	drawtext(L"学生成绩管理系统", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	// 显示按钮
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

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
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

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
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

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
	ButtonShow(w->editStudents_search);
	ButtonShow(w->editStudents_add);
	ButtonShow(w->editStudents_delete);
	ButtonShow(w->editStudents_back);
}

void showEditAdmins(Window* w)
{
	w->state = WindowState::editAdmins;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
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
// 查找管理员
AdminInfo* findAdminByUsername_ui(const char* username, AdminInfo* adminsList) {
	// 比较给定的用户名和管理员的用户名
	AdminInfo* currentAdmin = adminsList;
	while (currentAdmin != NULL) {
		// 比较当前学生的学号与给定的学号
		if (strcmp(currentAdmin->username, username) == 0) {
			// 如果找到匹配的学号，返回当前学生的信息
			return currentAdmin;
		}
		// 移动到链表的下一个节点
		currentAdmin = currentAdmin->next;
	}
	// 如果遍历完整个列表都没有找到匹配的学号，返回NULL
	return NULL;
}
//管理员登录
//设置全局变量，便于后续参数调用
Window* window = (Window*)malloc(sizeof(Window));
void AdminSignIn() {
	AdminInfo* tmp = window->manager.admins;
	AdminInfo* tmp1 = window->manager.admins;
	//判断学号是否存在



	wchar_t ReceAcctNumber[20]{ L"admin" }; //记录输入的用户名字符串
	TCHAR InputAcct[] = _T("请输入用户名");
	InputBox(ReceAcctNumber, 20, InputAcct);

	int wideStrLen_3 = wcslen(ReceAcctNumber);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
	tmp1 = findAdminByUsername_ui(ReceAcctNumber_s, tmp);
	while (tmp1 == NULL)
	{
		handleInputError("账号不存在\n");
		wchar_t ReceAcctNumber[20]{ L"admin" }; //记录输入的用户名字符串
		TCHAR InputAcct[] = _T("请输入用户名");
		InputBox(ReceAcctNumber, 20, InputAcct);
		int wideStrLen_3 = wcslen(ReceAcctNumber);
		// 为char类型的字符串分配足够的空间
		char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
		// 将宽字符串转换为多字节字符串
		WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
		tmp1 = findAdminByUsername_ui(ReceAcctNumber_s, tmp);
	}






	wchar_t ReceAcctpassword[30]{ L"admin" }; //记录输入的密码字符串
	TCHAR InputPass[] = _T("请输入密码");
	InputBox(ReceAcctpassword, 30, InputPass);

	int wideStrLen_4 = wcslen(ReceAcctpassword);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);

	while (!isPasswordValid(ReceAcctpassword_s)) {
		//改为弹出弹框
		handleInputError("密码应为1-15位数字或字母，请重新输入。\n");

		wchar_t ReceAcctpassword[30]{ L"admin" }; //记录输入的密码字符串
		TCHAR InputPass[] = _T("请输入密码");
		InputBox(ReceAcctpassword, 20, InputPass);
		int wideStrLen_4 = wcslen(ReceAcctpassword);
		// 为char类型的字符串分配足够的空间
		char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
		// 将宽字符串转换为多字节字符串
		WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);
	}


	//如果用户名和密码都正确才进度到管理员界面，否则弹窗提示错误
	if (strcmp(tmp1->username, ReceAcctNumber_s) == 0 && strcmp(tmp1->password, ReceAcctpassword_s) == 0) {
		cleardevice();
		//window = new Window;
		windowInit(window, 1024, 640);
		windowShow(window);
		messageLoop(window);
		windowDelete(window);
		delete window;
	}
	//弹窗错误提示，需要先实例化SignError对象
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"用户名或密码错误!", L"提示", MB_OK);
	}
	exit(0);
}

//学生登录
void StuSignIn() {
	StudentInfo* tmp = window->manager.students;
	StudentInfo* tmp1 = window->manager.students;
	//判断学号是否存在



	wchar_t ReceAcctNumber[20]{ L"admin" }; //记录输入的用户名字符串
	TCHAR InputAcct[] = _T("请输入用户名");
	InputBox(ReceAcctNumber, 20, InputAcct);

	int wideStrLen_3 = wcslen(ReceAcctNumber);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
	tmp1 = findStudentByID_ui(ReceAcctNumber_s, tmp);
	while (tmp1 == NULL)
	{
		handleInputError("账号不存在\n");
		wchar_t ReceAcctNumber[20]{ L"admin" }; //记录输入的用户名字符串
		TCHAR InputAcct[] = _T("请输入用户名");
		InputBox(ReceAcctNumber, 20, InputAcct);
		int wideStrLen_3 = wcslen(ReceAcctNumber);
		// 为char类型的字符串分配足够的空间
		char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
		// 将宽字符串转换为多字节字符串
		WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
		tmp1 = findStudentByID_ui(ReceAcctNumber_s, tmp);
	}






	wchar_t ReceAcctpassword[30]{ L"admin" }; //记录输入的密码字符串
	TCHAR InputPass[] = _T("请输入密码");
	InputBox(ReceAcctpassword, 30, InputPass);

	int wideStrLen_4 = wcslen(ReceAcctpassword);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);

	while (!isPasswordValid(ReceAcctpassword_s)) {
		//改为弹出弹框
		handleInputError("密码应为1-15位数字或字母，请重新输入。\n");

		wchar_t ReceAcctpassword[30]{ L"admin" }; //记录输入的密码字符串
		TCHAR InputPass[] = _T("请输入密码");
		InputBox(ReceAcctpassword, 20, InputPass);
		int wideStrLen_3 = wcslen(ReceAcctpassword);
		// 为char类型的字符串分配足够的空间
		char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
		// 将宽字符串转换为多字节字符串
		WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);
	}


	//如果用户名和密码都正确才进度到管理员界面，否则弹窗提示错误
	if (strcmp(tmp1->studentID, ReceAcctNumber_s) == 0 && strcmp(tmp1->password, ReceAcctpassword_s) == 0) {
		cleardevice();
		windowInit(window, 1024, 640);
		windowShow(window);
		messageLoop(window);
		windowDelete(window);
		free(window);
	}
	//弹窗错误提示，需要先实例化SignError对象
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"用户名或密码错误!", L"提示", MB_OK);
	}
	exit(0);
}
//首页
void FirstPage() {
	StudentInfo* news = (StudentInfo*)malloc(sizeof(StudentInfo));
	AdminInfo* newa = (AdminInfo*)malloc(sizeof(AdminInfo));
	(window->manager).students = NULL;
	(window->manager).admins = NULL;
	loadFromFile_all(&(window->manager));
	loadFromFile();//从文件加载
	initgraph(1024, 640);//窗口大小
	MOUSEMSG m1;//鼠标操作1
	cleardevice();
	IMAGE picture1;
	loadimage(&picture1, BACKGROUND_IMAGE, 1024, 640);
	putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	setfillcolor(GREEN);

	//大标题
	settextstyle(60, 0,L"宋体");
	outtextxy(150, 100, L"学生成绩管理系统");

	//三个选项的背景
	fillrectangle(0, 445, 300, 490);
	fillrectangle(0, 505, 300, 550);
	fillrectangle(0, 565, 300, 610);

	setbkmode(TRANSPARENT);

	//三个选项的文字
	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	_tcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    //设置输出效果为抗锯齿，不会那么模糊
	f.lfHeight = 35;					//设置字体大小
	settextstyle(&f);                     // 设置字体样式

	RECT R[3] = { {0, 445, 300, 490},{0, 505, 300, 550},{0, 565, 300, 610} };
	//用drawtext而不是outtextxy，可以实现文字的居中
	drawtext(L"管理员操作界面", &R[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"学生操作界面", &R[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"退出程序", &R[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//进入主界面选项操作界面
	while (1) {
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 0 && m1.x <= 300 && m1.y >= 445 && m1.y <= 490)//管理员界面
		{
			setlinecolor(RED);
			rectangle(0, 445, 300, 490);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //当单击鼠标左键时触发事件
				AdminSignIn(); //管理员登录界面，只有账号密码正确才执行AdminPage函数
				break;
			}
		}
		else if (m1.x >= 0 && m1.x <= 300 && m1.y >= 505 && m1.y <= 550)//学生用户界面
		{
			setlinecolor(RED);
			rectangle(0, 505, 300, 550);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //当单击鼠标左键时触发事件
				StuSignIn();
				break;
			}
		}
		else if (m1.x >= 0 && m1.x <= 300 && m1.y >= 565 && m1.y <= 610)//退出
		{
			setlinecolor(RED);
			rectangle(0, 565, 300, 610);
			if (m1.uMsg == WM_LBUTTONDOWN) {
				exit(0);
			}
		}
		//鼠标不在上面悬停
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
	loadFromFile();//从文件加载

	if (adminsList == NULL) {
		AdminInfo* admin = (AdminInfo*)malloc(sizeof(AdminInfo));
		if (admin == NULL) {
			// 如果内存分配失败，打印错误信息并退出程序
			fprintf(stderr, "内存分配失败\n");
			exit(EXIT_FAILURE);
		}
		strcpy(admin->username, "admin");
		strcpy(admin->password, "admin");
		admin->next = NULL;
		adminsList = admin;
	}
	// 初始化管理员信息,用户名和密码均为admin

	loginSystem();// 进入系统

	if (!isSaved)saveToFile();//保存到文件

	freeMemory(&studentsList);//释放内存
	freeAdminMemory(&adminsList);//释放内存
	return;
}