#include "../include/myString.hpp"

bool myString::operator==(const myString& otherString)const{
    if ( string_.size() == otherString.size()) {
        unsigned index = 0;
        while (index < string_.size() && 
                string_[index] == otherString[index]) {
            index++;
        }
        return (index == string_.size());
    }
    return false;
}

void myString::set(const std::string& nuevoString){
    string_.clear();
    for (size_t i = 0; i < nuevoString.size(); i++) {
        string_.push_back(nuevoString[i]);
    }
}

/*myString myString::cut(const unsigned& inicio, const unsigned& fin)const{
    std::string subString;
    if (inicio>fin) {
        for (size_t i = inicio; i < string_.size(); i++){
            subString.push_back(string_[i]);
        }
    }else{
        for (size_t i = inicio; i < fin+1; i++){
            subString.push_back(string_[i]);
        }
    }
    return subString;
}


bool myString::contains(const myString& substring)const{
    unsigned i = 0, j = 0;
    //while (j < substring.size()) {
    //    i = 0;
    //    while (i < string_.size()) {

    //    }
    //}
    return true;
}/*

/*std::ostream& operator<<(std::ostream& os, const myString& string){
    os << string.string();
    return os;
}*/
