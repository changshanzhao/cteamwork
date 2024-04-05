#include "Manager.h"

bool read(const std::string& fileName, Manager M)
{
    // �Զ����ƶ�ȡģʽ���ļ�
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file)
    {
        return false;
    }

    // ��ȡ����
    Student data = {};
    while (file.read((char*)&data, sizeof(Student)))
    {
        M.students.push_back(data);
    }

    file.close();
    return true;
}

void write(const std::string& fileName, Manager M)
{
    // �Զ�����д��ģʽ���ļ�
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    // д������
    for (int i = 0; i < M.students.size(); i++)
    {
        file.write((const char*)& M.students[i], sizeof(Student));
    }

    file.close();
}

void addStudent(const Student& student, Manager M)
{
    M.students.push_back(student);
}

void sortById(Manager M)
{
    std::sort(M.students.begin(), M.students.end());
}

void sortByScore(Manager M)
{
    std::sort(M.students.begin(), M.students.end(), std::greater<Student>());
}

const Student& getStudent(int index, Manager M)
{
    return M.students[index];
}

void setStudent(int index, const Student& student, Manager M)
{
    M.students[index] = student;
}

void deleteStudent(int index, Manager M)
{
    M.students.erase(M.students.begin() + index);
}

int size(Manager M)
{
    // TODO: �ڴ˴����� return ���
    return (int)M.students.size();
}

int searchName(const wchar_t* searchTerms, Manager M)
{
    // TODO: �ڴ˴����� return ���
    std::vector<Student>::const_iterator iter;
    iter = std::find(M.students.begin(), M.students.end(), searchTerms);
    if (iter != M.students.end())
    {
        // �����ɹ�����������
        return (int)(iter - M.students.begin());
    }
    else
    {
        // ����ʧ�ܣ����� -1 ��ʾ����
        return -1;
    }
}

int searchId(int id, Manager M)
{
    std::vector<Student>::const_iterator iter;
    iter = std::find(M.students.begin(), M.students.end(), id);
    if (iter != M.students.end())
    {
        // �����ɹ�����������
        return (int)(iter - M.students.begin());
    }
    else
    {
        // ����ʧ�ܣ����� -1 ��ʾ����
        return -1;
    }
}

void clear(Manager* M)
{
    M->students.clear();
}
