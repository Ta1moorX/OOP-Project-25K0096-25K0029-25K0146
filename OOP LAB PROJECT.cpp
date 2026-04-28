#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

const int MAX_COMMENTS      = 20;
const int MAX_POSTS         = 50;
const int MAX_ASSIGNMENTS   = 30;
const int MAX_QUIZZES       = 20;
const int MAX_QUESTIONS     = 20;
const int MAX_SUBMISSIONS   = 50;
const int MAX_RECORDINGS    = 20;
const int MAX_MEETINGS      = 20;
const int MAX_SCORES        = 30;
const int MAX_ENROLLED      = 10;
const int MAX_MANAGED       = 10;
const int MAX_STUDENTS_CLS  = 50;
const int MAX_STUDENTS_PLT  = 100;
const int MAX_TEACHERS_PLT  = 20;
const int MAX_CLASSROOMS    = 20;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLine(char c = '-', int len = 60) {
    cout << string(len, c) << "\n";
}

void printHeader(const string& title) {
    printLine('=');
    cout << "  " << title << "\n";
    printLine('=');
}

string currentTime() {
    time_t now = time(0);
    string t = ctime(&now);
    t.pop_back();
    return t;
}

class Post {
public:
    string author;
    string content;
    string timestamp;
    string comments[MAX_COMMENTS];
    int    commentCount;

    Post() : commentCount(0) {}

    Post(const string& a, const string& c)
        : author(a), content(c), timestamp(currentTime()), commentCount(0) {}

    void addComment(const string& commenter, const string& comment) {
        if (commentCount < MAX_COMMENTS)
            comments[commentCount++] = commenter + ": " + comment;
        else
            cout << "  Comment limit reached.\n";
    }

    void display() const {
        printLine();
        cout << "  [" << timestamp << "]\n";
        cout << "  " << author << " posted:\n";
        cout << "  " << content << "\n";
        if (commentCount > 0) {
            cout << "  Comments:\n";
            for (int i = 0; i < commentCount; i++)
                cout << "    > " << comments[i] << "\n";
        }
    }
};

class Assignment {
public:
    string title;
    string description;
    string dueDate;
    int    totalMarks;
    bool   isOpen;

    Assignment() : totalMarks(0), isOpen(false) {}

    Assignment(const string& t, const string& d,
               const string& due, int marks)
        : title(t), description(d), dueDate(due),
          totalMarks(marks), isOpen(true) {}

    void display() const {
        cout << "  [ASSIGNMENT] " << title << "\n";
        cout << "    " << description << "\n";
        cout << "    Due: " << dueDate
             << "  |  Marks: " << totalMarks
             << "  |  Status: " << (isOpen ? "OPEN" : "CLOSED") << "\n";
    }
};

class Quiz {
public:
    string title;
    string deadline;
    int    totalMarks;
    string questions[MAX_QUESTIONS];
    int    questionCount;
    bool   isOpen;

    Quiz() : totalMarks(0), questionCount(0), isOpen(false) {}

    Quiz(const string& t, const string& dl, int marks)
        : title(t), deadline(dl), totalMarks(marks),
          questionCount(0), isOpen(true) {}

    void addQuestion(const string& q) {
        if (questionCount < MAX_QUESTIONS)
            questions[questionCount++] = q;
        else
            cout << "  Question limit reached.\n";
    }

    void display() const {
        cout << "  [QUIZ] " << title << "\n";
        cout << "    Deadline: " << deadline
             << "  |  Marks: " << totalMarks
             << "  |  Questions: " << questionCount
             << "  |  Status: " << (isOpen ? "OPEN" : "CLOSED") << "\n";
    }
};

class Recording {
public:
    string title;
    string uploadedBy;
    string url;
    string duration;
    string uploadDate;

    Recording() {}

    Recording(const string& t, const string& uploader,
              const string& u, const string& dur)
        : title(t), uploadedBy(uploader), url(u),
          duration(dur), uploadDate(currentTime()) {}

    void display() const {
        cout << "  [REC] " << title << "\n";
        cout << "    Uploaded by: " << uploadedBy
             << "  |  Duration: " << duration << "\n";
        cout << "    Link: " << url << "\n";
    }
};

class Meeting {
public:
    string title;
    string link;
    string scheduledTime;
    bool   isLive;

    Meeting() : isLive(false) {}

    Meeting(const string& t, const string& l, const string& sched)
        : title(t), link(l), scheduledTime(sched), isLive(false) {}

