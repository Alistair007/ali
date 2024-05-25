//---------------------------------------------------------//
//-----Ali's metaprogramming javascript-styled logging-----//
//-----Please note:----------------------------------------//
//------#-This is still in beta, i'm using std::cout,------//
//---------I'll update the code to use printf()------------//
//---------------------------------------------------------//

#include <iostream>
#include <vector>
#include <type_traits>

template<typename T>
class Printer{
public:
    Printer(const std::vector<T>* ptr){
        vec = ptr;
    }
    Printer<T> expand(){
        // TODO: Add std::vector check!!!
        for (size_t i = 0; i < vec->size(); i++){
            printf("\n  %zu: ", i);
            std::cout << (*vec)[i];
        }
        return *this;
    }
private:
    const std::vector<T>* vec;
};

template<typename T>
Printer<T> print(const std::vector<T>& vec){
    size_t size = vec.size();
    printf("(%zu) [", size);
    for (size_t i = 0; i < size - 1; i++){
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[size - 1];
    printf("]");
    Printer<T> ret(&vec);
    return ret;
}

Printer<std::string> print(const std::string& data){
    printf(data.c_str());
    for (int i = 0; i < 20 - data.length(); i++) printf(" ");
    printf("%p", (void*)&data);
    Printer<std::string> ret(data);
    return ret;
}

int main(){
    std::vector<int> x = {2,34,234,5345,345,2,6,3,45,345};
    print(x);
}