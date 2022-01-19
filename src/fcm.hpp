#ifndef FCM_H
#define FCM_H

#include<map>
#include<string>

using namespace std;

/**
 * fcm - Finite Context Machine. This class is to collect statistical information about texts
 */
class fcm {
    private:
        int k; // k-order model
        double alfa;

    public:
        double distance;
        double modelEntropy;
        double estimatedEntropy;
        
        fcm();
        fcm(int k, double alfa);
        void estimate(map<string, map<char, int>> &model, char *filename);
        void loadModel(map<string, map<char, int>> &model, char *filename);
        void calculateModelEntropy(map<string, map<char, int>> &model);
};

#endif