    void goLive()  { isLive = true;  }
    void endMeet() { isLive = false; }

    void display() const {
        cout << "  [MEETING] " << title << "\n";
        cout << "    Scheduled: " << scheduledTime
             << "  |  Status: "
             << (isLive ? "** LIVE NOW **" : "Upcoming") << "\n";
        cout << "    Join Link: " << link << "\n";
    }
};

class Submission {
public:
    string studentName;
    string assignmentTitle;
    string fileOrContent;
    string submittedAt;
    int    marksObtained;
    bool   isGraded;

    Submission() : marksObtained(0), isGraded(false) {}

    Submission(const string& sn, const string& at, const string& content)
        : studentName(sn), assignmentTitle(at),
          fileOrContent(content), submittedAt(currentTime()),
          marksObtained(0), isGraded(false) {}

    void grade(int marks) {
        marksObtained = marks;
        isGraded = true;
    }

    void display() const {
        cout << "    Student: " << studentName
             << "  |  Submitted: " << submittedAt << "\n";
        cout << "    Content: " << fileOrContent << "\n";
        if (isGraded)
            cout << "    Marks: " << marksObtained << "\n";
        else
            cout << "    Marks: Not graded yet\n";
    }
};

struct ScoreEntry {
    string title;
    int    marks;
};

class GradeTracker {
public:
    string     studentId;
    ScoreEntry scores[MAX_SCORES];
    int        scoreCount;

    GradeTracker() : scoreCount(0) {}

    GradeTracker(const string& id) : studentId(id), scoreCount(0) {}

    void addScore(const string& title, int marks) {
        if (scoreCount < MAX_SCORES) {
            scores[scoreCount].title = title;
            scores[scoreCount].marks = marks;
            scoreCount++;
        } else {
            cout << "  Score limit reached.\n";
        }
    }

    void display() const {
        cout << "  Grade report for: " << studentId << "\n";
        int total = 0;
        for (int i = 0; i < scoreCount; i++) {
            cout << "    " << left << setw(30)
                 << scores[i].title << scores[i].marks << "\n";
            total += scores[i].marks;
        }
        printLine();
        cout << "  Total marks: " << total << "\n";
    }
};

class Stream {
    Post posts[MAX_POSTS];
    int  postCount_;
public:
    Stream() : postCount_(0) {}

    void addPost(const string& author, const string& content) {
        if (postCount_ < MAX_POSTS) {
            posts[postCount_++] = Post(author, content);
            cout << "  Post added to stream.\n";
        } else {
            cout << "  Stream is full.\n";
        }
    }

    void commentOnPost(int idx, const string& commenter,
                       const string& comment) {
        if (idx >= 0 && idx < postCount_)
            posts[idx].addComment(commenter, comment);
    }

    void display() const {
        if (postCount_ == 0) {
            cout << "  Stream is empty.\n";
            return;
        }
        cout << "  " << postCount_ << " post(s) in stream:\n";
        for (int i = 0; i < postCount_; i++)
            posts[i].display();
    }

    int postCount() const { return postCount_; }
};

class Classwork {
    Assignment assignments[MAX_ASSIGNMENTS];
    int        assignmentCount_;

    Quiz       quizzes[MAX_QUIZZES];
    int        quizCount_;

    Submission submissions[MAX_SUBMISSIONS];
    int        submissionCount_;

public:
    Classwork()
        : assignmentCount_(0), quizCount_(0), submissionCount_(0) {}

    void addAssignment(const string& t, const string& d,
                       const string& due, int marks) {
        if (assignmentCount_ < MAX_ASSIGNMENTS) {
            assignments[assignmentCount_++] = Assignment(t, d, due, marks);
            cout << "  Assignment \"" << t << "\" added.\n";
        } else {
            cout << "  Assignment limit reached.\n";
        }
    }

    void addQuiz(const string& t, const string& dl, int marks) {
        if (quizCount_ < MAX_QUIZZES) {
            quizzes[quizCount_++] = Quiz(t, dl, marks);
            cout << "  Quiz \"" << t << "\" added.\n";
        } else {
            cout << "  Quiz limit reached.\n";
        }
    }

    void addQuestionToQuiz(int idx, const string& q) {
        if (idx >= 0 && idx < quizCount_)
            quizzes[idx].addQuestion(q);
    }

