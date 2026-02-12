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

void DeleteACourse(int CourseN)
{
    CNode *CurrentCourse = CourseList;
    if (CurrentCourse == NULL)
    {
        cout << "No Courses Found" << endl;
    }
    else
    {
        while (CurrentCourse->NextCourse->CourseNo != CourseN && CurrentCourse != NULL)
        {
            CurrentCourse = CurrentCourse->NextCourse;
        }
        if (CurrentCourse == NULL)
        {
            cout << "Course No: " << CourseN << "Not Found" << endl;
        }
        else
        {
            if (CurrentCourse->NextCourse->NextCourse == NULL)
            {
                CurrentCourse->NextCourse = NULL;
            }
            else
            {
                CurrentCourse->NextCourse = CurrentCourse->NextCourse->NextCourse;
            }
        }
    }
}

void SearchACourse(int Courseno)
{

    if (CourseList == NULL)
    {
        cout << "No Courses Registered to be Searched" << endl;
    }
    else
    {

        CNode *CurrentCourse = CourseList;
        int Position = 1;
        while (CurrentCourse != NULL && CurrentCourse->CourseNo != Courseno)
        {
            CurrentCourse = CurrentCourse->NextCourse;
            Position += 1;
        }
        if (CurrentCourse->CourseNo == Courseno)
        {
            cout << "Course No: " << Courseno << "found at " << Position << endl;
        }
        else
        {
            cout << "Course No: " << Courseno << "Not Registered" << endl;
        }
    }
    // return CurrentCourse;
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
        NewCourse->NextCourse = NULL;
        NewCourse->Student_List = NewStudent;
        CourseList = NewCourse;
    }
    else
    {
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse != NULL && CurrentCourse->CourseNo != Cno)
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

void DisplayCourseList()
{
    if (CourseList == NULL)
    {
        cout << "No Courses Registered" << endl;
    }
    else
    {
        CNode *CurrentCourse = CourseList;
        cout << "List of All Courses Registered" << endl;
        while (CurrentCourse->NextCourse != NULL)
        {
            cout << CurrentCourse->CourseNo << endl;
            CurrentCourse = CurrentCourse->NextCourse;
        }
    }
}

void DeleteAStudent(int StudentN)
{
    if (CourseList == NULL)
    {
        cout << "No Courses Registered" << endl;
    }
    else
    {
        bool StudentFound = false;
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse != NULL)
        {
            CurrentCourse = CurrentCourse->NextCourse;
            SNode *CurrentStudent = CurrentCourse->Student_List;
            while (CurrentStudent->NextStudent->SeatNo != StudentN && CurrentStudent->NextStudent != NULL)
            {
                CurrentStudent = CurrentStudent->NextStudent;
            }
            if (CurrentStudent->NextStudent->SeatNo == StudentN)
            {
                StudentFound = true;
                if (CurrentStudent->NextStudent->NextStudent == NULL)
                {
                    CurrentStudent->NextStudent = NULL;
                }
                else
                {
                    CurrentStudent->NextStudent = CurrentStudent->NextStudent->NextStudent;
                }
                cout << "Student with Seat No: " << StudentN << "found in Course No:" << CurrentCourse->CourseNo << "is Removed from the list Successfully" << endl;
            }
        }
        if (StudentFound == false)
        {
            cout << "Student with Seat No: " << StudentN << "Not Found" << endl;
        }
    }
}

void DeleteAStudentFromACourse(int CourseN, int StudentN)
{
    if (CourseList == NULL)
    {
        cout << "No Courses Registered" << endl;
    }
    else
    {
        bool StudentFound = false;
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse != NULL && CurrentCourse->CourseNo != CourseN)
        {
            CurrentCourse = CurrentCourse->NextCourse;
        }
        if (CurrentCourse == NULL)
        {
            cout << "Course No: " << CourseN << "Not Found" << endl;
        }
        else
        {
            SNode *CurrentStudent = CurrentCourse->Student_List;
            if (CurrentStudent->SeatNo == StudentN)
            {
                CurrentCourse->Student_List = CurrentStudent->NextStudent;
                StudentFound = true;
            }
            else
            {
                while (CurrentStudent->NextStudent->SeatNo != StudentN && CurrentStudent->NextStudent != NULL)
                {
                    CurrentStudent = CurrentStudent->NextStudent;
                }
                if (CurrentStudent->NextStudent->SeatNo == StudentN)
                {
                    StudentFound = true;
                    if (CurrentStudent->NextStudent->NextStudent == NULL)
                    {
                        CurrentStudent->NextStudent = NULL;
                    }
                    else
                    {
                        CurrentStudent->NextStudent = CurrentStudent->NextStudent->NextStudent;
                    }
                }
            }
            cout << "Student with Seat No: " << StudentN << "Found and is Removed from the Course with Course No:" << CurrentCourse->CourseNo << endl;
        }
        if (StudentFound == false)
        {
            cout << "Student with Seat No: " << StudentN << " Not Found" << endl;
        }
    }
}

