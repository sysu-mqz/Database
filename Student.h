#pragma once
#ifndef STUDENT_H_
#define STUDENT_H_
#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<memory>
#include<set>
#include <iterator>
#include<vector>

using namespace std;
class Date                                      //Date类保存生日
{
private:
	int year;
	int month;
	int day;
public:
	Date(int y = 2000, int m = 1, int d = 1) :year(y), month(m), day(d) {}
	 int getY() { return year; }
	 int getM() { return month; }
	 int getD() { return day; }
	 void setdate(int year_, int month_, int day_) { year = year_; month = month_; day = day_; }

};
class Course                                           //Course类保存成绩学分,然后添加入map，map的key值为课程名
{
private:
	double credits;
	int score;
public:
	Course(double credits_, int score_) :credits(credits_), score(score_) {}
	~Course() {}
	inline double getCredits() { return credits; }
	inline int getScore() { return score; }
};

class Student                                       //Student集中保存各学生信息
{
public:
	string id;
	string name;
	string sex;
	Date birthday;
	int schoolYear;
	string birthplace;
	map<string, Course> courses;                                          //保存学生每一门课程信息
public:
	Student(string id_ = "0", string name_ = " ", string sex_ = " ",Date birthday_ = NULL, int schoolYear_ = 0, string birthplace_ =" ")
		:id(id_), name(name_), sex(sex_), birthday(birthday_), schoolYear(schoolYear_), birthplace(birthplace_) {}
	~Student() {}
	 void setID(string id_) { id = id_; }      //各个存函数
     void setName(string name_) { name = name_; }
	 void setSex(string sex_) { sex = sex_; }
	 void setBirthday(int byear, int bmonth, int bday) { birthday.setdate(byear, bmonth, bday); }
	void setSchoolYear(int year) { schoolYear = year; }
	 void setBirthPlace(string bplace) { birthplace = bplace; }
	void setCourse(string courseName, double credits, int score);     //   设置添加每一门课程信息
	void Total();                                                       //计算加入总分信息
	bool operator <(const Student& s) const { return id < s.id; }      //为set提供排序规则
	string getid() { return id; }      //取函数
	string getname() { return name; }
	string getsex() { return sex; }
	int getY() { return birthday.getY(); }
	int getM() { return birthday.getM(); }
    int getD() {return birthday.getD();}
	int getschoolyear(){ return schoolYear; }
	string getbirthplace() { return birthplace; }
	map<string, Course>getcourses() { return courses; }
};

map<string, Student>students;//记录双表总信息

void Student::setCourse(string courseName, double credits, int score)       // 设置添加每一门课程信息
{
	Course course_(credits, score);
	courses.insert(pair<string, Course>(courseName, course_));
}

void Student::Total()                                                        //计算加入总分信息        
{
	int totalscore = 0;
	double totalcredits = 0;
	for (auto iter = courses.begin(); iter != courses.end(); iter++)
	{
		totalscore += iter->second.getScore();
		totalcredits += iter->second.getCredits();
	}
	Course Totalcourse(totalcredits, totalscore);
	courses.insert(pair<string, Course>("Total", Totalcourse)); 
}


ostream& operator<<(ostream& out, Date& d)                                //重载Date型<<运算符
{
	out << d.getY() << "/" << d.getM() << "/" << d.getD();
	return out;
}
ostream& operator<<(ostream& out, Course& course)                        //重载Course型
{
	out << course.getScore() << " " << course.getCredits();
	return out;
}
ostream& operator<<(ostream& out, map<string, Course>& courseScore)       //重载map<string,Course>型
{
	map<string, Course>::iterator iter;
	for (iter = courseScore.begin(); iter != courseScore.end(); iter++)
	{
		out << iter->first << ":" << iter->second << "\t";
	}
	return out;
}
ostream& operator<<(ostream& out, Student& s)                             //重载Student型，包含基本信息和课程信息
{
	out << s.id << "\t" << s.name << "\t" << s.sex << "\t" << s.birthday << "\t" << s.schoolYear << "\t" << s.birthplace << "\n" << s.courses;
	return out;
}

ostream& operator<<(ostream& out, map<string, Student>& stu)               
{
	for (auto iter = stu.begin(); iter != stu.end(); iter++)
		out << iter->second << endl;
	return out;
}

ostream& operator<<(ostream& out, map<int, Student>& stu)
{
	for (auto iter = stu.begin(); iter != stu.end(); iter++)
		out << iter->second << "\n";
	return out;
}

//重载用于多条件查询的&&及||
map<string, Student> operator&&(map<string, Student> s1, map<string, Student>s2)
{
	set<Student>set1; set<Student>set2; set<Student>set3;
	map<string, Student>intersection;;
	for (auto iter = s1.begin(); iter != s1.end(); iter++)
		set1.insert(iter->second);
	for (auto iter = s2.begin(); iter != s2.end(); iter++)
		set2.insert(iter->second);
	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(set3, set3.begin()));
	for (auto iter = set3.begin(); iter != set3.end(); iter++)
	{
		intersection.insert(pair<string, Student>(iter->id, *iter));
	}
	return intersection;;
}