    void submitAssignment(const string& student,
                          const string& title,
                          const string& content) {
        if (submissionCount_ < MAX_SUBMISSIONS) {
            submissions[submissionCount_++] =
                Submission(student, title, content);
            cout << "  Submission recorded for \"" << title << "\".\n";
        } else {
            cout << "  Submission limit reached.\n";
        }
    }

    void gradeSubmission(int idx, int marks) {
        if (idx >= 0 && idx < submissionCount_) {
            submissions[idx].grade(marks);
            cout << "  Graded.\n";
        }
    }

    void displayAssignments() const {
        if (assignmentCount_ == 0) {
            cout << "  No assignments yet.\n"; return;
        }
        for (int i = 0; i < assignmentCount_; i++)
            assignments[i].display();
    }

    void displayQuizzes() const {
        if (quizCount_ == 0) {
            cout << "  No quizzes yet.\n"; return;
        }
        for (int i = 0; i < quizCount_; i++)
            quizzes[i].display();
    }

    void displaySubmissions() const {
        if (submissionCount_ == 0) {
            cout << "  No submissions yet.\n"; return;
        }
        cout << "  Submissions (" << submissionCount_ << "):\n";
        for (int i = 0; i < submissionCount_; i++) {
            cout << "  [" << i << "]\n";
            submissions[i].display();
        }
    }

    int assignmentCount() const { return assignmentCount_; }
    int quizCount()       const { return quizCount_; }
};

class OnlineClass {
    Recording recordings[MAX_RECORDINGS];
    int       recordingCount_;

    Meeting   meetings[MAX_MEETINGS];
    int       meetingCount_;

public:
    OnlineClass() : recordingCount_(0), meetingCount_(0) {}

    void uploadRecording(const string& title, const string& uploader,
                         const string& url,   const string& duration) {
        if (recordingCount_ < MAX_RECORDINGS) {
            recordings[recordingCount_++] =
                Recording(title, uploader, url, duration);
            cout << "  Recording \"" << title << "\" uploaded.\n";
        } else {
            cout << "  Recording limit reached.\n";
        }
    }

    void scheduleMeeting(const string& title, const string& link,
                         const string& sched) {
        if (meetingCount_ < MAX_MEETINGS) {
            meetings[meetingCount_++] = Meeting(title, link, sched);
            cout << "  Meeting \"" << title << "\" scheduled.\n";
        } else {
            cout << "  Meeting limit reached.\n";
        }
    }

    void startMeeting(int idx) {
        if (idx >= 0 && idx < meetingCount_) {
            meetings[idx].goLive();
            cout << "  Meeting is now LIVE!\n";
        }
    }

    void endMeeting(int idx) {
        if (idx >= 0 && idx < meetingCount_) {
            meetings[idx].endMeet();
            cout << "  Meeting ended.\n";
        }
    }

    void displayRecordings() const {
        if (recordingCount_ == 0) {
            cout << "  No recordings yet.\n"; return;
        }
        cout << "  Recordings (" << recordingCount_ << "):\n";
        for (int i = 0; i < recordingCount_; i++)
            recordings[i].display();
    }

    void displayMeetings() const {
        if (meetingCount_ == 0) {
            cout << "  No meetings scheduled.\n"; return;
        }
        cout << "  Meetings (" << meetingCount_ << "):\n";
        for (int i = 0; i < meetingCount_; i++)
            meetings[i].display();
    }

    int liveCount() const {
        int c = 0;
        for (int i = 0; i < meetingCount_; i++)
            if (meetings[i].isLive) c++;
        return c;
    }
};

class User {
protected:
    string name;
    string id;
    string email;
    string password;
public:
    User() {}

    User(const string& n, const string& i,
         const string& e, const string& p)
        : name(n), id(i), email(e), password(p) {}

    virtual ~User() {}

    string getName()  const { return name; }
    string getId()    const { return id; }
    string getEmail() const { return email; }

    bool checkPassword(const string& p) const { return password == p; }

    virtual void displayProfile() const {
        cout << "  Name : " << name  << "\n";
        cout << "  ID   : " << id    << "\n";
        cout << "  Email: " << email << "\n";
    }

    virtual string getRole() const { return "User"; }
};

class Student : public User {
    string       enrolledClassCodes[MAX_ENROLLED];
    GradeTracker gradeTrackers[MAX_ENROLLED];
    int          enrolledCount;

public:
    Student() : enrolledCount(0) {}

