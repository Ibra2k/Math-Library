#include "main.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){

    Matrix A(3, 3);

    A.setValues({
        {1, -2, 7},
        {6, 0, -1},
        {-3, -10, 4},
    });

    cout << A;

    cout << A.getDeterminant(A.matrix());



    return 0;
};

