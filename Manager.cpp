#include "Manager.h"

bool read(const std::string& fileName, Manager M)
{
    // 以二进制读取模式打开文件
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file)
    {
        return false;
    }

    // 读取数据
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
    // 以二进制写入模式打开文件
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    // 写入数据
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
    // TODO: 在此处插入 return 语句
    return (int)M.students.size();
}

int searchName(const wchar_t* searchTerms, Manager M)
{
    // TODO: 在此处插入 return 语句
    std::vector<Student>::const_iterator iter;
    iter = std::find(M.students.begin(), M.students.end(), searchTerms);
    if (iter != M.students.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - M.students.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

int searchId(int id, Manager M)
{
    std::vector<Student>::const_iterator iter;
    iter = std::find(M.students.begin(), M.students.end(), id);
    if (iter != M.students.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - M.students.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

void clear(Manager* M)
{
    M->students.clear();
}