    Student(const string& n, const string& i,
            const string& e, const string& p)
        : User(n, i, e, p), enrolledCount(0) {}

    void enrollInClass(const string& code) {
        if (enrolledCount < MAX_ENROLLED) {
            enrolledClassCodes[enrolledCount] = code;
            gradeTrackers[enrolledCount]      = GradeTracker(id);
            enrolledCount++;
            cout << "  " << name << " enrolled in class " << code << ".\n";
        } else {
            cout << "  Enrollment limit reached.\n";
        }
    }

    void addGrade(const string& classCode,
                  const string& title, int marks) {
        for (int i = 0; i < enrolledCount; i++) {
            if (enrolledClassCodes[i] == classCode) {
                gradeTrackers[i].addScore(title, marks);
                return;
            }
        }
        cout << "  Not enrolled in that class.\n";
    }

    void viewGrades() const {
        if (enrolledCount == 0) {
            cout << "  No grades yet.\n"; return;
        }
        for (int i = 0; i < enrolledCount; i++) {
            cout << "  Class: " << enrolledClassCodes[i] << "\n";
            gradeTrackers[i].display();
        }
    }

    void displayProfile() const override {
        User::displayProfile();
        cout << "  Role: Student\n";
        cout << "  Enrolled in " << enrolledCount << " class(es)\n";
    }

    string getRole() const override { return "Student"; }

    int    getEnrolledCount() const { return enrolledCount; }
    string getEnrolledCode(int i) const { return enrolledClassCodes[i]; }
};

class Teacher : public User {
protected:
    string subjectSpeciality;
    string managedClassCodes[MAX_MANAGED];
    int    managedCount;

public:
    Teacher() : managedCount(0) {}

    Teacher(const string& n, const string& i,
            const string& e, const string& p,
            const string& subj)
        : User(n, i, e, p), subjectSpeciality(subj), managedCount(0) {}

    void addManagedClass(const string& code) {
        if (managedCount < MAX_MANAGED)
            managedClassCodes[managedCount++] = code;
    }

    void displayProfile() const override {
        User::displayProfile();
        cout << "  Role   : Teacher\n";
        cout << "  Subject: " << subjectSpeciality << "\n";
        cout << "  Managing " << managedCount << " class(es)\n";
    }

    string getRole()    const override { return "Teacher"; }
    string getSubject() const          { return subjectSpeciality; }

    virtual void conductSpecialActivity() {
        cout << "  Conducting a general class activity.\n";
    }
};

class MathTeacher : public Teacher {
public:
    MathTeacher() {}
    MathTeacher(const string& n, const string& i,
                const string& e, const string& p)
        : Teacher(n, i, e, p, "Mathematics") {}

    void conductSpecialActivity() override {
        cout << "  [Math] Conducting a problem-solving quiz session.\n";
    }

    void uploadFormulaSheet(Stream& stream) {
        stream.addPost(name,
            "[Formula Sheet] Quadratic, Trigonometry & Calculus reference uploaded.");
    }
};

class ScienceTeacher : public Teacher {
public:
    ScienceTeacher() {}
    ScienceTeacher(const string& n, const string& i,
                   const string& e, const string& p)
        : Teacher(n, i, e, p, "Science") {}

    void conductSpecialActivity() override {
        cout << "  [Science] Assigning a virtual lab report.\n";
    }

    void uploadLabInstructions(Stream& stream) {
        stream.addPost(name,
            "[Lab] Instructions for Lab #3 - Osmosis experiment uploaded.");
    }
};

class EnglishTeacher : public Teacher {
public:
    EnglishTeacher() {}
    EnglishTeacher(const string& n, const string& i,
                   const string& e, const string& p)
        : Teacher(n, i, e, p, "English Literature") {}

    void conductSpecialActivity() override {
        cout << "  [English] Hosting a poetry discussion session.\n";
    }
};

class CSTeacher : public Teacher {
public:
    CSTeacher() {}
    CSTeacher(const string& n, const string& i,
              const string& e, const string& p)
        : Teacher(n, i, e, p, "Computer Science") {}

    void conductSpecialActivity() override {
        cout << "  [CS] Running a live coding exercise.\n";
    }
};

class Classroom {
    string   classCode;
    string   className;
    Teacher* teacher;
    Stream      stream;
    Classwork   classwork;
    OnlineClass onlineClass;
    Student* students[MAX_STUDENTS_CLS];
    int      studentCount;

public:
    Classroom() : teacher(nullptr), studentCount(0) {}

