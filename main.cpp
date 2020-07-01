#include"Student.h"
using namespace std;
// 将学生按姓名排序
void SortByName(map<string, Student> & students)
{
	map<string, Student>sortByName;
	for (auto iter = students.begin(); iter != students.end(); iter++)
		sortByName.insert(make_pair((iter->second).name, iter->second));
	cout << "按姓名排序：\n";
	cout << sortByName;
}

//将学生单学科分数排序
void SortByScore(map<string, Student>& students, string courseName, int min = 0, int max = 0)
{
	map<int, Student>sortByScore;
	int score;
	for (auto iter = students.begin(); iter != students.end(); iter++)
	{
		score = ((((iter->second).getcourses()).find(courseName))->second).getScore();
		if(score>=min&&score<=max)
		sortByScore.insert(pair<int, Student>(score, iter->second));
	}
	
	cout << courseName << "在" << min << "和" << max << "之间的学生有：" << endl;
		for (map<int, Student>::iterator iter1 = sortByScore.begin();iter1!= sortByScore.end(); iter1++)
		{
			cout << iter1->second << "\n";
		}
}
//按总分排序
void SortByTotalscore(map<string, Student>& students, int min = 0, int max = 0)
{
	map<int, Student>sortByTotalscore;
	int total_score;
	for (auto iter = students.begin(); iter != students.end(); iter++)
	{
		total_score = ((((iter->second).getcourses()).find("Total"))->second).getScore();
		if (total_score >= min && total_score <= max)
			sortByTotalscore.insert(pair<int, Student>(total_score, iter->second));
	}

	cout << "总分在" << min << "和" << max << "之间的学生有：" << endl;
	for (map<int, Student>::iterator iter1 = sortByTotalscore.begin(); iter1 != sortByTotalscore.end(); iter1++)
	{
		cout << iter1->second << "\n";
	}

}
//删除符合多条件查询要求的学生
void Delete(map<string, Student>target)
{
	cout << "符合条件的学生有:\n" << target << "\n";
	map<string, Student>students1 = students;
	map<string, Student>::iterator pos;
	for (pos = target.begin(); pos != target.end(); pos++)
	{
		students1.erase(pos->first);
	}
	cout << "已将上述学生从列表中删除，新列表为：\n" << students1;
}

void myfile()
{
	ifstream file1;                                                              //输入第一个文件
	Date date;
	Student stu("", "", "", date, 0, "");
	file1.open("StudentInfo.txt");
	if (file1.fail())
	{
		cerr << "传入文件失败" << endl;
	}
	string str, all;
	string byear, bmonth, bday;
	string id, name, sex, birthday, school_year, birthplace;
	string::size_type start = 1;
	string::size_type end = 0;
	while (getline(file1, str))
	{
		if (str[0] == '#')
			continue;
		istringstream line(str);
		line >> id >> name >> sex >> birthday >> school_year >> birthplace;
		stu.setID(id); stu.setSex(sex); stu.setName(name);
		stu.setSchoolYear(stoi(school_year)); stu.setBirthPlace(birthplace);
		end = birthday.find("/");
		byear.assign(birthday, start, end - start);
		start = birthday.find_first_not_of("/", end);
		end = birthday.find_first_of("/", start);
		bmonth.assign(birthday, start, end - start);
		start = birthday.find_first_not_of("/", end);
		end = birthday.length();
		bday.assign(birthday, start, end - start + 1);
		stu.setBirthday(stoi(byear), stoi(bmonth), stoi(bday));
		students.insert(pair<string, Student>(id, stu));                 //保存基本信息   
	}
	ifstream file2;                                       //输入第二个文件
	file2.open("StudentCourse.txt");
	if (file2.fail())
	{
		cerr << "传入文件失败" << endl;
	}
	string str_, all_;
	while (getline(file2, str_))
	{
		all_ = all_ + str_ + " ";
	}
	int _scores;
	double _credits;
	string course_, credits_, scores_, k;
	start = all_.find("109");
	map<string, int> m;
	for (int i = 0; i <= 27; i++)
	{
		end = all_.find_first_of("\t", start);
		id.assign(all_, start, end - start);
		start = all_.find_first_not_of("\t", end);
		if (" " == k.assign(all_, start + 1, 1))                               //按几节识别保存课程名
		{
			course_ = "C ";
			end = all_.find_first_of(" ", start);
			start = all_.find_first_not_of(" ", end);
			end = all_.find_first_of(" ", start);
			course_ = course_ + k.assign(all_, start, end - start);
			start = all_.find_first_not_of(" ", end);
			end = all_.find_first_of("\t", start);
			course_ = course_ + " " + k.assign(all_, start, end - start);
		}
		else if ("P" == k.assign(all_, start, 1))
		{
			end = all_.find_first_of("\t", start);
			course_.assign(all_, start, end - start);
		}
		else
		{
			end = all_.find_first_of(" ", start);
			course_ = k.assign(all_, start, end - start);
			start = all_.find_first_not_of(" ", end);
			end = all_.find_first_of("\t", start);
			course_ = course_ + " " + k.assign(all_, start, end - start);
		}
		start = all_.find_first_not_of("\t", end);
		end = all_.find_first_of("\t", start);
		_credits = stod(credits_.assign(all_, start, end - start));
		start = all_.find_first_not_of("\t", end);
		end = all_.find(" ", start);
		_scores = stoi(scores_.assign(all_, start, end - start));
		start = end + 1;
		(students.find(id))->second.setCourse(course_, _credits, _scores);               //保存课程信息      
	}
	map<string, Student>::iterator iter_total;
	for (iter_total = students.begin(); iter_total != students.end(); iter_total++)
	{
		iter_total->second.Total();                                                   //得到各学生总成绩，总学分
	}
}

void Test()                                  //试用各功能
{
	map<string, Student> result;
	ofstream file3;
	file3.open("result.txt");
	string course2 = "College English";
	string sex = "sex";
	string schoolYear = "schoolYear";
	myfile();
	cout << "1.按姓名排序:\n";
	SortByName(students);
	cout << endl;
	cout << "2.单科范围查询(以C Programming Language为例):"<<endl;
	string course1 = "C Programming Language";
	SortByScore(students,course1, 50, 80);
	cout << "\n";
	string str = "SchoolYear";
	cout << "多条件查询并删除操作：\n多条件为：(sex == 'F') && (SchoolYear > 2017) || (C Programming Language < 80))\n";
	Delete((sex == 'F') && ((str > 70) || (course1 < 80)));
	cout << "\n";

	cout << "\n以下内容同步输出到result.txt中\n";
	cout << "1.打印2018级选修C语言且成绩小于60分的学生\n";
	file3 << "1.打印2018级选修C语言且成绩小于60分的学生\n";
	result = ((schoolYear == 2018) && (course1 < 60));
	cout << result << "\n";
	file3 << result << "\n";
	result = showAverage(80, 100);
	cout << "2.统计课程平均分大于80的学生个人信息并输出\n";
	file3 << "2.统计课程平均分大于80的学生个人信息并输出\n";
	cout  << result << "\n";
	file3 << result << "\n";
	cout << "3.查询每个学生是否修满12学分\n";
	file3 << "3.查询每个学生是否修满12学分\n";
	result = Credits(12);
	cout << "总学分标准为：" << 12 << "分,以下同学达到\n" << result << "\n";
	file3 << "总学分标准为：" << 12 << "分,以下同学未达到\n" << result << "\n";
}
int main()
{
	Test();
	return 0;
}
