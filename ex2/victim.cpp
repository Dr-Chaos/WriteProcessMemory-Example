#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>

int main() {
    system("title VICTIM");
    srand(time(NULL));
    while(0x01) {
        int data=rand()%100+1;
        std::cout<<&data<<" = "<<data<<std::endl;
        getch();
    } return 0x00;
}