    Classroom(const string& code, const string& name, Teacher* t)
        : classCode(code), className(name),
          teacher(t), studentCount(0) {
        teacher->addManagedClass(code);
    }

    string getCode() const { return classCode; }
    string getName() const { return className; }

    void enrollStudent(Student* s) {
        if (studentCount < MAX_STUDENTS_CLS) {
            students[studentCount++] = s;
            s->enrollInClass(classCode);
        } else {
            cout << "  Classroom is full.\n";
        }
    }


    void teacherPost(const string& content) {
        stream.addPost(teacher->getName(), content);
    }
    void studentPost(Student* s, const string& content) {
        stream.addPost(s->getName(), content);
    }
    void viewStream() { stream.display(); }


    void addAssignment(const string& t, const string& d,
                       const string& due, int marks) {
        classwork.addAssignment(t, d, due, marks);
    }
    void addQuiz(const string& t, const string& dl, int marks) {
        classwork.addQuiz(t, dl, marks);
    }
    void submitAssignment(const string& student,
                          const string& title,
                          const string& content) {
        classwork.submitAssignment(student, title, content);
    }
    void viewAssignments() { classwork.displayAssignments(); }
    void viewQuizzes()     { classwork.displayQuizzes(); }
    void viewSubmissions() { classwork.displaySubmissions(); }
    void gradeSubmission(int idx, int marks) {
        classwork.gradeSubmission(idx, marks);
    }


    void uploadRecording(const string& title, const string& url,
                         const string& dur) {
        onlineClass.uploadRecording(title, teacher->getName(), url, dur);
    }
    void scheduleMeeting(const string& title, const string& link,
                         const string& sched) {
        onlineClass.scheduleMeeting(title, link, sched);
    }
    void startMeeting(int idx)  { onlineClass.startMeeting(idx); }
    void endMeeting(int idx)    { onlineClass.endMeeting(idx); }
    void viewRecordings()       { onlineClass.displayRecordings(); }
    void viewMeetings()         { onlineClass.displayMeetings(); }


    void displayDashboard() const {
        printHeader("CLASS: " + className + "  [" + classCode + "]");
        cout << "  Teacher : " << teacher->getName()
             << " (" << teacher->getSubject() << ")\n";
        cout << "  Students: " << studentCount << "\n";
        cout << "  Stream  : " << stream.postCount() << " posts\n";
        cout << "  Work    : " << classwork.assignmentCount()
             << " assignment(s),  " << classwork.quizCount() << " quiz(zes)\n";
        cout << "  Live now: " << onlineClass.liveCount() << " meeting(s)\n";
        printLine();
    }

    // People
    void displayPeople() const {
        cout << "  Teacher: " << teacher->getName() << "\n\n";
        cout << "  Students (" << studentCount << "):\n";
        for (int i = 0; i < studentCount; i++)
            cout << "    * " << students[i]->getName()
                 << "  [" << students[i]->getId() << "]\n";
    }
};

class Platform {
    Classroom* classrooms[MAX_CLASSROOMS];
    int        classroomCount;

    Student*   students[MAX_STUDENTS_PLT];
    int        studentCount;

    Teacher*   teachers[MAX_TEACHERS_PLT];
    int        teacherCount;

public:
    Platform()
        : classroomCount(0), studentCount(0), teacherCount(0) {}

    ~Platform() {
        for (int i = 0; i < classroomCount; i++) delete classrooms[i];
        for (int i = 0; i < studentCount;   i++) delete students[i];
        for (int i = 0; i < teacherCount;   i++) delete teachers[i];
    }

    void addStudent(Student* s) {
        if (studentCount < MAX_STUDENTS_PLT)
            students[studentCount++] = s;
    }
    void addTeacher(Teacher* t) {
        if (teacherCount < MAX_TEACHERS_PLT)
            teachers[teacherCount++] = t;
    }
    void addClassroom(Classroom* c) {
        if (classroomCount < MAX_CLASSROOMS)
            classrooms[classroomCount++] = c;
    }

    Student* findStudent(const string& id) {
        for (int i = 0; i < studentCount; i++)
            if (students[i]->getId() == id) return students[i];
        return nullptr;
    }

    Teacher* findTeacher(const string& id) {
        for (int i = 0; i < teacherCount; i++)
            if (teachers[i]->getId() == id) return teachers[i];
        return nullptr;
    }

