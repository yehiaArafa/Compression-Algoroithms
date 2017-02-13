#include <iostream>
#include<fstream>
#include<sstream>
#include <stdlib.h>

using namespace std;

void encode();
void decode();

string to_encode,encoded,decoded;

int main()
{
    fstream file;
    file.open("data.txt");
    char c;
    while (file >> c)
    {
        to_encode+=c;
    }
    file.close();

    cout<<"Original String : "<<to_encode<<endl;
    encode();
    cout<<"Encoded String : "<<encoded<<endl;
    decode();
    cout<<"Decoded String : "<<decoded<<endl;

    return 0;
}

void encode()
{
    int counter=0,i=0;
    char prev;

    while(i<to_encode.size())
    {
        if(to_encode[i]!=prev)
        {
            if(i && counter>3)
            {
                stringstream ss;
                ss<<counter;
                encoded+="!";
                encoded+=ss.str();
            }
            else
            {
                for(int k=0; k<counter-1; k++)
                    encoded+=prev;
            }
            encoded+=to_encode[i];
            prev=to_encode[i];
            counter=0;
        }
        counter++;
        i++;
    }

    if(counter>3)
    {
        stringstream ss;
        ss<<counter;
        encoded+="!";
        encoded+=ss.str();
    }
    else
    {
        for(int k=0; k<counter-1; k++)
            encoded+=prev;
    }
}

void decode()
{
    int i=0;
    int j=1;

    char next,prev;
    int counter=0,prev_counter=1,m=0;

    while(i<encoded.size())
    {
        next=encoded[j];

        if(next=='!')
        {
            counter=encoded[j+1]-'0';

            for(int k=0; k<counter; k++)
            {
                decoded+=encoded[i];
            }
            i=j+2;
            j=i+1;
        }

        else
        {
            decoded+=encoded[i];
            i++;
            j=i+1;
        }

    }
}
