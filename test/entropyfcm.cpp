#include "../src/fcm.cpp"

#include<map>
#include<string>

int main(int argc, char** argv){

    map<string, map<char, int>> model;
    //Command line arguments processing
    if(argc != 2){
        cout << "Error: Usage sintax is: ./tfcm <textfile>" << endl;
        return 0; 
    }


    for(int i=20; i < 21; i++){
        fcm f(i, 0.1);
        cout << "Processing for order " << i << " ..." << endl;
        f.loadModel(model, argv[1]);
        f.calculateModelEntropy(model);
        cout << "Model Entropy: " << f.modelEntropy << endl;
        model.clear();
    }



}