    Classroom* findClassroom(const string& code) {
        for (int i = 0; i < classroomCount; i++)
            if (classrooms[i]->getCode() == code) return classrooms[i];
        return nullptr;
    }

    User* login(const string& id, const string& pass) {
        for (int i = 0; i < studentCount; i++)
            if (students[i]->getId() == id &&
                students[i]->checkPassword(pass))
                return students[i];
        for (int i = 0; i < teacherCount; i++)
            if (teachers[i]->getId() == id &&
                teachers[i]->checkPassword(pass))
                return teachers[i];
        return nullptr;
    }

    void listClassrooms() const {
        cout << "  Available classrooms:\n";
        for (int i = 0; i < classroomCount; i++)
            cout << "    [" << classrooms[i]->getCode()
                 << "] " << classrooms[i]->getName() << "\n";
    }
};


void teacherMenu(Teacher* t, Platform& platform) {
    int choice;
    do {
        printHeader("TEACHER MENU — " + t->getName());
        cout << "  1. View / enter a classroom\n";
        cout << "  2. My profile\n";
        cout << "  0. Logout\n";
        printLine();
        cout << "  Choice: "; cin >> choice; cin.ignore();

        if (choice == 1) {
            platform.listClassrooms();
            cout << "  Enter class code: ";
            string code; getline(cin, code);
            Classroom* cls = platform.findClassroom(code);
            if (!cls) { cout << "  Class not found.\n"; continue; }

            int c2;
            do {
                cls->displayDashboard();
                cout << "  1. Stream\n";
                cout << "  2. Classwork\n";
                cout << "  3. Online Class\n";
                cout << "  4. People\n";
                cout << "  0. Back\n";
                cout << "  Choice: "; cin >> c2; cin.ignore();

                if (c2 == 1) {
                    int c3;
                    do {
                        printHeader("STREAM");
                        cls->viewStream();
                        cout << "\n  1. Post announcement\n";
                        cout << "  0. Back\n";
                        cout << "  Choice: "; cin >> c3; cin.ignore();
                        if (c3 == 1) {
                            cout << "  Message: ";
                            string msg; getline(cin, msg);
                            cls->teacherPost(msg);
                        }
                    } while (c3 != 0);

                } else if (c2 == 2) {
                    int c3;
                    do {
                        printHeader("CLASSWORK");
                        cout << "  1. View assignments\n";
                        cout << "  2. Add assignment\n";
                        cout << "  3. View quizzes\n";
                        cout << "  4. Add quiz\n";
                        cout << "  5. View submissions\n";
                        cout << "  6. Grade a submission\n";
                        cout << "  0. Back\n";
                        cout << "  Choice: "; cin >> c3; cin.ignore();

                        if (c3 == 1) { cls->viewAssignments(); }
                        else if (c3 == 2) {
                            string title, desc, due;
                            int marks;
                            cout << "  Title: "; getline(cin, title);
                            cout << "  Desc : "; getline(cin, desc);
                            cout << "  Due  : "; getline(cin, due);
                            cout << "  Marks: "; cin >> marks; cin.ignore();
                            cls->addAssignment(title, desc, due, marks);
                        }
                        else if (c3 == 3) { cls->viewQuizzes(); }
                        else if (c3 == 4) {
                            string title, dl;
                            int marks;
                            cout << "  Title   : "; getline(cin, title);
                            cout << "  Deadline: "; getline(cin, dl);
                            cout << "  Marks   : "; cin >> marks; cin.ignore();
                            cls->addQuiz(title, dl, marks);
                        }
                        else if (c3 == 5) { cls->viewSubmissions(); }
                        else if (c3 == 6) {
                            cls->viewSubmissions();
                            int idx, marks;
                            cout << "  Submission index: "; cin >> idx; cin.ignore();
                            cout << "  Marks to give  : "; cin >> marks; cin.ignore();
                            cls->gradeSubmission(idx, marks);
                        }
                    } while (c3 != 0);

                } else if (c2 == 3) {
                    int c3;
                    do {
                        printHeader("ONLINE CLASS");
                        cout << "  1. View recordings\n";
                        cout << "  2. Upload recording\n";
                        cout << "  3. View meetings\n";
                        cout << "  4. Schedule meeting\n";
                        cout << "  5. Start meeting\n";
                        cout << "  6. End meeting\n";
                        cout << "  0. Back\n";
                        cout << "  Choice: "; cin >> c3; cin.ignore();

                        if (c3 == 1) { cls->viewRecordings(); }
                        else if (c3 == 2) {
                            string title, url, dur;
                            cout << "  Title   : "; getline(cin, title);
                            cout << "  URL/link: "; getline(cin, url);
                            cout << "  Duration: "; getline(cin, dur);
                            cls->uploadRecording(title, url, dur);
                        }
                        else if (c3 == 3) { cls->viewMeetings(); }
                        else if (c3 == 4) {
                            string title, link, sched;
                            cout << "  Title    : "; getline(cin, title);
                            cout << "  Link     : "; getline(cin, link);
                            cout << "  Scheduled: "; getline(cin, sched);
                            cls->scheduleMeeting(title, link, sched);
                        }
                        else if (c3 == 5) {
                            int idx;
                            cout << "  Meeting index: "; cin >> idx; cin.ignore();
                            cls->startMeeting(idx);
                        }
                        else if (c3 == 6) {
                            int idx;
                            cout << "  Meeting index: "; cin >> idx; cin.ignore();
                            cls->endMeeting(idx);
                        }
                    } while (c3 != 0);

                } else if (c2 == 4) {
                    printHeader("PEOPLE");
                    cls->displayPeople();
                }
            } while (c2 != 0);

        } else if (choice == 2) {
            printHeader("MY PROFILE");
            t->displayProfile();
            t->conductSpecialActivity();
        }
    } while (choice != 0);
}

