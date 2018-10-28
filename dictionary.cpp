#include"Dictionary.h"

Dictionary::Dictionary(int declaredSize){
    limitSize_ = declaredSize;
    keyTable_.resize(declaredSize);
    contentTable_.resize(declaredSize);
    statusTable_.resize(declaredSize);
    for(int i = 0; i<declaredSize; i++){
        statusTable_[i] = EMPTYF;
    }
}

int Dictionary::Hasher(const string& s, int limit){
    int sum = 0;
    for(int i = 0;i<s.length();i++){
        sum+=(char)s[i];
    }
    return sum%limit;

}

int Dictionary::Resolver(int d_hash){
    for(int attempts = 0; attempts<limitSize_; attempts++){
        if(statusTable_[d_hash]!=FILLEDF){
            return d_hash;
        }
        else
            d_hash++;
        if(d_hash>=limitSize_) d_hash = 0;
    }
    return -1;
}

int Dictionary::AddElement(const string& key,const string& content){
    int indexToInsert = Resolver(Hasher(key,limitSize_));
    if(indexToInsert>=0){
        statusTable_[indexToInsert] = FILLEDF;
        keyTable_[indexToInsert] = key;
        contentTable_[indexToInsert] = content;
    }
    return indexToInsert;
}

const string* Dictionary::FindElement(const string& key){
    int index = Hasher(key,limitSize_);
    for(int attempts = 0; attempts<limitSize_; attempts++){
        if(keyTable_.at(index)==key) {
            string* sptr = &(contentTable_.at(index));
            return sptr;
        }
        else index++;
        if(index>=limitSize_) index = 0;
    }
    #ifdef LOUD
    cout << "Such element("<<key<<") does not exist!" << endl;
    #endif // LOUD
    return nullptr;
}

int Dictionary::ElementIndex(const string& key){
    int index = Hasher(key,limitSize_);
    for(int attempts = 0; attempts<limitSize_; attempts++){
        if(keyTable_.at(index)==key) {
            return index;
        }
        else index++;
        if(index>=limitSize_) index = 0;
    }
    #ifdef LOUD
    cout << "Such element("<<key<<") does not exist!" << endl;
    #endif // LOUD
    return -1;
}

const string* Dictionary::operator[](const string& key){
    return FindElement(key);
}

int Dictionary::GetRealSize() const{
    int number = 0;
    for(int i = 0; i<limitSize_; i++){
        if (statusTable_[i]==FILLEDF) number++;
    }
    return number;
}

int Dictionary::RemoveElement(const string& key){
    int index = ElementIndex(key);
    if(index<0) return -1;
    statusTable_[index] = REMOVEDF;
    keyTable_[index] = "";
    contentTable_[index] = "";
    return index;
}

ostream& operator<<(ostream& os, const Dictionary& dict){
    for(int i = 0; i<dict.limitSize_; i++){
        os << "INDEX: " << i << " KEY: " << dict.keyTable_.at(i) << " CONTENT: " << dict.contentTable_.at(i) << endl;
    }
    return os;
}


