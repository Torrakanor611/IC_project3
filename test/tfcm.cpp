/**
 * programa tem como entrada 1 ou mais ficheiros de texto para os quais se quer tirar o modelo
 * 
 * example of usage: ./tfcm ../models/simple.txt ../models/PT.utf8
 */
#include "../src/fcm.cpp"

#include<map>
#include<string>

void printModel(map<string, map<char, int>> model, int n);

int main(int argc, char** argv){
    //Command line arguments processing
    if(argc < 2){
        cout << "Error: Usage sintax is: ./tfcm <textfile>" << endl;
        return 0; 
    } 


    map<string, map<char, int>> model;

    for(int i = 1; i < argc; i++){
        
        cout << "trying to process: " << argv[i] << endl;
        fcm::loadModel(model, 5, argv[i]);
        cout << "done" << endl;
    }

    cout << "printing model:" << endl;

    // imprime os 1os 20 pares de model
    printModel(model, 20);
}

void printModel(map<string, map<char, int>> model, int n){
    int i = 0;
    for (auto it : model) {
        cout << "{\"" << it.first << "\" :";
        map<char, int> &internal_map = it.second;
        for (auto it2: internal_map) {
            cout << " {'" << it2.first << "' : " << it2.second << "}";
        }
        cout << "}" << endl;
        if(i > n){
            break;
        }
        i++;
    }
}