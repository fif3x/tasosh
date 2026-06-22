#include <tasosh/token.h>

#include <string>
#include <vector>
#include <bits/stdc++.h>

std::vector <std::string> tasosh::token::tokens = { };

void tasosh::token::tokenize(std::string line){
    std::stringstream str(line);

    std::string intermediate = { };

    while(getline(str, intermediate, ' ')){
        if(intermediate.empty()) continue; // for the spaces before the commands

        tasosh::token::tokens.push_back(intermediate);
    }
}