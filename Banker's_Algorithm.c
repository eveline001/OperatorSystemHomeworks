#include <iostream>

const int MAXM = 1;
const int MAXN = 100;

using namespace std;

int Resource[MAXM], Available[MAXM];
int Claim[MAXN][MAXM], Allocation[MAXN][MAXM];
int n;

int Need[MAXN][MAXM];
bool Finish[MAXN];
int SafetQ[MAXN];
int finished;

bool IsAvailable(const int thisNeed[], const int thisAvailable[]){
    for(int i = 0; i < MAXM; i++){
        if(thisNeed[i] > thisAvailable[i]) return false;
    }
    return true;
}

void LineAdd(int LineA[], int LineB[]){
    for(int i = 0; i < MAXM; i++){
        LineA[i] += LineB[i];
    }
}

int main()
{
    cout << "Please input " << MAXM << " integers of Resource:" << endl;
    for(int i = 0; i < MAXM; i++) cin >> Resource[i];
    cout << "Please input " << MAXM << " integers of Available:" << endl;
    for(int i = 0; i < MAXM; i++) cin >> Available[i];
    cout << "Please input the number of process:" << endl;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cout << "Please input " << MAXM << " integers of Claim[" << i << "]:" << endl;
        for(int j = 0; j < MAXM; j++) cin >> Claim[i][j];
    }
    for(int i = 1; i <= n; i++){
        cout << "Please input " << MAXM << " integers of Allocation[" << i << "]:" << endl;
        for(int j = 0; j < MAXM; j++) cin >> Allocation[i][j];
    }
    cout << "Running..." << endl;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < MAXM; j++){
            Need[i][j] = Claim[i][j] - Allocation[i][j];
        }
        Finish[i] = false;
    }
    finished = 0;
    for(int times = 0; times < n; times++){
        for(int i = 1; i <= n; i++){
            if(!Finish[i]){
                if(IsAvailable(Need[i], Available)){
                    Finish[i] = true;
                    SafetQ[times] = i;
                    finished++;
                    LineAdd(Available, Claim[i]);
                }
            }
        }
    }
    if(finished == n){
        cout << "True" << endl;
        cout << "Safet Queue: ";
        for(int i = 0; i < n; i++) cout << SafetQ[i] << ' ';
        cout << endl;
    }else{
        cout << "False" << endl;
    }
    return 0;
}