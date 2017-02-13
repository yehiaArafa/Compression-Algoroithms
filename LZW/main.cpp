#include <iostream>
#include<map>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

map <string,string> Dect;

string to_encode,encoded,decoded;
float beforeCompression,afterCompression;
float compressionRatio;

void encode();
//void decode();


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

    beforeCompression=to_encode.size() * 8;

    cout<<"Original String : "<<to_encode<<endl;
    encode();
    cout<<"Size before compresion : "<<beforeCompression<<endl;
    cout<<"Encoded String : "<<encoded<<endl;
    afterCompression=(encoded.size()+4) * 8; // add 4 for the initial map to be sent with the file
    cout<<"Size after compression : "<<afterCompression<<endl;
    compressionRatio=(afterCompression/beforeCompression) * 100 ;
    cout<<"Compression ratio : "<<compressionRatio<<"%"<<endl;
    Dect.clear();
   // decode();
   // cout<<"Decoded String : "<<decoded<<endl;
}


void encode(){
  string temp="";
  char c;
  int counter=2;
  Dect["q"]="0";
  Dect["x"]="1";

  for(int i=0;i<to_encode.size();i++){
    c=to_encode[i];

     if(Dect[temp+c]!=""){
          temp+=c;
    }
    else{
        counter++;
        encoded+=Dect[temp];
        stringstream s;
        s << counter;
        Dect[temp+c]=s.str();
        temp=c;
    }
  }
 encoded+=Dect[temp];

}
/*
void decode(){
  string temp="";
  bool flag=false;
  char c;
  string prevCode,currentCode,addDect;
  int counter=2;
  Dect["1"]="q";
  Dect["2"]="x";
  temp=encoded[0];
  prevCode=Dect[temp];
  decoded+=prevCode;

  for(int i=1;i<encoded.size();i++){
     temp=encoded[i];
     currentCode=Dect[temp];
     if(currentCode==""){
        currentCode=prevCode+prevCode[0];
        counter++;
        stringstream s;
        s << counter;
        Dect[s.str()]=currentCode;
        flag=true;
     }
     else{
        flag=false;
     }
     decoded+=currentCode;
     if(!flag){
     c=currentCode[0];
     addDect=prevCode+c;
     counter++;
     stringstream s;
     s << counter;
     Dect[s.str()]=addDect;
     }
     prevCode=currentCode;
  }

}
*/

