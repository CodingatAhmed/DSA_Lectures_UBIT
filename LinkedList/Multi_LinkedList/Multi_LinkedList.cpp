#include <iostream>
#include <cstdlib>
#include <cstdint>
using namespace std;

struct SNode
{
    int SeatNo;
    SNode *NextStudent;
};

struct CNode
{
    int CourseNo;
    CNode *NextCourse;
    SNode *Student_List;
};

CNode *CourseList = NULL;

void AddACourse(int enterCourseNo)
{
    CNode *NewCourse = (CNode *)malloc(sizeof(CNode));
    NewCourse->CourseNo = enterCourseNo;
    NewCourse->Student_List = NULL;
    NewCourse->NextCourse = NULL;
    if (CourseList == NULL)
    {
        CourseList = NewCourse;
    }
    else
    {
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse->NextCourse != NULL)
        {
            CurrentCourse = CurrentCourse->NextCourse;
        }
        CurrentCourse->NextCourse = NewCourse;
    }
}

void AddStudentToCourse(int Cno, int Seatno)
{
    SNode *NewStudent = (SNode *)malloc(sizeof(SNode));
    NewStudent->SeatNo = Seatno;
    NewStudent->NextStudent = NULL;
    if (CourseList == NULL)
    {
        CNode *NewCourse = (CNode *)malloc(sizeof(CNode));
        NewCourse->CourseNo = Cno;
        NewCourse->Student_List = NULL;
        NewCourse->NextCourse = NULL;
        NewCourse->Student_List = NewStudent;
    }
    else
    {
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse->NextCourse != NULL && CurrentCourse->CourseNo != Cno)
        {
            CurrentCourse = CurrentCourse->NextCourse;
        }
        if (CurrentCourse->CourseNo == Cno)
        {
            if (CurrentCourse->Student_List == NULL)
            {
                CurrentCourse->Student_List = NewStudent;
            }
            else
            {
                SNode *CurrentStudent = CurrentCourse->Student_List;
                while (CurrentStudent->NextStudent != NULL)
                {
                    CurrentStudent = CurrentStudent->NextStudent;
                }
                CurrentStudent->NextStudent = NewStudent;
            }
            cout << "Student Added into Course" << Cno << "Successfully" << endl;
        }
        else
        {
            cout << "Course not found" << endl;
        }
    }
}
void DisplayAll()
{
    CNode *CurrentCourse = CourseList;
    if (CurrentCourse == NULL)
    {
        cout << "No Courses Registered" << endl;
    }
    else
    {
        while (CurrentCourse != NULL)
        {
            cout << "Course No:" << CurrentCourse->CourseNo << endl;
            SNode *CurrentStudent = CurrentCourse->Student_List;
            if (CurrentStudent == NULL)
            {
                cout << "No Student Enrolled in Course No: " << CurrentCourse->CourseNo << endl;
            }
            else
            {
                while (CurrentStudent != NULL)
                {
                    cout << "Student Seat No" << CurrentStudent->SeatNo << endl;
                    CurrentStudent = CurrentStudent->NextStudent;
                }
            }
            CurrentCourse = CurrentCourse->NextCourse;
        }
    }
}

int main()
{
    // AddACourse(404);
    // AddStudentToCourse(404, 55);
    // AddStudentToCourse(404, 56);
    // AddStudentToCourse(404, 57);
    // AddACourse(405);
    // AddStudentToCourse(405, 55);
    // AddStudentToCourse(405, 56);
    // AddStudentToCourse(405, 57);
    DisplayAll();
    return 0;
}