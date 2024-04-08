#include <iostream>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

class Student {
private:
    std::string name;
    std::string surname;
    std::string albumNumber;
    std::vector<float> grades;

public:
    Student(const std::string& initName = "", const std::string& initSurname = "", const std::string& initAlbumNumber = "", const std::vector<float>& initGrades = {})
        : name(initName), surname(initSurname), albumNumber(initAlbumNumber), grades(initGrades) {
        if (!isValidAlbumNumber(initAlbumNumber)) {
            cout << "Invalid album number provided" << endl;
            albumNumber = "";
        }
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setSurname(const std::string& newSurname) {
        surname = newSurname;
    }

    bool setAlbumNumber(const std::string& newAlbumNumber) {
        if (isValidAlbumNumber(newAlbumNumber)) {
            albumNumber = newAlbumNumber;
            return true;
        }
        return false;
    }

    bool add_grade(float grade) {
        if (grade >= 2.0 && grade <= 5.0) {
            grades.push_back(grade);
            return true;
        }
        return false;
    }

    float calculate_grade() const {
        if (grades.empty()) {
            return 0.0f;
        }
        float sum = std::accumulate(grades.begin(), grades.end(), 0.0f);
        return sum / grades.size();
    }

    bool passedSemester() const {
        int countFail = count(grades.begin(), grades.end(), 2.0f);
        return countFail <= 1;
    }

    void print() const {
        std::cout << "Student: " << name << " " << surname << " Album Number: " << albumNumber << " Grades:";
        for (const auto& grade : grades) {
            std::cout << " " << grade;
        }
        std::cout << "Mean Grade: " << calculate_grade();
        std::cout << "Passed: " << (passedSemester() ? "Yes" : "No") << std::endl;
    }

private:
    bool isValidAlbumNumber(const std::string& number) const {
        if (number.length() < 5 || number.length() > 6) return false;
        return all_of(number.begin(), number.end(), ::isdigit);
    }
};

int main() {
    Student student("Some", "Student", "12345", {2, 3, 4, 5, 3});
    student.print();
    if (!student.setAlbumNumber("1234")) {
        cout << "Failed to update album number: invalid format." << endl;
    }
    return 0;
}