void SearchAStudent(int StudentN)
{
    if (CourseList == NULL)
    {
        cout << "No Courses Registered" << endl;
    }
    else
    {
        bool StudentFound = false;
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse != NULL)
        {
            CurrentCourse = CurrentCourse->NextCourse;
            SNode *CurrentStudent = CurrentCourse->Student_List;
            while (CurrentStudent->SeatNo != StudentN && CurrentStudent != NULL)
            {
                CurrentStudent = CurrentStudent->NextStudent;
            }
            if (CurrentStudent->SeatNo == StudentN)
            {
                StudentFound = true;
                cout << "Student with Seat No: " << StudentN << " found" << endl;
            }
        }
        if (StudentFound == false)
        {
            cout << "Student with Seat No: " << StudentN << " Not Found" << endl;
        }
    }
}
void SearchAStudentFromACourse(int CourseN, int StudentN)
{
    if (CourseList == NULL)
    {
        cout << "No Courses Registered" << endl;
    }
    else
    {
        bool StudentFound = false;
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse != NULL && CurrentCourse->CourseNo != CourseN)
        {
            CurrentCourse = CurrentCourse->NextCourse;
        }
        if (CurrentCourse == NULL)
        {
            cout << "Course No: " << CourseN << "Not Found" << endl;
        }
        else
        {
            SNode *CurrentStudent = CurrentCourse->Student_List;
            while (CurrentStudent->SeatNo != StudentN && CurrentStudent != NULL)
            {
                CurrentStudent = CurrentStudent->NextStudent;
            }
            if (CurrentStudent->SeatNo == StudentN)
            {
                StudentFound = true;
                cout << "Student with Seat No: " << StudentN << "Found from the Course with Course No:" << CurrentCourse->CourseNo << endl;
            }
        }
        if (StudentFound == false)
        {
            cout << "Student with Seat No: " << StudentN << " Not Found" << endl;
        }
    }
}

void DisplayStudentListfromCourse(int CourseN)
{
    if (CourseList == NULL)
    {
        cout << "No Courses Found" << endl;
    }
    else
    {
        CNode *CurrentCourse = CourseList;
        while (CurrentCourse->CourseNo != CourseN && CurrentCourse != NULL)
        {
            CurrentCourse = CurrentCourse->NextCourse;
        }
        if (CurrentCourse == NULL)
        {
            cout << "Course No: " << CourseN << " Not Found" << endl;
        }
        else
        {
            SNode *CurrentStudent = CurrentCourse->Student_List;
            if (CurrentStudent == NULL)
            {
                cout << "No Student Enrolled in Course No: " << CourseN << endl;
            }
            else
            {
                cout << "All Students List of Course No: " << CourseN << endl;
                while (CurrentStudent != NULL)
                {
                    cout << "Student Seat No: " << CurrentStudent->SeatNo << endl;
                    CurrentStudent = CurrentStudent->NextStudent;
                }
            }
        }
    }
}

void DisplayAll()
{
    CNode *CurrentCourse = CourseList;
    if (CurrentCourse == NULL)
    {
        cout << "No Courses or Students to Display" << endl;
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
                    cout << "Student Seat No: " << CurrentStudent->SeatNo << endl;
                    CurrentStudent = CurrentStudent->NextStudent;
                }
            }
            CurrentCourse = CurrentCourse->NextCourse;
        }
    }
}

int main()
{
    AddACourse(404);
    AddStudentToCourse(404, 55);
    AddStudentToCourse(404, 56);
    AddStudentToCourse(404, 57);
    AddACourse(405);
    AddStudentToCourse(405, 55);
    AddStudentToCourse(405, 56);
    AddStudentToCourse(405, 57);
    DeleteACourse(405);
    // DeleteAStudentFromACourse(405, 55);
    // DisplayStudentListfromCourse(405);
    DisplayAll();
    return 0;
}