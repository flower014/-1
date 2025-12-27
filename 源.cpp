#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

#define MAX 1000 

// 联系人结构体
struct Person
{
    string m_Name;
    int m_Sex;     // 性别:1男 2女
    int m_Age;
    string m_Phone;
    string m_Email;  // 邮箱
    string m_Addr;
    string m_Category;  // 分类（家人、朋友、同事等）
    string m_Company;   // 公司
    string m_Position;  // 职位
};

// 通讯录结构体
struct Addressbooks
{
    struct Person personArray[MAX];
    int m_Size;
};

// 函数声明
void addPerson(Addressbooks* abs);
void showPerson(Addressbooks* abs);
int isExist(Addressbooks* abs, string name);
void deletePerson(Addressbooks* abs);
void findPerson(Addressbooks* abs);
void modifyPerson(Addressbooks* abs);
void cleanPerson(Addressbooks* abs);
void showMenu();
void showAllCategories(Addressbooks* abs);
void searchByMultipleConditions(Addressbooks* abs);
void showStatistics(Addressbooks* abs);
void sortContacts(Addressbooks* abs);

// 1.添加联系人
void addPerson(Addressbooks* abs)
{
    if (abs->m_Size == MAX)
    {
        cout << "通讯录已满，无法添加!" << endl;
        return;
    }

    cout << "\n========== 添加联系人 ==========" << endl;

    string name;
    cout << "请输入姓名：";
    cin >> name;
    abs->personArray[abs->m_Size].m_Name = name;

    cout << "请输入性别：" << endl;
    cout << "1 --- 男" << endl;
    cout << "2 --- 女" << endl;
    int sex = 0;
    while (true)
    {
        cin >> sex;
        if (sex == 1 || sex == 2)
        {
            abs->personArray[abs->m_Size].m_Sex = sex;
            break;
        }
        cout << "输入有误，请重新输入: ";
    }

    cout << "请输入年龄：";
    int age = 0;
    cin >> age;
    abs->personArray[abs->m_Size].m_Age = age;

    cout << "请输入联系电话：";
    string phone;
    cin >> phone;
    abs->personArray[abs->m_Size].m_Phone = phone;

    cout << "请输入电子邮箱：";
    string email;
    cin >> email;
    abs->personArray[abs->m_Size].m_Email = email;

    cout << "请输入家庭住址：";
    string address;
    cin.ignore();  // 清除缓冲区
    getline(cin, address);
    abs->personArray[abs->m_Size].m_Addr = address;

    cout << "请选择分类：" << endl;
    cout << "1 --- 家人" << endl;
    cout << "2 --- 朋友" << endl;
    cout << "3 --- 同事" << endl;
    cout << "4 --- 同学" << endl;
    cout << "5 --- 其他" << endl;
    int categoryChoice = 0;
    while (true)
    {
        cin >> categoryChoice;
        switch (categoryChoice) {
        case 1: abs->personArray[abs->m_Size].m_Category = "家人"; break;
        case 2: abs->personArray[abs->m_Size].m_Category = "朋友"; break;
        case 3: abs->personArray[abs->m_Size].m_Category = "同事"; break;
        case 4: abs->personArray[abs->m_Size].m_Category = "同学"; break;
        case 5: abs->personArray[abs->m_Size].m_Category = "其他"; break;
        default: cout << "输入有误，请重新选择: "; continue;
        }
        break;
    }

    cout << "请输入公司名称（如无则输入-）：";
    string company;
    cin >> company;
    abs->personArray[abs->m_Size].m_Company = (company == "-") ? "" : company;

    cout << "请输入职位（如无则输入-）：";
    string position;
    cin >> position;
    abs->personArray[abs->m_Size].m_Position = (position == "-") ? "" : position;

    // 更新通讯录人数
    abs->m_Size++;

    cout << "\n添加成功！" << endl;

    system("pause");
    system("cls");
}

