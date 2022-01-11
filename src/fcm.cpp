#include "fcm.hpp"        
        
fcm::fcm(){ }

fcm::fcm(int k, double alfa){
    this->k = k;
    this->alfa = alfa; // this->alfa = (*this).alfa
}