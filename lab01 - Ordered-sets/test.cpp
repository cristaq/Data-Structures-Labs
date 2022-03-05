#include <iostream>
using namespace std;

struct complex{
    private:
        int real;
        int imaginar;
    public:
        void afisare() {
            if(imaginar >= 0) {
                cout << real << "+" << imaginar << "i" << endl;
            }
            else{
                cout << real << imaginar << "i" << endl;
            }
        }
};

int main() {
    int i;
    cout << i;
}