// 2.显示所有联系人信息
void showPerson(Addressbooks* abs)
{
    if (abs->m_Size == 0)
    {
        cout << "当前记录为空" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "\n========== 所有联系人信息 ==========" << endl;
    cout << "总联系人数量: " << abs->m_Size << endl;
    cout << string(100, '-') << endl;
    cout << left << setw(10) << "姓名"
        << setw(6) << "性别"
        << setw(6) << "年龄"
        << setw(15) << "电话"
        << setw(20) << "邮箱"
        << setw(10) << "分类"
        << setw(15) << "公司"
        << setw(15) << "职位"
        << setw(20) << "住址" << endl;
    cout << string(100, '-') << endl;

    for (int i = 0; i < abs->m_Size; i++)
    {
        cout << left << setw(10) << abs->personArray[i].m_Name
            << setw(6) << (abs->personArray[i].m_Sex == 1 ? "男" : "女")
            << setw(6) << abs->personArray[i].m_Age
            << setw(15) << abs->personArray[i].m_Phone
            << setw(20) << (abs->personArray[i].m_Email.empty() ? "无" : abs->personArray[i].m_Email)
            << setw(10) << abs->personArray[i].m_Category
            << setw(15) << (abs->personArray[i].m_Company.empty() ? "无" : abs->personArray[i].m_Company)
            << setw(15) << (abs->personArray[i].m_Position.empty() ? "无" : abs->personArray[i].m_Position)
            << setw(20) << abs->personArray[i].m_Addr << endl;
    }
    cout << string(100, '-') << endl;

    system("pause");
    system("cls");
}

// 3.删除指定联系人信息
void deletePerson(Addressbooks* abs)
{
    cout << "\n========== 删除联系人 ==========" << endl;
    cout << "请输入您要删除的联系人姓名：";
    string name;
    cin >> name;

    int ret = isExist(abs, name);
    if (ret != -1)
    {
        cout << "\n找到联系人：" << endl;
        cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
        cout << "电话：" << abs->personArray[ret].m_Phone << endl;

        cout << "确定要删除吗？(y/n): ";
        char confirm;
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            for (int i = ret; i < abs->m_Size - 1; i++)
            {
                abs->personArray[i] = abs->personArray[i + 1];
            }
            abs->m_Size--;
            cout << "删除成功" << endl;
        }
        else {
            cout << "已取消删除" << endl;
        }
    }
    else
    {
        cout << "查无此人" << endl;
    }

    system("pause");
    system("cls");
}

// 4.查找指定联系人信息（按姓名）
void findPerson(Addressbooks* abs)
{
    cout << "\n========== 查找联系人 ==========" << endl;
    cout << "请输入您要查找的联系人姓名：";
    string name;
    cin >> name;

    int ret = isExist(abs, name);
    if (ret != -1)
    {
        cout << "\n找到联系人：" << endl;
        cout << string(50, '-') << endl;
        cout << "姓名：" << abs->personArray[ret].m_Name << endl;
        cout << "性别：" << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << endl;
        cout << "年龄：" << abs->personArray[ret].m_Age << endl;
        cout << "电话：" << abs->personArray[ret].m_Phone << endl;
        cout << "邮箱：" << (abs->personArray[ret].m_Email.empty() ? "无" : abs->personArray[ret].m_Email) << endl;
        cout << "分类：" << abs->personArray[ret].m_Category << endl;
        cout << "公司：" << (abs->personArray[ret].m_Company.empty() ? "无" : abs->personArray[ret].m_Company) << endl;
        cout << "职位：" << (abs->personArray[ret].m_Position.empty() ? "无" : abs->personArray[ret].m_Position) << endl;
        cout << "住址：" << abs->personArray[ret].m_Addr << endl;
        cout << string(50, '-') << endl;
    }
    else
    {
        cout << "查无此人" << endl;
    }

    system("pause");
    system("cls");
}

