#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

typedef vector<int> Records;

class RecordsManager {
private:
    fstream _file;
    string _filename;

public:
    RecordsManager(string filename) : _filename(filename) {}

    // Update read function with exception handling
    void read(Records &records) {
        try {
            _file.open(_filename, ios::in);

            if (!_file.is_open()) {
                throw runtime_error("Could not open file: " + _filename);
            }
            string line;
        

    
            while (getline(_file, line)) {
            try {
                int value = stoi(line);
                records.push_back(value);
            }
            catch (const invalid_argument& e) {
                _file.close();
                cout << "<invalid_arguments> error" << endl;
                throw;
            }
            catch (const out_of_range& e) {
                _file.close();
                cout << "<out_of_range> error" << endl;
                throw;
            }
        }

        _file.close();
    }
    catch (...) {
        if (_file.is_open()) {
            _file.close();
        }
        throw;
        }
    }
};

int main(int argc, char* argv[]) {
    Records myRecords;

    string filename = "records.txt";
    if (argc > 1) filename = argv[1];

    RecordsManager recordM(filename); 
    
    try {
    recordM.read(myRecords);

    int sum = 0;
    for (int i = 0; i < myRecords.size(); i++) {
        sum += myRecords[i];
    }
    cout << sum << endl;
}
catch (const exception& e) {
    cout << "Error in main" << e.what() << endl;
    return 1;
    }

    return 0;
}