void studentMenu(Student* s, Platform& platform) {
    int choice;
    do {
        printHeader("STUDENT MENU — " + s->getName());
        cout << "  1. View a classroom\n";
        cout << "  2. My grades\n";
        cout << "  3. My profile\n";
        cout << "  0. Logout\n";
        printLine();
        cout << "  Choice: "; cin >> choice; cin.ignore();

        if (choice == 1) {
            platform.listClassrooms();
            cout << "  Enter class code: ";
            string code; getline(cin, code);
            Classroom* cls = platform.findClassroom(code);
            if (!cls) { cout << "  Class not found.\n"; continue; }

            int c2;
            do {
                cls->displayDashboard();
                cout << "  1. Stream\n";
                cout << "  2. Classwork\n";
                cout << "  3. Online Class\n";
                cout << "  4. People\n";
                cout << "  0. Back\n";
                cout << "  Choice: "; cin >> c2; cin.ignore();

                if (c2 == 1) {
                    int c3;
                    do {
                        printHeader("STREAM");
                        cls->viewStream();
                        cout << "\n  1. Post a comment/question\n";
                        cout << "  0. Back\n";
                        cout << "  Choice: "; cin >> c3; cin.ignore();
                        if (c3 == 1) {
                            cout << "  Message: ";
                            string msg; getline(cin, msg);
                            cls->studentPost(s, msg);
                        }
                    } while (c3 != 0);

                } else if (c2 == 2) {
                    int c3;
                    do {
                        printHeader("CLASSWORK");
                        cout << "  1. View assignments\n";
                        cout << "  2. Submit assignment\n";
                        cout << "  3. View quizzes\n";
                        cout << "  0. Back\n";
                        cout << "  Choice: "; cin >> c3; cin.ignore();

                        if (c3 == 1) { cls->viewAssignments(); }
                        else if (c3 == 2) {
                            string title, content;
                            cout << "  Assignment title: "; getline(cin, title);
                            cout << "  Your work       : "; getline(cin, content);
                            cls->submitAssignment(s->getName(), title, content);
                        }
                        else if (c3 == 3) { cls->viewQuizzes(); }
                    } while (c3 != 0);

                } else if (c2 == 3) {
                    int c3;
                    do {
                        printHeader("ONLINE CLASS");
                        cout << "  1. Watch recordings\n";
                        cout << "  2. Join meetings\n";
                        cout << "  0. Back\n";
                        cout << "  Choice: "; cin >> c3; cin.ignore();
                        if (c3 == 1) { cls->viewRecordings(); }
                        else if (c3 == 2) { cls->viewMeetings(); }
                    } while (c3 != 0);

                } else if (c2 == 4) {
                    printHeader("PEOPLE");
                    cls->displayPeople();
                }
            } while (c2 != 0);

        } else if (choice == 2) {
            printHeader("MY GRADES");
            s->viewGrades();
        } else if (choice == 3) {
            printHeader("MY PROFILE");
            s->displayProfile();
        }
    } while (choice != 0);
}