// 5.修改指定联系人信息
void modifyPerson(Addressbooks* abs)
{
    cout << "\n========== 修改联系人 ==========" << endl;
    cout << "请输入您要修改的联系人姓名：";
    string name;
    cin >> name;

    int ret = isExist(abs, name);
    if (ret != -1)
    {
        cout << "\n找到联系人，当前信息：" << endl;
        cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
        cout << "电话：" << abs->personArray[ret].m_Phone << endl;

        cout << "\n请输入新的信息（直接回车保持原值）：" << endl;

        // 姓名
        cout << "请输入姓名 [" << abs->personArray[ret].m_Name << "]: ";
        cin.ignore();
        string newName;
        getline(cin, newName);
        if (!newName.empty()) {
            abs->personArray[ret].m_Name = newName;
        }

        // 性别
        cout << "请输入性别 (1-男, 2-女) [" << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "]: ";
        string sexInput;
        getline(cin, sexInput);
        if (!sexInput.empty()) {
            abs->personArray[ret].m_Sex = stoi(sexInput);
        }

        // 年龄
        cout << "请输入年龄 [" << abs->personArray[ret].m_Age << "]: ";
        string ageInput;
        getline(cin, ageInput);
        if (!ageInput.empty()) {
            abs->personArray[ret].m_Age = stoi(ageInput);
        }

        // 电话
        cout << "请输入联系电话 [" << abs->personArray[ret].m_Phone << "]: ";
        string phone;
        getline(cin, phone);
        if (!phone.empty()) {
            abs->personArray[ret].m_Phone = phone;
        }

        // 邮箱
        cout << "请输入电子邮箱 [" << abs->personArray[ret].m_Email << "]: ";
        string email;
        getline(cin, email);
        if (!email.empty()) {
            abs->personArray[ret].m_Email = email;
        }

        // 分类
        cout << "请选择分类 (1-家人, 2-朋友, 3-同事, 4-同学, 5-其他) [" << abs->personArray[ret].m_Category << "]: ";
        string categoryInput;
        getline(cin, categoryInput);
        if (!categoryInput.empty()) {
            int categoryChoice = stoi(categoryInput);
            switch (categoryChoice) {
            case 1: abs->personArray[ret].m_Category = "家人"; break;
            case 2: abs->personArray[ret].m_Category = "朋友"; break;
            case 3: abs->personArray[ret].m_Category = "同事"; break;
            case 4: abs->personArray[ret].m_Category = "同学"; break;
            case 5: abs->personArray[ret].m_Category = "其他"; break;
            }
        }

        // 公司
        cout << "请输入公司名称 [" << abs->personArray[ret].m_Company << "]: ";
        string company;
        getline(cin, company);
        abs->personArray[ret].m_Company = company;

        // 职位
        cout << "请输入职位 [" << abs->personArray[ret].m_Position << "]: ";
        string position;
        getline(cin, position);
        abs->personArray[ret].m_Position = position;

        // 地址
        cout << "请输入家庭住址 [" << abs->personArray[ret].m_Addr << "]: ";
        string address;
        getline(cin, address);
        if (!address.empty()) {
            abs->personArray[ret].m_Addr = address;
        }

        cout << "\n修改成功" << endl;
    }
    else
    {
        cout << "查无此人" << endl;
    }

    system("pause");
    system("cls");
}

// 6.清空所有联系人
void cleanPerson(Addressbooks* abs)
{
    cout << "\n========== 清空通讯录 ==========" << endl;
    cout << "确定要清空所有联系人吗？(y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        abs->m_Size = 0;
        cout << "通讯录已清空" << endl;
    }
    else {
        cout << "已取消操作" << endl;
    }

    system("pause");
    system("cls");
}

