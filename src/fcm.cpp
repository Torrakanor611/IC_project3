#include "fcm.hpp"

#include<fstream>
#include<string>
#include<iostream>

using namespace std;

void readChar(ifstream &ifs, char *c);
        
fcm::fcm(){ }

fcm::fcm(int k, double alfa){
    this->k = k;
    this->alfa = alfa; // this->alfa = (*this).alfa
}

void fcm::loadModel(map<string, map<char, int>> &model, int k, char *filename){
    ifstream ifs(filename, std::ios::in);
    if(!ifs.is_open()){
        throw runtime_error("Error: Could not open file!");
    }

    string ctx;
    char aux;
    for (int i = 0; i < k; i++){
        readChar(ifs, &aux);

        printf("char: %c\n", aux);

        ctx.append(1, aux);
    }

    do{
        readChar(ifs, &aux);

        if (model.count(ctx) > 0){
            model[ctx][aux]++;
        }else{
            map<char, int> empty;
            model[ctx] = empty;
            model[ctx][aux]++;
        }
        // update ctx
        ctx.erase(0,1); // removes first character
        ctx.append(1, aux);
    }while(!ifs.eof());
}

void readChar(ifstream &ifs, char *c){
    do{
        ifs.get(*c);
    }while(*c == '\n' && !ifs.eof());
}