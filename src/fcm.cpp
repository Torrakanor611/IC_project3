#include "fcm.hpp"

#include<fstream>
#include<string>
#include<iostream>
#include<cmath>

using namespace std;

#define ALPHABETH_SIZE 27

void readChar(ifstream &ifs, char *c);
void entropy(double *entropy, double prob);
        
fcm::fcm(){ }

fcm::fcm(int k, double alfa){
    this->k = k;
    this->alfa = alfa; // this->alfa = (*this).alfa
}

void calculateModelEntropy(map<string, map<char, int>> &model){
    ;
}

void fcm::estimate(map<string, map<char, int>> &model, const char *filename){
    ifstream ifs(filename, std::ios::in);
    if(!ifs.is_open()){
        throw runtime_error("Error: Could not open file!");
    }

    string ctx;
    char aux;
    for (int i = 0; i < k; i++){
        readChar(ifs, &aux);
        ctx.append(1, aux);
    }

    int noccur, totalOccur;

    double H = 0;

    do{
        readChar(ifs, &aux);

        totalOccur = 0;

        // modelo contem contexto
        if(model.count(ctx) > 0){
            map<char, int> &occur = model[ctx];
            // contexto tem o char que procuramos
            if(occur.count(aux) > 0){  
                noccur = occur[aux];
            }else{ // não tem
                noccur = 0;
            }
            for(auto i : occur){
                // contar o número total de entrys para o contexto
                totalOccur += i.second;
            }
        }else{  // não contêm
            noccur = 0;
            totalOccur = 0;
        }

        // estimar entropia
        H += -log2((noccur + alfa) / (totalOccur + (alfa * ALPHABETH_SIZE)));
        // printf("H = %f", H);

        // update ctx
        ctx.erase(0,1); // removes first character
        ctx.append(1, aux);
    }while(!ifs.eof());

    // save estimated entropy on static atribute
    distance = H;
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