// 7.显示所有分类
void showAllCategories(Addressbooks* abs)
{
    if (abs->m_Size == 0) {
        cout << "通讯录为空" << endl;
        system("pause");
        system("cls");
        return;
    }

    vector<string> categories;
    vector<int> counts;

    // 收集所有分类
    for (int i = 0; i < abs->m_Size; i++) {
        string category = abs->personArray[i].m_Category;
        bool found = false;

        for (size_t j = 0; j < categories.size(); j++) {
            if (categories[j] == category) {
                counts[j]++;
                found = true;
                break;
            }
        }

        if (!found) {
            categories.push_back(category);
            counts.push_back(1);
        }
    }

    cout << "\n========== 通讯录分类统计 ==========" << endl;
    cout << "总联系人: " << abs->m_Size << " 人" << endl;
    cout << string(30, '-') << endl;
    cout << left << setw(10) << "分类" << setw(10) << "人数" << setw(10) << "比例" << endl;
    cout << string(30, '-') << endl;

    for (size_t i = 0; i < categories.size(); i++) {
        float ratio = (float)counts[i] / abs->m_Size * 100;
        cout << left << setw(10) << categories[i]
            << setw(10) << counts[i]
            << fixed << setprecision(1) << ratio << "%" << endl;
    }

    cout << "\n按分类查看联系人：" << endl;
    for (size_t i = 0; i < categories.size(); i++) {
        cout << i + 1 << ". " << categories[i] << endl;
    }
    cout << "0. 返回主菜单" << endl;

    int choice;
    cout << "\n请选择要查看的分类编号: ";
    cin >> choice;

    if (choice > 0 && choice <= (int)categories.size()) {
        string selectedCategory = categories[choice - 1];
        cout << "\n========== " << selectedCategory << " 分类联系人 ==========" << endl;

        int count = 0;
        for (int i = 0; i < abs->m_Size; i++) {
            if (abs->personArray[i].m_Category == selectedCategory) {
                cout << left << setw(10) << abs->personArray[i].m_Name
                    << setw(15) << abs->personArray[i].m_Phone
                    << setw(20) << (abs->personArray[i].m_Email.empty() ? "无" : abs->personArray[i].m_Email)
                    << setw(15) << (abs->personArray[i].m_Company.empty() ? "无" : abs->personArray[i].m_Company) << endl;
                count++;
            }
        }
        cout << "共 " << count << " 人" << endl;
    }

    system("pause");
    system("cls");
}

