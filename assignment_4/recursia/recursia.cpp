#using <vector>
#using <string>
#using <iostream>
#using <set>

using std::vector;
using std::string;
using vec_docs = std::vector<Doctor>;
using set_docs = std::set<Doctor>;
using set_pats = std::set<Patient>;
using vec_pats = std::vector<Patient>;
using map_docspats = std::map<Doctor, std::set<Patient>>;

struct Doctor {
    string name;
    int hours_free;
};

struct Patient {
    string name;
    int hours_needed;
};

void CanAllPatientsBeSeen(set_docs rem_doctors, vec_pats rem_pats,
                          map_docspats schedule) {
    if (rem_pats.empty())
        std::cout << "All Patients are scheduled!" << std::endl;
    else {
        for (auto& doctor : rem_doctors) {
            Patient patient = rem_pats.back();
            rem_pats.pop_back();
            if (doctor.hours_free >= patient.hours_needed) {
                schedule.at(doctor).emplace(patient);
                doctor.hours_free -= patient.hours_needed;
                if (doctor.hours_free == 0) {
                    rem_doctors.erase(doctor);
                }
                CanAllPatientsBeSeen(rem_doctors, rem_patiens, schedule);
                doctor.hours_free += patient.hours_needed;
                if (!rem_doctors.find(doctor))
                    rem_doctors.emplace(doctor);
            }
            rem_pats.push_back(patient);
        }
    }
}

int main() {
    Doctor thomas{Thomas, 10};
    Doctor taussig{Taussig, 8};
    Doctor sacks{Sacks, 8};
    Doctor ofri{Ofri, 8};

    Patient lacks{Lakcs, 2};
    Patient gage{Gage, 3};
    Patient mol{Molaison, 4};
    Patient write{Writebol, 3};
    Patient wash{Washkansky, 6};
    Patient sand{sandoval, 8};
    Patient giese{Giese, 6};

    set_docs{thomas, taussig, sacks, ofri};
    vec_pats{lacks, gage, mol, write, wash, sand, giese};
    map_docspats schedule;
}
