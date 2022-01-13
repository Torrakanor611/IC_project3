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

        void calculateModelEntropy(map<string, map<char, int>> &model);

    public:
        static double modelEntropy;

        fcm();
        fcm(int k, double alfa);
        void estimate(map<string, map<char, int>> &model, char *filename);
        static void loadModel(map<string, map<char, int>> &model, int k, char *filename);
};

#endif