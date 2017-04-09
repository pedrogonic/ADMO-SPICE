
#ifndef Utils_hpp
#define Utils_hpp

#include <string>
#include <sstream>
#include <vector>

#define MY_DEBUG false
#define DEBUG_APROX false
#define VERBOSE true
#define INITIAL_STEP_DIVIDER 10
#define ERROR_TOLERANCE 10E-2
#define MAX_NR1 50
#define MAX_NR2 50
#define RANDOM_RANGE 50
#define SEPARATOR ","
#define UNKNOWN_SEPARATOR "/"
#define OUT_EXT "csv"
#define WINDOWS false

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

int pos(std::vector<std::string>,std::string);

class FileException : public std::runtime_error {
    public :
        FileException() : std::runtime_error("Unable to open file."){}
};

class ParamException : public std::runtime_error {
    public :
    ParamException() : std::runtime_error("Unable to open file."){}
};

class ValException : public std::runtime_error {
    public :
    ValException() : std::runtime_error("Unable to open file."){}
};

class ComponentException : public std::runtime_error {
    public :
    ComponentException() : std::runtime_error("Unable to open file."){}
};

class AnalysisException : public std::runtime_error {
    public :
    AnalysisException() : std::runtime_error("Unable to open file."){}
};

class AdamsMoultonException : public std::runtime_error {
    public :
    AdamsMoultonException() : std::runtime_error("Unable to open file."){}
};

class NoAnalysisException : public std::runtime_error {
    public :
    NoAnalysisException() : std::runtime_error("Unable to open file."){}
};

#endif /* Utils_hpp */
