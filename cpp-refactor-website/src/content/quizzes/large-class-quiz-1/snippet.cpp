#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class StudentManagementSystem {
private:
    // Student data
    std::vector<std::string> studentIds;
    std::map<std::string, std::string> studentNames;
    std::map<std::string, std::string> contactEmails;
    std::map<std::string, std::string> contactPhones;
    std::map<std::string, std::string> addresses;
    std::map<std::string, int> graduationYears;
    
    // Course data
    std::vector<std::string> availableCourses;
    std::map<std::string, std::string> courseDescriptions;
    std::map<std::string, int> courseCredits;
    std::map<std::string, std::vector<std::string>> coursePrerequisites;
    std::map<std::string, std::string> courseInstructors;
    std::map<std::string, std::string> courseDepartments;
    
    // Enrollment data
    std::map<std::string, std::vector<std::string>> studentEnrollments; // studentId -> courseIds
    std::map<std::string, std::map<std::string, double>> studentGrades; // studentId -> (courseId -> grade)
    
    // Authentication data
    std::map<std::string, std::string> userPasswords;
    std::string currentUser;
    bool isAdmin;
    
    // Reporting variables
    std::string reportFormat;
    bool includeDetailedInfo;
    
public:
    StudentManagementSystem() {
        // Initialize with some defaults
        reportFormat = "txt";
        includeDetailedInfo = false;
        isAdmin = false;
    }
    
    // Authentication methods
    bool login(const std::string& username, const std::string& password) {
        if (userPasswords.find(username) != userPasswords.end() && 
            userPasswords[username] == password) {
            currentUser = username;
            // Check if user is admin
            isAdmin = (username == "admin");
            return true;
        }
        return false;
    }
    
    void logout() {
        currentUser = "";
        isAdmin = false;
    }
    
    // Student management methods
    void addStudent(const std::string& id, const std::string& name, const std::string& email) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        studentIds.push_back(id);
        studentNames[id] = name;
        contactEmails[id] = email;
    }
    
    void updateStudentContact(const std::string& id, const std::string& email, const std::string& phone) {
        if (!isAdmin && currentUser != id) {
            std::cout << "Permission denied." << std::endl;
            return;
        }
        
        contactEmails[id] = email;
        contactPhones[id] = phone;
    }
    
    void setStudentAddress(const std::string& id, const std::string& address) {
        if (!isAdmin && currentUser != id) {
            std::cout << "Permission denied." << std::endl;
            return;
        }
        
        addresses[id] = address;
    }
    
    void setGraduationYear(const std::string& id, int year) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        graduationYears[id] = year;
    }
    
    // Course management methods
    void addCourse(const std::string& courseId, const std::string& description, int credits) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        availableCourses.push_back(courseId);
        courseDescriptions[courseId] = description;
        courseCredits[courseId] = credits;
    }
    
    void setCourseInstructor(const std::string& courseId, const std::string& instructor) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        courseInstructors[courseId] = instructor;
    }
    
    void setCourseDepartment(const std::string& courseId, const std::string& department) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        courseDepartments[courseId] = department;
    }
    
    void addCoursePrerequisite(const std::string& courseId, const std::string& prerequisiteId) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        coursePrerequisites[courseId].push_back(prerequisiteId);
    }
    
    // Enrollment methods
    void enrollStudent(const std::string& studentId, const std::string& courseId) {
        if (!isAdmin && currentUser != studentId) {
            std::cout << "Permission denied." << std::endl;
            return;
        }
        
        // Check if course exists
        if (std::find(availableCourses.begin(), availableCourses.end(), courseId) == availableCourses.end()) {
            std::cout << "Course not found." << std::endl;
            return;
        }
        
        // Check if student exists
        if (std::find(studentIds.begin(), studentIds.end(), studentId) == studentIds.end()) {
            std::cout << "Student not found." << std::endl;
            return;
        }
        
        // Check prerequisites
        if (coursePrerequisites.find(courseId) != coursePrerequisites.end()) {
            for (const auto& prereq : coursePrerequisites[courseId]) {
                bool completed = false;
                if (studentEnrollments.find(studentId) != studentEnrollments.end()) {
                    auto& enrollments = studentEnrollments[studentId];
                    if (std::find(enrollments.begin(), enrollments.end(), prereq) != enrollments.end()) {
                        if (studentGrades[studentId][prereq] >= 60.0) { // Pass grade
                            completed = true;
                        }
                    }
                }
                
                if (!completed) {
                    std::cout << "Prerequisite not met: " << prereq << std::endl;
                    return;
                }
            }
        }
        
        studentEnrollments[studentId].push_back(courseId);
        std::cout << "Student " << studentId << " enrolled in " << courseId << std::endl;
    }
    
    void assignGrade(const std::string& studentId, const std::string& courseId, double grade) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        if (studentEnrollments.find(studentId) == studentEnrollments.end()) {
            std::cout << "Student not enrolled in any courses." << std::endl;
            return;
        }
        
        auto& enrollments = studentEnrollments[studentId];
        if (std::find(enrollments.begin(), enrollments.end(), courseId) == enrollments.end()) {
            std::cout << "Student not enrolled in this course." << std::endl;
            return;
        }
        
        studentGrades[studentId][courseId] = grade;
        std::cout << "Grade assigned: " << grade << " for " << studentId << " in " << courseId << std::endl;
    }
    
    // Reporting methods
    void setReportingOptions(const std::string& format, bool detailed) {
        reportFormat = format;
        includeDetailedInfo = detailed;
    }
    
    void generateStudentReport(const std::string& studentId) {
        if (!isAdmin && currentUser != studentId) {
            std::cout << "Permission denied." << std::endl;
            return;
        }
        
        std::cout << "===== Student Report =====" << std::endl;
        std::cout << "ID: " << studentId << std::endl;
        std::cout << "Name: " << studentNames[studentId] << std::endl;
        std::cout << "Email: " << contactEmails[studentId] << std::endl;
        
        if (includeDetailedInfo) {
            std::cout << "Phone: " << contactPhones[studentId] << std::endl;
            std::cout << "Address: " << addresses[studentId] << std::endl;
            std::cout << "Graduation Year: " << graduationYears[studentId] << std::endl;
        }
        
        std::cout << "\nEnrolled Courses:" << std::endl;
        if (studentEnrollments.find(studentId) != studentEnrollments.end()) {
            for (const auto& courseId : studentEnrollments[studentId]) {
                std::cout << "- " << courseId << ": " << courseDescriptions[courseId];
                
                if (studentGrades.find(studentId) != studentGrades.end() && 
                    studentGrades[studentId].find(courseId) != studentGrades[studentId].end()) {
                    std::cout << " | Grade: " << studentGrades[studentId][courseId];
                }
                
                std::cout << std::endl;
            }
        }
        
        std::cout << "=========================" << std::endl;
    }
    
    void generateCourseReport(const std::string& courseId) {
        // Only admins can see all student grades for a course
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        std::cout << "===== Course Report =====" << std::endl;
        std::cout << "Course ID: " << courseId << std::endl;
        std::cout << "Description: " << courseDescriptions[courseId] << std::endl;
        std::cout << "Credits: " << courseCredits[courseId] << std::endl;
        std::cout << "Instructor: " << courseInstructors[courseId] << std::endl;
        std::cout << "Department: " << courseDepartments[courseId] << std::endl;
        
        std::cout << "\nPrerequisites:" << std::endl;
        if (coursePrerequisites.find(courseId) != coursePrerequisites.end()) {
            for (const auto& prereq : coursePrerequisites[courseId]) {
                std::cout << "- " << prereq << ": " << courseDescriptions[prereq] << std::endl;
            }
        }
        
        std::cout << "\nEnrolled Students:" << std::endl;
        for (const auto& [id, courses] : studentEnrollments) {
            if (std::find(courses.begin(), courses.end(), courseId) != courses.end()) {
                std::cout << "- " << id << ": " << studentNames[id];
                
                if (studentGrades.find(id) != studentGrades.end() && 
                    studentGrades[id].find(courseId) != studentGrades[id].end()) {
                    std::cout << " | Grade: " << studentGrades[id][courseId];
                }
                
                std::cout << std::endl;
            }
        }
        
        std::cout << "=========================" << std::endl;
    }
    
    // Other system utilities
    void exportData(const std::string& filename) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        std::cout << "Exporting data to " << filename << "..." << std::endl;
        // Imagine file export code here
    }
    
    void importData(const std::string& filename) {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        std::cout << "Importing data from " << filename << "..." << std::endl;
        // Imagine file import code here
    }
    
    void backupSystem() {
        if (!isAdmin) {
            std::cout << "Permission denied. Admin access required." << std::endl;
            return;
        }
        
        std::cout << "Backing up system data..." << std::endl;
        // Imagine backup code here
    }
    
    void printSystemStats() {
        std::cout << "System Statistics:" << std::endl;
        std::cout << "Total Students: " << studentIds.size() << std::endl;
        std::cout << "Total Courses: " << availableCourses.size() << std::endl;
        std::cout << "Total Enrollments: ";
        
        int totalEnrollments = 0;
        for (const auto& [_, courses] : studentEnrollments) {
            totalEnrollments += courses.size();
        }
        
        std::cout << totalEnrollments << std::endl;
    }
};

// Example usage
int main() {
    StudentManagementSystem system;
    
    // Assume we have setup the admin account somehow
    system.login("admin", "adminpass");
    
    // Setup some data
    system.addStudent("S001", "John Doe", "john@example.com");
    system.addCourse("CS101", "Introduction to Programming", 3);
    system.enrollStudent("S001", "CS101");
    system.assignGrade("S001", "CS101", 85.5);
    
    // Generate a report
    system.generateStudentReport("S001");
    
    return 0;
}
