#include "bits/stdc++.h"
#include "ssi.hpp"

using namespace std;

int main(){
    string text; getline(std::cin, text);
    SSI s = SSI(text); 
    cout<<s.expr();
}