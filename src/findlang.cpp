#include "../src/fcm.cpp"

// ./findlang ../models/PT.utf8 ../models/ENG.utf8 ../models/ESP.utf8 ../models/GER.utf8 ../models/IT.utf8 ../models/FR.utf8 ../models/SWE.utf8 ../models/SWE.utf8 ../models/DAN.utf8  ../models/simple.txt
// ./findlang ../models/ARAB.utf8 ../models/BG.utf8 ../models/BOSN.utf8 ../models/CZ.utf8 ../models/DAN.utf8 ../models/ENG.utf8 ../models/ESP.utf8 ../models/EST.utf8 ../models/FI.utf8 ../models/FR.utf8 ../models/GER.utf8 ../models/GK.utf8 ../models/IS.utf8 ../models/IT.utf8 ../models/JPN.utf8 ../models/LT.utf8 ../models/MAC.utf8 ../models/NOR.utf8 ../models/PT.utf8 ../models/RO.utf8 ../models/RU.utf8 ../models/SK.utf8 ../models/SWE.utf8 ../models/TURK.utf8 ../models/books/lusiadas.txt
// ./findlang ../models/ARABmodel.txt ../models/BGmodel.txt ../models/BOSNmodel.txt ../models/CZmodel.txt ../models/DANmodel.txt ../models/ENGmodel.txt ../models/ESPmodel.txt ../models/ESTmodel.txt ../models/FImodel.txt ../models/FRmodel.txt ../models/GERmodel.txt ../models/GKmodel.txt ../models/ISmodel.txt ../models/ITmodel.txt ../models/JPNmodel.txt ../models/LTmodel.txt ../models/MACmodel.txt ../models/NORmodel.txt ../models/PTmodel.txt ../models/ROmodel.txt ../models/RUmodel.txt ../models/SKmodel.txt ../models/SWEmodel.txt ../models/TURKmodel.txt ../models/books/lusiadas.txt
// ./findlang ../models/ARABmodel.txt ../models/BGmodel.txt ../models/SKmodel.txt ../models/PTmodel.txt ../models/SWEmodel.txt ../models/TURKmodel.txt ../models/lusiadas.txt

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

        f.estimate(model, argv[argc-1]);
        // cout << "distancia estimada: " << f.distance << endl;
        // cout << "entropia estimada: " << f.estimatedEntropy << endl;

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