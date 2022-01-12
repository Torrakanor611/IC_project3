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
        int k;
        double alfa;

    public:
        double entropy;

        fcm();
        fcm(int k, double alfa);
        void estimate(map<string, map<char, int>> &model, const char *filename);
        static void loadModel(map<string, map<char, int>> &model, int k, char *filename);
};

#endif