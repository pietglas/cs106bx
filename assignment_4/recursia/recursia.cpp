#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>

using std::cout;
using std::endl;
using std::vector;
using std::string;


struct Doctor {
    string name;
    mutable int hours_free;
};

struct Patient {
    string name;
    int hours_needed;
};

// overload operators, so we can put our types into collections
namespace std {
    template <> struct hash<Doctor> {
        size_t operator()(const Doctor & x) const {
            std::hash<std::string> h;
            return h(x.name);
        }
    };

    template <> struct hash<Patient> {
        size_t operator()(const Patient & x) const {
            std::hash<std::string> h;
            return h(x.name);
        }
    };

    bool operator ==(const Doctor & doctor1, const Doctor & doctor2) {
        if (doctor1.name == doctor2.name)
            return true;
        else
            return false;
    }

    bool operator ==(const Patient & patient1, const Patient & patient2) {
        if (patient1.name == patient2.name)
            return true;
        else
            return false;
    }

     bool operator <(const Doctor & doctor1, const Doctor & doctor2) {
        if (doctor1.name < doctor2.name)
            return true;
        else
            return false;
    }

    bool operator <(const Patient & patient1, const Patient & patient2) {
        if (patient1.name < patient2.name)
            return true;
        else
            return false;
    }
}

using set_strs = std::set<std::string>;
using vec_docs = std::vector<Doctor>;
using set_docs = std::set<Doctor>;
using set_pats = std::set<Patient>;
using vec_pats = std::vector<Patient>;
using map_docspats = std::unordered_map<Doctor, std::vector<Patient>>;
using vec_schedules = std::vector<std::unordered_map<Doctor, std::vector<Patient>>>;



void GenerateSchedules(vec_pats& rem_pats, map_docspats& schedule,
        vec_schedules& possible_schedules, int& nr_possible_schedules) {
    
    if (rem_pats.empty()) {
        possible_schedules.push_back(schedule);
        ++nr_possible_schedules;
    }

    else {
        for (auto& pair : schedule) {
            const Doctor& doctor = pair.first;
            Patient patient = rem_pats.back();
            rem_pats.pop_back();
            if ((doctor.hours_free) >= (patient.hours_needed)) {
                schedule.at(doctor).push_back(patient);
                doctor.hours_free -= patient.hours_needed;
                GenerateSchedules(rem_pats, schedule, possible_schedules,
                    nr_possible_schedules);
                doctor.hours_free += patient.hours_needed;
            }
            if (doctor.hours_free >= patient.hours_needed)
                schedule.at(doctor).pop_back();
            rem_pats.push_back(patient);
        }
    }
    
}

bool CanAllPatientsBeSeen(const vec_docs& doctors, const vec_pats& patients,
        map_docspats& schedule) {
    // set values
    for (int i = 0; i != doctors.size(); i++) {
        Doctor doctor = doctors.at(i);
        vec_pats personal_schedule;
        schedule.emplace(doctor, personal_schedule);
    }
    vec_pats rem_patients = patients;
    vec_schedules possible_schedules;
    int nr_possible_schedules = 0;

    // do the recursion by calculation all possibles schedules (if any)
    GenerateSchedules(rem_patients, schedule, possible_schedules,
        nr_possible_schedules);

    bool scheduling_possible = true;
    if (nr_possible_schedules > 0) {
        schedule = possible_schedules.at(0);
    }
    else
        scheduling_possible = false;

    return scheduling_possible;
}


int main() {
    Doctor thomas{"Thomas", 10};
    Doctor taussig{"Taussig", 8};
    Doctor sacks{"Sacks", 8};
    Doctor ofri{"Ofri", 8};

    Patient lacks{"Lakcs", 2};
    Patient gage{"Gage", 3};
    Patient mol{"Molaison", 4};
    Patient write{"Writebol", 3};
    Patient wash{"Washkansky", 6};
    Patient sand{"Sandoval", 8};
    Patient giese{"Giese", 6};

    vec_docs doctors{thomas, taussig, sacks, ofri};
    vec_pats patients{lacks, gage, mol, write, wash, sand, giese};

    map_docspats schedule;

    bool schedule_exists = CanAllPatientsBeSeen(doctors, patients, schedule);
    cout << schedule_exists << endl;
    
    
    // In case we want to print the schedule

    // for (auto & schedule : possible_schedules) {
    //     for (auto& doctor : doctors) {
    //         cout << "Doctor: " << doctor.name << endl;
    //         cout << "Patients: ";
    //         for (auto& patient : schedule.at(doctor)) {
    //             cout << patient.name << "  ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }   
    
}
