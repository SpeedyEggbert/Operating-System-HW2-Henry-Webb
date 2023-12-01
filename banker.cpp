//Code by Henry Webb
#include <iostream>
#include <fstream>
using namespace std;

//Both Process and Memory use an arrays to represent allocation of A, B, C
//[0] = A, [1] = B, [2] = C
class Process{
public:
    Process();
    Process(const int[], const int[]);
    int* getAllocated() const;
    int* getNeed() const;

private:
    int allocation[3];
    int maximum[3];
    int need[3];
};

//Memory class
class Memory{
public:
    Memory();
    Memory(int[]);
    void updateAvailable(int[]);
    int* getAvilable() const;

private:
    int available[3];
};

//Pareser class used to parse the data and return it
class Parser{
public:
    Parser();

    Process pList[5];
    Memory mem;
};

//Default ctor for process
Process::Process(){
     for(int i = 0; i < 3; ++i){
        allocation[i] = 0;
        maximum[i] = 0;
        need[i] = 0;
     }
}

//Ctor that takes curretly allocated memory and the max memory
//Any arrays sent MUST be >=3
Process::Process(const int alloc[],const int max[]){
    for(int i = 0; i < 3; ++i) {
        allocation[i] = alloc[i];
        maximum[i] = max[i];
        need[i] = maximum[i] - allocation[i];
    }

}

//Gets allocation of process, sends pointer to array
int* Process::getAllocated() const{
    static int arr[3];

    for(int i = 0; i < 3; ++i){
        arr[i] = allocation[i];
    }

    return arr;
}

//Gets need of process, sends pointer to array
int* Process::getNeed() const{
    static int arr[3];

    for(int i = 0; i < 3; ++i){
        arr[i] = need[i];
    }

    return arr;
}

//Defauly ctor for memory
Memory::Memory(){
    for(int i = 0; i < 3; ++i)
        available[i] = 0;
}

//Constructor for memeory by sending it avilable memory
//Any array send MUST be >=3
Memory::Memory(int mem[]){
    for(int i = 0; i < 3; ++i)
        available[i] = mem[i];
}

//Updates available memory by sending what previous allocated memory was
void Memory::updateAvailable(int mem[]){
    for(int i = 0; i < 3; ++i)
        available[i] += mem[i];
}

//Get the avaailable memory, returns pointer to array 
int* Memory::getAvilable() const{
    static int arr[3];

    for(int i = 0; i < 3; ++i){
        arr[i] = available[i];
    }

    return arr;
}

//Checks if the need of the process can be met by the available memory
bool operator<=(const Process& p, const Memory& m){
    int *need = p.getNeed();
    int *mem = m.getAvilable();

    for(int i = 0; i < 3; ++i){
        if(!((need[i]) <= (mem[i])))
            return false;
    }

    return true;
}

//Outputs safe sequence to file named "output.txt"
void outputSequence(int safeSequence[]){
    

    cout << "The found safe sequence is: ";

    for(int i = 0; i < 5; ++i){
        cout << "P" << safeSequence[i] << " ";
    }

    cout << endl;
}

//Default ctor is used as parser for data 
Parser::Parser(){
    std::ifstream file("data.txt");

    if(!file.is_open()){
        std::cout << "Unable to open file\n";
        exit(1);
    }

    int A;
    int B;
    int C;
    int avail[3];
    int max[3];

    //Runs five times, reading off a row of 6 numbers split by a comma
    for(int i = 0; i < 5; ++i){
        file >> A;
        avail[0] = A;
        file >> B;
        avail[1] = B;
        file >> C;
        avail[2] = C;

        file.ignore(256, ' ');

        file >> A;
        max[0] = A;
        file >> B;
        max[1] = B;
        file >> C;
        max[2] = C;

        pList[i] = Process(avail, max);
    }

    //Final 3 numbers in data.txt will always be memory
    file >> A;
    avail[0] = A;
    file >> B;
    avail[1] = B;
    file >> C;
    avail[2] = C;

    mem = Memory(avail);

    file.close();  
}



int main(){
    Parser list;
    
    bool safe[5]; //Bool array that keeps track of which corresponding process is safe
    int safeSequence[5] = {-1, -1, -1, -1, -1};//Int array that keeps track of the safe sequence order
    int c = 0;

    //Bankers algorithem
    while(safeSequence[4] == -1){
        for(int i = 0; i < 5; ++i){
            if(!safe[i]){
                if(list.pList[i] <= list.mem){
                    safe[i] = true;
                    safeSequence[c] = i;
                    ++c;
                    list.mem.updateAvailable(list.pList[i].getAllocated());
                }
            }
        }

        if(c > 5){
            cout << "Safe sequence not found" << endl;
            exit(1);
        }
    }

    outputSequencetput(safeSequence);
    
    return 0;
}