int main() {
    Platform platform;

    MathTeacher*    tMath = new MathTeacher   ("Mr. Khan",   "T001", "khan@school.edu",   "math123");
    ScienceTeacher* tSci  = new ScienceTeacher("Ms. Patel",  "T002", "patel@school.edu",  "sci456");
    EnglishTeacher* tEng  = new EnglishTeacher("Ms. Smith",  "T003", "smith@school.edu",  "eng789");
    CSTeacher*      tCS   = new CSTeacher     ("Mr. Muhammad Khalid Khan", "T004", "mkhalid.khan@nu.edu.pk", "cs000");

    platform.addTeacher(tMath);
    platform.addTeacher(tSci);
    platform.addTeacher(tEng);
    platform.addTeacher(tCS);

    Student* s1 = new Student("Syed Taimoor Ali",  "S001", "taimoor@student.edu",    "pass1");
    Student* s2 = new Student("Abdul Farid", "S002", "farid@student.edu", "pass2");
    Student* s3 = new Student("Zain Noman Dar", "S003", "zain@student.edu",  "pass3");

    platform.addStudent(s1);
    platform.addStudent(s2);
    platform.addStudent(s3);

    Classroom* math101 = new Classroom("MT101", "Calculus",            tMath);
    Classroom* sci201  = new Classroom("SC201",  "Science & Biology",          tSci);
    Classroom* eng301  = new Classroom("EN301",  "English Literature",         tEng);
    Classroom* cs401   = new Classroom("CS401",   "Object Oriented Programming",tCS);

    platform.addClassroom(math101);
    platform.addClassroom(sci201);
    platform.addClassroom(eng301);
    platform.addClassroom(cs401);

    math101->enrollStudent(s1);
    math101->enrollStudent(s2);
    sci201->enrollStudent(s2);
    sci201->enrollStudent(s3);
    cs401->enrollStudent(s1);
    cs401->enrollStudent(s3);
    eng301->enrollStudent(s1);
    eng301->enrollStudent(s2);
    eng301->enrollStudent(s3);


    math101->teacherPost("Welcome to Mathematics 101! Please review Chapter 1 before next class.");
    math101->addAssignment("Problem Set #1", "Solve quadratic equations", "2026-05-10", 20);
    math101->addQuiz("Chapter 1 Quiz", "2026-05-05", 10);
    math101->uploadRecording("Lecture 1 - Algebra Basics",
                             "https://classroom.rec/math-lec1", "45 min");
    math101->scheduleMeeting("Office Hours",
                             "https://meet.google.com/abc-xyz", "2026-05-02 3:00 PM");

    cs401->teacherPost("Welcome to OOP! We will use C++ throughout this course.");
    cs401->addAssignment("Lab 1: Classes & Objects",
                         "Create a simple Bank Account class", "2026-05-08", 25);
    cs401->addQuiz("Quiz 1: OOP Concepts", "2026-05-04", 15);
    cs401->uploadRecording("Lecture 1 - Intro to OOP",
                           "https://classroom.rec/cs-lec1", "50 min");


    printHeader("GOOGLE CLASSROOM  —  C++ OOP Edition");
    cout << "\n  Demo Accounts:\n";
    cout << "  Teachers: T001/math123  T002/sci456  T003/eng789  T004/cs000\n";
    cout << "  Students: S001/pass1   S002/pass2   S003/pass3\n\n";

    int mainChoice;
    do {
        printLine('=');
        cout << "  1. Login\n";
        cout << "  0. Exit\n";
        cout << "  Choice: "; cin >> mainChoice; cin.ignore();

        if (mainChoice == 1) {
            string id, pass;
            cout << "  User ID  : "; getline(cin, id);
            cout << "  Password : "; getline(cin, pass);

            User* user = platform.login(id, pass);
            if (!user) {
                cout << "  Invalid credentials.\n";
                continue;
            }
            cout << "  Welcome, " << user->getName()
                 << "! (" << user->getRole() << ")\n";

            if (user->getRole() == "Teacher")
                teacherMenu(dynamic_cast<Teacher*>(user), platform);
            else
                studentMenu(dynamic_cast<Student*>(user), platform);
        }
    } while (mainChoice != 0);

    cout << "\n  Goodbye!\n";
    return 0;
}