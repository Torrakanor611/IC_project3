#include "../src/fcm.cpp"

// ./findlang ../models/PT.utf8 ../models/ENG.utf8 ../models/ESP.utf8 ../models/GER.utf8 ../models/IT.utf8 ../models/FR.utf8 ../models/SWE.utf8 ../models/SWE.utf8 ../models/DAN.utf8  ../models/simple.txt
// ./findlang ../models/PTmodel.txt ../models/ENGmodel.txt ../models/ESPmodel.txt../models/GERmodel.txt ../models/ITmodel.txt ../models/FRmodel.txt ../models/SWEmodel.txt ../models/DANmodel.txt ../models/simple.txt

int main(int argc, char** argv)
{
    //Command line arguments processing
    if(argc < 2){
        cout << "Error: Usage sintax is: ./findlang <textfile> <textfile>" << endl;
        return 0; 
    }

    //Context order and alpha
    int k = -1;
    float a = 0;
    char l ='a';

    while(l != 'y' & l != 'n') {
        cout << "Load models (y/n): ";
        cin >> l;
    }

    if(l == 'n') {
        while(k <= 0){
            cout << "Insert context order (k): ";
            cin >> k;
        }
        while(a <= 0){
            cout << "Insert alpha (a): ";
            cin >> a;
        }
    }
    
    //Load models and processing
    fcm f = fcm(k, a);
    int distMin;
    string modelLang;
    for(int i = 1; i < argc - 1; i++){
        
        map<string, map<char, int>> model;
        
        cout << "Begin processing " << argv[i] << endl;
        if(l == 'n') {
            f.loadModel(model, argv[i]);
        }
        else {
            f.loadExistingModel(model, argv[i]);
        }

        if(i == 1) {
            modelLang = argv[i];
            distMin = f.distance;
        }
        else {
            if(distMin > f.distance) {
                modelLang = argv[i];
                distMin = f.distance;
            }
        }
        cout << "Model loaded sucessfully!" << endl;
    }

    cout << "\nGuess for the language in which a text was written: " << modelLang << endl;
    
    return 0;
}