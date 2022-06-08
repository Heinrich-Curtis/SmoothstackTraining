/*
    Messing around with some string functions I rarely use
*/
#include <string>
#include <iostream>
#include <cassert>

int main(){
    std::string s1 ("Hello There!");
    assert(s1.length() == 12);
    s1.replace(4,1,"\0"); //strings aren't char*, they don't end at the null,
    //they just don't print unprintable characters. Replacing a character with a null does
    //seem to remove it from the string though
    for (char c : s1){
        std::cout << c << " ";
    }
    std::cout << std::endl;
    std::cout << s1 << std::endl;
    //assert(s1.length() == 4);
    std::cout <<s1.length() << std::endl;
    std::string s2("1159486");
    char c = s2[s2.length() - 1];
    assert(c == '6');
    s2.erase(s2.length()-1);
    assert(s2 == "115948");
    assert(s2.length() == 6);
}