map<string, Student> operator||(map<string, Student> s1, map<string, Student> s2)
{
	set<Student>set1; set<Student>set2; set<Student>set3;
	map<string, Student>union_;
	for (auto iter = s1.begin(); iter!= s1.end(); iter++)
		set1.insert(iter->second);
	for (auto iter = s2.begin(); iter != s2.end(); iter++)
		set2.insert(iter->second);
	set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(set3, set3.begin()));
	for (auto iter= set3.begin(); iter != set3.end(); iter++)
	{
		union_.insert(pair<string, Student>(iter->id, *iter));
	}
	return union_;
}


map<string, Student> operator<(string what, int num)                 //查询出生年，学年，分数
{
	if (what == "BirthdayYear")
	{
		map<string, Student>birthyear;
		for (auto iter = students.begin(); iter!= students.end(); iter++)
		{
			if (((iter->second).birthday).getY() < num)
			{
				birthyear.insert(pair<string, Student>(iter->first, iter->second));
			}
		}
		return birthyear;
	}
	else if (what== "SchoolYear")
	{
		map<string, Student>schoolyear;
		for (auto iter = students.begin(); iter != students.end(); iter++)
		{
			if ((iter->second).schoolYear < num)
			{
				schoolyear.insert(pair<string, Student>(iter->first, iter->second));
			}
		}
		return schoolyear;
	}
	else
	{
		int score;
		map<string, Student>course;
		for (auto iter = students.begin(); iter!= students.end(); iter++)
		{
			score = ((iter->second).courses).find(what)->second.getScore();
			if ( score< num)    //比较该门成绩
			{
				course.insert(pair<string, Student>(iter->first, iter->second));
			}
		}
		return course;
	}
}


map<string, Student> operator>(string choice, int num)  
{
	if (choice == "BirthdayYear")
	{
		map<string, Student>birthyear;
		map<string, Student>::iterator pos;
		for (pos = students.begin(); pos != students.end(); pos++)
		{
			if ((pos->second).getY() > num)
			{
				birthyear.insert(pair<string, Student>(pos->first, pos->second));
			}
		}
		return birthyear;
	}
	else if (choice == "SchoolYear")
	{
		map<string, Student>schoolyear;
		map<string, Student>::iterator pos;
		for (pos = students.begin(); pos != students.end(); pos++)
		{
			if ((pos->second).getschoolyear() > num)
			{
				schoolyear.insert(pair<string, Student>(pos->first, pos->second));
			}
		}
		return schoolyear;
	}
	else
	{
		map<string, Student>course;
		map<string, Student>::iterator pos;
		for (pos = students.begin(); pos != students.end(); pos++)
		{
			if (((pos->second).courses).find(choice)->second.getScore() > num)
			{
				course.insert(pair<string, Student>(pos->first, pos->second));
			}
		}
		return course;
	}
}


map<string, Student> operator==(string sex1, char sex_)  //判断性别
{
	string realsex;
	if (sex_ == 'M') realsex = "Male";
	else
		realsex = "Female";
	map<string, Student>chosesex;
	for (auto pos = students.begin(); pos != students.end(); pos++)
	{
		if ((pos->second).getsex()== realsex)
		{
			chosesex.insert(pair<string, Student>(pos->first, pos->second));
		}
	}
	return chosesex;
}


map<string, Student>operator==(string schoolYear, int year)
{
	if (schoolYear == "schoolYear")
	{
		map<string, Student>schoolyear;
		map<string, Student>::iterator pos;
		for (pos = students.begin(); pos != students.end(); pos++)
		{
			if ((pos->second).getschoolyear() == year)
			{
				schoolyear.insert(pair<string, Student>(pos->first, pos->second));
			}
		}
		return schoolyear;
	}
}

//展示平均分符合范围的名单的函数
map<string, Student> showAverage(int low = 0, int up = 0)
{
	map<string, Student>Average;
	map<string, Student>::iterator pos;
	for (pos = students.begin(); pos != students.end(); pos++)
	{
		int average = ((pos->second).getcourses()).find("Total")->second.getScore() / (((pos->second).courses).size() - 1);
		if (average > low&& average <= up)
			Average.insert(pair<string, Student>(pos->first, pos->second));
	}
	return Average;
}

//查询学分是否达到要求
map<string, Student> Credits(double credit)
{
	map<string, Student>credits;
	for (auto iter= students.begin(); iter != students.end(); iter++)
	{
		double all_credits = ((iter->second).getcourses()).find("Total")->second.getCredits();//得到总学分
		if (all_credits >= credit)
			credits.insert(pair<string, Student>(iter->first, iter->second));
	}
	return credits;
}
#endif //STUDENTI_H_
