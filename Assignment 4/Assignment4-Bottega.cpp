//directories
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
//for it not to be annoying
using namespace std;
//here I will store each passengers data
class Passenger
{
private:
    string name;
    int mileage;
    int years;
    int sequence;
    int priority;
public:
    Passenger(string name, int mileage, int years, int sequence);
    void print();
    int getPriority();
};
//class passenger contructor
Passenger::Passenger(string name, int mileage, int years, int sequence)
{
    this->name = name;
    this->mileage = mileage;
    this->years = years;
    this->sequence = sequence;
    priority = (mileage/1000) + years - sequence;
}
//passenger method to print all important data
void Passenger::print(){
    cout << "Name: " << name << "  \t-> Priority: " << priority << endl;
}
//to get priority
int Passenger::getPriority(){
    return priority;
}
 //parsing input and making passenger objects
Passenger handleInput(string s){
    vector<string> tokens; //this will hold our tokens
    stringstream ss (s);//insterting s into stream
    string word; //for the tokens
    while (getline (ss, word, '\t')) {//parsing by the '\t delimiter'
        if (word.length() == 0)//handling double tab
        {
            continue;
        }
        tokens.push_back (word);//adding into token vector
    }
    if(tokens[1].find(',') != string::npos){//if the miles have a come, parse it
        tokens[1].erase(tokens[1].begin() + tokens[1].find(','));
    }
    return Passenger(tokens[0], stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));//return the passenger
}

class Compare {//the custom comparator for the priority queue
    public:
       bool operator()(Passenger& lhs, Passenger& rhs){//overloading the operator method
           if(lhs.getPriority() < rhs.getPriority()){//comparing
               return true;
           }
           return false;
      }
};

int main()
{
    // my text variable to hold my text
    string myText;
    //vector to hold all my passenger objects
    vector<Passenger> passengers;
    //read from the text
    ifstream myFile;
    myFile.open("customers.txt");
    for(int i = 0; getline(myFile, myText); i++){//read text line by line
        if (i == 0)//if its the top line (Name	Mileage	Years	Sequence) ignore it
        {
            continue;
        }
        
        passengers.push_back(handleInput(myText));//add to passengers vectors
    }
    priority_queue<Passenger, std::vector<Passenger>, Compare> pq; //priority queue to sort the passengers
    for(Passenger p: passengers){//pushing passengers to the priority queue
        pq.push(p);
    }
    while(!pq.empty())//while its not empty, keep poping and printing
    {
        Passenger a = pq.top();
        a.print();
        pq.pop();
    }

    myFile.close();//close the text file
    
}