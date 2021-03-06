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

myString myString::capitalize(void)const{
    std::string capitalized;
    for (size_t i = 0; i < string_.size(); i++) {
        //si es una letra minuscula
        if ( (int) string_[i] > 96 && (int) string_[i] < 123 ) {
            capitalized.push_back((char)( ( (int) string_[i] ) - 32 ));
        }else{
            capitalized.push_back(string_[i]);
        }
    }
    return myString(capitalized);
}

myString myString::cut(const unsigned& inicio, const unsigned& fin)const{
    std::string subString;
    if (inicio >= string_.size() || fin >= string_.size() || 
            inicio < 0 || fin < 0 || (inicio > fin && fin != 0) ) {
        return subString;
    }
    
    if (inicio > fin && fin == 0) {
        for (size_t i = 0; i < inicio; i++){
            subString.push_back(string_[i]);
        }
    }else if (fin >= 0) {
        for (size_t i = inicio; i < fin+1; i++){
            subString.push_back(string_[i]);
        }
    }
    return subString;
}


bool myString::contains(const myString& substring)const{
    if (substring.size() > string_.size()) {
        return false;
    }
    
    unsigned i = 0, j = 0;
    while (i < size()) {
        j = i + substring.size() - 1;
        if ( cut(i,j) == substring ) {
            return true;
        }
        i++;
    }
    return false;
}

/*std::ostream& operator<<(std::ostream& os, const myString& string){
    os << string.string();
    return os;
}*/
