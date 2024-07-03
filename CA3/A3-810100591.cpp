#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#define NUM_OF_ZANG 3
#define NUM_OF_CLASS 2
#define FORBIDEN '0'
#define FREE '1'
#define EMPTY '0'
#define FULL '1'
#define NOTFOUND '4'
#define NOT_FOUND 4

using namespace std;

struct Zang
{
    int start_hour;
    int start_min;
    int end_hour;
    int end_min;
};

struct Day
{
    string name;
    vector<char> free_zang{EMPTY, EMPTY, EMPTY};
};

struct Teacher
{
    string name;
    vector<string> courses;
    vector<Day> schedule;
};

struct Schadule
{
    string teacher_name;
    int zang_class;
};

struct Course
{
    string name;
    string day1;
    string day2;
    vector<char> allowable_zang{FORBIDEN, FORBIDEN, FORBIDEN};
    vector<Schadule> course_state{{"0", NOT_FOUND}, {"0", NOT_FOUND}};
};

const vector<string> zangs{"07:30 09:00", "09:30 11:00", "11:30 13:00"};
const vector<Zang> school_time{{7, 30, 9, 0}, {9, 30, 11, 0}, {11, 30, 13, 0}};
const vector<string> week{"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};

bool compare_by_teacher_name(const Teacher &e1, const Teacher &e2)
{
    return e1.name < e2.name;
}

vector<Teacher> input_teachers(int teacher_num)
{
    vector<Teacher> teacher_list;
    Day temp_day;
    int num_of_free_days, num_course;
    string temp_course_name;
    for (int i = 0; i < teacher_num; i++)
    {
        Teacher temp_teacher;
        cin >> temp_teacher.name >> num_of_free_days;
        for (int j = 0; j < num_of_free_days; j++)
        {
            cin >> temp_day.name;
            temp_teacher.schedule.push_back(temp_day);
        }
        cin >> num_course;
        for (int j = 0; j < num_course; j++)
        {
            cin >> temp_course_name;
            temp_teacher.courses.push_back(temp_course_name);
        }
        teacher_list.push_back(temp_teacher);
    }
    return teacher_list;
}

bool is_allowable_zang(int start_h, int start_m, int end_h, int end_m, int index_zang)
{
    int prob_start = 0, prob_end = 0;
    if ((start_h < (school_time[index_zang]).start_hour) ||
        ((start_h == (school_time[index_zang]).start_hour) && (start_m <= (school_time[index_zang]).start_min)))
    {
        prob_start = 1;
    }
    if ((end_h > (school_time[index_zang]).end_hour) ||
        ((end_h == (school_time[index_zang]).end_hour) && (end_m >= (school_time[index_zang]).end_min)))
    {
        prob_end = 1;
    }
    if (prob_start && prob_end)
    {
        return true;
    }
    return false;
}

bool compare_by_course_name(const Course &e1, const Course &e2)
{
    return e1.name < e2.name;
}

vector<Course> input_course(int course_num)
{
    char trash;
    int start_h, start_m, end_h, end_m;
    vector<Course> course_list;
    for (int i = 0; i < course_num; i++)
    {
        Course temp_course;
        cin >> temp_course.name >> temp_course.day1 >> temp_course.day2 >> start_h >> trash >> start_m >> end_h >> trash >> end_m;
        for (int k = 0; k < school_time.size(); k++)
        {
            if (is_allowable_zang(start_h, start_m, end_h, end_m, k))
            {
                temp_course.allowable_zang[k] = FREE;
            }
        }
        course_list.push_back(temp_course);
    }
    return course_list;
}

void prepare_input_data(vector<Course> &course_list, vector<Teacher> &teacher_list)
{
    int num_teacher, num_course;
    cin >> num_teacher;
    teacher_list = input_teachers(num_teacher);
    std::sort(teacher_list.begin(), teacher_list.end(), compare_by_teacher_name);
    cin >> num_course;
    course_list = input_course(num_course);
    std::sort(course_list.begin(), course_list.end(), compare_by_course_name);
}

bool is_in_vect(string course_name, const vector<string> &failed_courses)
{
    //چک میکند که ایا یک عنصر خاص در بردار وجود رارد یا نه
    for(int l=0;l<failed_courses.size();l++)
    {
        if(course_name==failed_courses[l])
        {
            return true;
        }
    }
    return false;
}

Course *find_Course_for_zang(string day_name, int zang, vector<Course> &course_list,
                    map<string, vector<char>> &the_class, int class_index, const vector<string> &failed_course)
{
    if (course_list.size() == 0)
    {
        return NULL;
    }
    Course *prop_course;
    for (int i = 0; i < course_list.size(); i++)
    {
        if ((course_list[i].day1 == day_name || course_list[i].day2 == day_name) &&
            course_list[i].allowable_zang[zang] == FREE && course_list[i].course_state[class_index].zang_class == NOT_FOUND)
        {
            if (the_class[course_list[i].day1][zang] == EMPTY && the_class[course_list[i].day2][zang] == EMPTY)
            {
                if ((!is_in_vect(course_list[i].name, failed_course)&&failed_course.size()!=0)||failed_course.size()==0)
                {
                    prop_course = &course_list[i];
                    break;
                }
            }
        }
        if (i == (course_list.size() - 1))
        {
            return NULL;
        }
    }
    return prop_course;
}

int find_day_form_teachers(const Teacher &teacher, string day_name)
{
    for (int i = 0; i < teacher.schedule.size(); i++)
    {
        if (teacher.schedule[i].name == day_name)
        {
            return i;
        }
    }
    return -1;
}
//بهتر است نام را اینگونه تغییر دهید.
bool find_course_form_teacher(const Teacher &teacher, string course_name)
{
    for (string course : teacher.courses)
    {
        //بررسی میکند که ایا 
        if (course == course_name)
        {
            return true;
        }
    }
    return false;
}

Teacher *find_teacher_for_course(string course_name, string day1, string day2, int zang, vector<Teacher> &teacher_list, int &day1_ind, int &day2_ind)
{
    char state=EMPTY;
    Teacher *prop_teacher, curr_teacher;
    if (teacher_list.size() == 0)
    {
        return NULL;
    }
    for(int i=0; i<teacher_list.size();i++)
    {
        curr_teacher=teacher_list[i];
        if(find_course_form_teacher(curr_teacher,course_name))
        {
            int day1_index = find_day_form_teachers(curr_teacher, day1);
            int day2_index = find_day_form_teachers(curr_teacher, day2);
            if(day1_index!=-1&&day2_index!=-1&&curr_teacher.schedule[day1_index].free_zang[zang]==EMPTY&&curr_teacher.schedule[day2_index].free_zang[zang]==EMPTY)
            {
                if(state==EMPTY)
                {
                    prop_teacher=&(teacher_list[i]);
                    day1_ind=day1_index;
                    day2_ind=day2_index;
                    state=FULL;
                }
                else if(curr_teacher.schedule.size()<prop_teacher->schedule.size())
                {
                    prop_teacher=&(teacher_list[i]);
                    day1_ind=day1_index;
                    day2_ind=day2_index;
                }
            }
        }
    }
    if(state==FULL)
    {
        return prop_teacher;
    }
    return NULL;
}

void set_course(Course *prop_course, Teacher *prop_teacher, int class_index, int day1_ind, int day2_ind, int zang_code)
{
    prop_course->course_state[class_index].zang_class = zang_code;
    prop_course->course_state[class_index].teacher_name=prop_teacher->name;
    prop_teacher->schedule[day1_ind].free_zang[zang_code] = FULL;
    prop_teacher->schedule[day2_ind].free_zang[zang_code] = FULL;
    return;
}

void fill_a_zang(string day_name, int zang_code, vector<Course> &course_list, vector<Teacher> &teacher_list, map<string, vector<char>> &the_class, int class_index)
{
    int day1_ind, day2_ind;
    vector<string> failed_course;
    Course *prop_course ;
    Teacher *prop_teacher;
    while (true)
    {
        prop_course = find_Course_for_zang(day_name, zang_code, course_list, the_class, class_index, failed_course);
        if (prop_course == NULL)
        {
            the_class[day_name][zang_code] = NOTFOUND;
            return;
        }
        prop_teacher = find_teacher_for_course(prop_course->name, prop_course->day1, prop_course->day2, zang_code, teacher_list, day1_ind, day2_ind);
        if (prop_teacher == NULL)
        {
            failed_course.push_back(prop_course->name);
            continue;
        }
        break;
    }
    set_course(prop_course, prop_teacher, class_index, day1_ind, day2_ind, zang_code);
    the_class[prop_course->day1][zang_code] = FULL;
    the_class[prop_course->day2][zang_code] = FULL;
}

void fill_all_days(vector<Course> &course_list, vector<Teacher> &teacher_list)
{
    vector<map<string, vector<char>>> school_schadule;
    map<string, vector<char>> class1{{"Saturday", {EMPTY, EMPTY, EMPTY}},
                                          {"Sunday", {EMPTY, EMPTY, EMPTY}},
                                          {"Monday", {EMPTY, EMPTY, EMPTY}},
                                         {"Tuesday", {EMPTY, EMPTY, EMPTY}},
                                         {"Wednesday", {EMPTY, EMPTY, EMPTY}}};
    map<string, vector<char>> class2{{"Saturday", {EMPTY, EMPTY, EMPTY}},
                                          {"Sunday", {EMPTY, EMPTY, EMPTY}},
                                          {"Monday", {EMPTY, EMPTY, EMPTY}},
                                         {"Tuesday", {EMPTY, EMPTY, EMPTY}},
                                         {"Wednesday", {EMPTY, EMPTY, EMPTY}}};
    school_schadule.push_back(class1);
    school_schadule.push_back(class2);
    for(int i=0;i<school_schadule.size();i++)
    {
        for(int j=0;j<week.size();j++)
        {
            for(int k=0;k<school_time.size();k++)
            {
                    fill_a_zang(week[j],k,course_list,teacher_list,school_schadule[i],i);
            }
        }
    }
}

void out_put(vector<Course> &course_list)
{
    for (int i = 0; i < course_list.size(); i++)
    {
        cout << course_list[i].name << endl;
        for (int k = 0; k < NUM_OF_CLASS; k++)
        {
            if (course_list[i].course_state[k].zang_class != NOT_FOUND)
            {
                cout << course_list[i].course_state[k].teacher_name << ": "<< zangs[course_list[i].course_state[k].zang_class] << endl;
            }
            else
            {
                cout << "Not Found" << endl;
            }
        }
    }
}

int main()
{
    // بردار ها را تعریف میکنیم.
    vector<Teacher> teacher_list;
    vector<Course> course_list;
    //معلم ها و روز ها را ورودی میگیریم.
    prepare_input_data(course_list,teacher_list);
    //برنامه را میچینیم.
    fill_all_days(course_list,teacher_list);
    //خروجی ها را چاپ میکنیم.
    out_put(course_list);
    return 0;
}