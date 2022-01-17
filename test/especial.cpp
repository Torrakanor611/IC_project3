#include "../src/fcm.cpp"

#include<map>
#include<string>

void printModel(map<string, map<char, int>> model, int n);

int main(int argc, char** argv){

    map<string, map<char, int>> model;

    fcm::loadModel(model, 5, "../models/especial.utf8");

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