// 8.多条件搜索
void searchByMultipleConditions(Addressbooks* abs)
{
    if (abs->m_Size == 0) {
        cout << "通讯录为空" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "\n========== 多条件搜索 ==========" << endl;
    cout << "请选择搜索条件：" << endl;
    cout << "1. 按姓名搜索" << endl;
    cout << "2. 按电话搜索" << endl;
    cout << "3. 按邮箱搜索" << endl;
    cout << "4. 按公司搜索" << endl;
    cout << "5. 按分类搜索" << endl;
    cout << "6. 按年龄范围搜索" << endl;
    cout << "0. 返回主菜单" << endl;

    int choice;
    cout << "\n请选择: ";
    cin >> choice;

    vector<int> results;

    switch (choice) {
    case 1: { // 按姓名搜索
        cout << "请输入姓名（支持模糊搜索）: ";
        string name;
        cin >> name;

        for (int i = 0; i < abs->m_Size; i++) {
            if (abs->personArray[i].m_Name.find(name) != string::npos) {
                results.push_back(i);
            }
        }
        break;
    }
    case 2: { // 按电话搜索
        cout << "请输入电话（支持模糊搜索）: ";
        string phone;
        cin >> phone;

        for (int i = 0; i < abs->m_Size; i++) {
            if (abs->personArray[i].m_Phone.find(phone) != string::npos) {
                results.push_back(i);
            }
        }
        break;
    }
    case 3: { // 按邮箱搜索
        cout << "请输入邮箱（支持模糊搜索）: ";
        string email;
        cin >> email;

        for (int i = 0; i < abs->m_Size; i++) {
            if (!abs->personArray[i].m_Email.empty() &&
                abs->personArray[i].m_Email.find(email) != string::npos) {
                results.push_back(i);
            }
        }
        break;
    }
    case 4: { // 按公司搜索
        cout << "请输入公司名称（支持模糊搜索）: ";
        string company;
        cin >> company;

        for (int i = 0; i < abs->m_Size; i++) {
            if (!abs->personArray[i].m_Company.empty() &&
                abs->personArray[i].m_Company.find(company) != string::npos) {
                results.push_back(i);
            }
        }
        break;
    }
    case 5: { // 按分类搜索
        cout << "请选择分类：" << endl;
        cout << "1. 家人 2. 朋友 3. 同事 4. 同学 5. 其他" << endl;
        int catChoice;
        cout << "请选择: ";
        cin >> catChoice;

        string category;
        switch (catChoice) {
        case 1: category = "家人"; break;
        case 2: category = "朋友"; break;
        case 3: category = "同事"; break;
        case 4: category = "同学"; break;
        case 5: category = "其他"; break;
        default: cout << "无效选择" << endl; break;
        }

        for (int i = 0; i < abs->m_Size; i++) {
            if (abs->personArray[i].m_Category == category) {
                results.push_back(i);
            }
        }
        break;
    }
    case 6: { // 按年龄范围搜索
        int minAge, maxAge;
        cout << "请输入最小年龄: ";
        cin >> minAge;
        cout << "请输入最大年龄: ";
        cin >> maxAge;

        for (int i = 0; i < abs->m_Size; i++) {
            if (abs->personArray[i].m_Age >= minAge &&
                abs->personArray[i].m_Age <= maxAge) {
                results.push_back(i);
            }
        }
        break;
    }
    case 0:
        system("cls");
        return;
    default:
        cout << "无效选择" << endl;
        system("pause");
        system("cls");
        return;
    }

    // 显示搜索结果
    if (results.empty()) {
        cout << "\n未找到匹配的联系人" << endl;
    }
    else {
        cout << "\n找到 " << results.size() << " 个匹配的联系人：" << endl;
        cout << string(80, '-') << endl;
        cout << left << setw(10) << "姓名"
            << setw(6) << "性别"
            << setw(6) << "年龄"
            << setw(15) << "电话"
            << setw(20) << "邮箱"
            << setw(10) << "分类"
            << setw(15) << "公司" << endl;
        cout << string(80, '-') << endl;

        for (size_t i = 0; i < results.size(); i++) {
            int idx = results[i];
            cout << left << setw(10) << abs->personArray[idx].m_Name
                << setw(6) << (abs->personArray[idx].m_Sex == 1 ? "男" : "女")
                << setw(6) << abs->personArray[idx].m_Age
                << setw(15) << abs->personArray[idx].m_Phone
                << setw(20) << (abs->personArray[idx].m_Email.empty() ? "无" : abs->personArray[idx].m_Email)
                << setw(10) << abs->personArray[idx].m_Category
                << setw(15) << (abs->personArray[idx].m_Company.empty() ? "无" : abs->personArray[idx].m_Company) << endl;
        }
    }

    system("pause");
    system("cls");
}

// 9.显示统计信息
void showStatistics(Addressbooks* abs)
{
    if (abs->m_Size == 0) {
        cout << "通讯录为空" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "\n========== 通讯录统计信息 ==========" << endl;

    int maleCount = 0, femaleCount = 0;
    int totalAge = 0;
    int minAge = 200, maxAge = 0;

    // 按分类统计
    vector<string> categories;
    vector<int> categoryCounts;

    for (int i = 0; i < abs->m_Size; i++) {
        // 统计性别
        if (abs->personArray[i].m_Sex == 1) maleCount++;
        else femaleCount++;

        // 统计年龄
        totalAge += abs->personArray[i].m_Age;
        if (abs->personArray[i].m_Age < minAge) minAge = abs->personArray[i].m_Age;
        if (abs->personArray[i].m_Age > maxAge) maxAge = abs->personArray[i].m_Age;

        // 统计分类
        string category = abs->personArray[i].m_Category;
        bool found = false;
        for (size_t j = 0; j < categories.size(); j++) {
            if (categories[j] == category) {
                categoryCounts[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            categories.push_back(category);
            categoryCounts.push_back(1);
        }
    }

    float avgAge = (float)totalAge / abs->m_Size;

    cout << "总联系人: " << abs->m_Size << " 人" << endl;
    cout << "性别分布: 男 " << maleCount << " 人 (" << fixed << setprecision(1)
        << (float)maleCount / abs->m_Size * 100 << "%), 女 " << femaleCount << " 人 ("
        << (float)femaleCount / abs->m_Size * 100 << "%)" << endl;
    cout << "年龄统计: 平均 " << avgAge << " 岁, 最小 " << minAge << " 岁, 最大 " << maxAge << " 岁" << endl;

    cout << "\n分类统计:" << endl;
    cout << string(30, '-') << endl;
    for (size_t i = 0; i < categories.size(); i++) {
        cout << left << setw(10) << categories[i] << ": "
            << categoryCounts[i] << " 人 ("
            << fixed << setprecision(1) << (float)categoryCounts[i] / abs->m_Size * 100 << "%)" << endl;
    }

    system("pause");
    system("cls");
}

// 10.排序联系人
void sortContacts(Addressbooks* abs)
{
    if (abs->m_Size == 0) {
        cout << "通讯录为空" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "\n========== 排序联系人 ==========" << endl;
    cout << "请选择排序方式：" << endl;
    cout << "1. 按姓名排序" << endl;
    cout << "2. 按年龄排序" << endl;
    cout << "3. 按分类排序" << endl;
    cout << "0. 取消排序" << endl;

    int choice;
    cout << "\n请选择: ";
    cin >> choice;

    // 创建临时数组用于排序
    vector<Person> tempArray;
    for (int i = 0; i < abs->m_Size; i++) {
        tempArray.push_back(abs->personArray[i]);
    }

    switch (choice) {
    case 1: // 按姓名排序
        sort(tempArray.begin(), tempArray.end(), [](const Person& a, const Person& b) {
            return a.m_Name < b.m_Name;
            });
        cout << "已按姓名排序" << endl;
        break;
    case 2: // 按年龄排序
        sort(tempArray.begin(), tempArray.end(), [](const Person& a, const Person& b) {
            return a.m_Age < b.m_Age;
            });
        cout << "已按年龄排序" << endl;
        break;
    case 3: // 按分类排序
        sort(tempArray.begin(), tempArray.end(), [](const Person& a, const Person& b) {
            if (a.m_Category == b.m_Category) {
                return a.m_Name < b.m_Name;
            }
            return a.m_Category < b.m_Category;
            });
        cout << "已按分类排序" << endl;
        break;
    case 0:
        cout << "已取消排序" << endl;
        system("pause");
        system("cls");
        return;
    default:
        cout << "无效选择" << endl;
        system("pause");
        system("cls");
        return;
    }

    // 将排序后的数据复制回原数组
    for (size_t i = 0; i < tempArray.size(); i++) {
        abs->personArray[i] = tempArray[i];
    }

    cout << "\n排序完成，是否显示排序结果？(y/n): ";
    char show;
    cin >> show;

    if (show == 'y' || show == 'Y') {
        showPerson(abs);
    }
    else {
        system("cls");
    }
}

// 检测联系人是否存在
int isExist(Addressbooks* abs, string name)
{
    for (int i = 0; i < abs->m_Size; i++)
    {
        if (abs->personArray[i].m_Name == name)
        {
            return i;
        }
    }
    return -1;
}

// 菜单界面
void showMenu()
{
    cout << "===================================" << endl;
    cout << "*****    个人通讯录管理系统    *****" << endl;
    cout << "===================================" << endl;
    cout << "*****  1. 添加联系人           *****" << endl;
    cout << "*****  2. 显示所有联系人       *****" << endl;
    cout << "*****  3. 删除联系人           *****" << endl;
    cout << "*****  4. 查找联系人(按姓名)   *****" << endl;
    cout << "*****  5. 修改联系人           *****" << endl;
    cout << "*****  6. 多条件搜索联系人     *****" << endl;
    cout << "*****  7. 显示分类管理         *****" << endl;
    cout << "*****  8. 显示统计信息         *****" << endl;
    cout << "*****  9. 排序联系人           *****" << endl;
    cout << "*****  10. 清空通讯录          *****" << endl;
    cout << "*****  0. 退出系统             *****" << endl;
    cout << "===================================" << endl;
    cout << "请选择操作 (0-10): ";
}

int main() {
    int select = 0;
    Addressbooks abs;
    abs.m_Size = 0;

    while (true)
    {
        showMenu();
        cin >> select;

        switch (select)
        {
        case 1:
            addPerson(&abs);
            break;
        case 2:
            showPerson(&abs);
            break;
        case 3:
            deletePerson(&abs);
            break;
        case 4:
            findPerson(&abs);
            break;
        case 5:
            modifyPerson(&abs);
            break;
        case 6:
            searchByMultipleConditions(&abs);
            break;
        case 7:
            showAllCategories(&abs);
            break;
        case 8:
            showStatistics(&abs);
            break;
        case 9:
            sortContacts(&abs);
            break;
        case 10:
            cleanPerson(&abs);
            break;
        case 0:
            cout << "\n感谢使用个人通讯录管理系统，再见！" << endl;
            system("pause");
            return 0;
        default:
            cout << "输入错误，请重新输入！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;

}
