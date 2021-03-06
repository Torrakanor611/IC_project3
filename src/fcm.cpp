#include "fcm.hpp"

#include<fstream>
#include<string>
#include<iostream>
#include<cmath>
#include <sstream>

using namespace std;

#define ALPHABETH_SIZE 27

void readChar(ifstream &ifs, char *c);
        
fcm::fcm(){ }

fcm::fcm(int k, double alfa){
    this->k = k;
    this->alfa = alfa; // this->alfa = (*this).alfa
}

void fcm::calculateModelEntropy(map<string, map<char, int>> &model){
    // int jj = 0;
    
    int aux;
    int totalEntrys = 0;
    map<string, int> totalOccurCtx;
    for(auto i : model){
        map<char, int> &occur = model[i.first];
        aux = 0;
        for(auto i : occur){
            aux += i.second;
        }
        totalOccurCtx[i.first] = aux;
        totalEntrys += aux;
        // if (jj < 3){
        //     printf("aux: %d\n", aux);
        //     printf("totalOccurCtx[i.first]: %d\n", totalOccurCtx[i.first]);
        //     printf("totalEntrys: %d\n", totalEntrys);
        // }
        // jj++;
    }
    // jj = 0;
    double probCtx, prob, ctxEntropy, H;
    int ctxTotal;

    for(auto i : model){
        map<char, int> &occur = model[i.first];

        ctxTotal = totalOccurCtx[i.first];
        probCtx = (double)ctxTotal / totalEntrys;

        // if (jj < 3){
        //     printf("ctxTotal: %d\n", ctxTotal);
        //     printf("probCtx: %f\n", probCtx);

        // }
        ctxEntropy = 0;
        for(auto i : occur){
            prob = (double) i.second / ctxTotal;
            ctxEntropy -= prob * log2(prob);
            // if (jj < 3){
            //     printf("prob: %f\n", prob);
            //     printf("ctxEntropy: %f\n", ctxEntropy);
            //     printf("totalEntrys: %d\n---\n", totalEntrys);
            // }
        }
        H += ctxEntropy * probCtx;
        // jj++;
    }
    modelEntropy = H;
}

void fcm::estimate(map<string, map<char, int>> &model, char *filename){
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
    double sumH = 0;
    int count = 0;

    do{
        readChar(ifs, &aux);
        count++;

        totalOccur = 0;
        // modelo contem contexto
        if(model.count(ctx) > 0){
            map<char, int> &occur = model[ctx];
            // contexto tem o char que procuramos
            if(occur.count(aux) > 0){  
                noccur = occur[aux];
            }else{ // n??o tem
                noccur = 0;
            }
            for(auto i : occur){
                // contar o n??mero total de entrys para o contexto
                totalOccur += i.second;
            }
        }else{  // n??o cont??m
            noccur = 0;
            totalOccur = 0;
        }

        sumH += -log2((noccur + alfa) / (totalOccur + (alfa * ALPHABETH_SIZE)));

        // update ctx
        ctx.erase(0,1); // removes first character
        ctx.append(1, aux);
    }while(!ifs.eof());

    // save estimated distance
    distance = sumH;

    // save estimated entropy
    estimatedEntropy = sumH / count;

    // Update number of characters in the file
    nLetters = count;
}

void fcm::loadModel(map<string, map<char, int>> &model, char *filename){
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

    // Filename path to a file were to store the model
    size_t dot = string(filename).find_last_of(".");
    string destFilename = string(filename).substr(0, dot);
    destFilename += "model.txt";
    cout << destFilename << endl;

    ofstream myfile;
    myfile.open (destFilename);
    myfile << k << "\t" << alfa << endl;
    for(auto i : model) {
        map<char, int> &occur = model[i.first];
        myfile << i.first;
        for(auto j : occur){
            myfile << '\t' << j.first << '\t' << j.second;
        }
        myfile << endl;
    }
    myfile.close();
}

void fcm::loadExistingModel(map<string, map<char, int>> &model, char *filename) {
    ifstream file(filename);
    string line;
    int i = -2;
    string a;
    char b;
    int c;
    while (getline(file, line)) {
        istringstream lin(line);
        
        while(i < 0) {
            getline(lin, line, '\t');
            if(i== -2) {
                k = stoi(line);
            }
            else {
                alfa = stod(line);
            }
            i++;
        }

        if(i >= 0) {
            while(getline(lin, line, '\t')) {
                if(i == 0) {
                    a = line;
                    i++;
                }
                else if(i == 1) {
                    b = line[0];
                    i++;
                }
                else {
                    c = stoi(line);
                    model[a][b] = c;
                    if(getline(lin, line, '\t')) {
                        b = line[0];
                        i = 2;
                    }
                    else {
                        i = 0;
                    }
                }
            }
        }
    }
}

void readChar(ifstream &ifs, char *c){
    char s;
    do{
        ifs.get(s);
        if(!(s == '\n'| s == '\t')) {
            *c = s;
        }
    }while((*c == '\n'|*c == '\t') && !ifs.eof());
}