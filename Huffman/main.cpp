#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map <char,string> myMap;
int beforeFreq,afterFreq;

struct Node {
	int freq;
	char c;
	Node* left;
	Node* right;
};

bool comparable(Node* node1, Node* node2) {
	return node1->freq > node2->freq;
}

void printCode(Node* root, string str) {
	if (root == NULL)
		return;

	if (root->c != '$'){
		myMap[root->c]=str;
		afterFreq += str.length()*root->freq;
		//cout << root->c << " " << str<<endl;
	}
	printCode(root->left, str + "0");
	printCode(root->right, str + "1");

}



int main() {


	fstream file;
	file.open("data.txt");

	char c;
	int freq;

	vector<Node*> v;

	while (file >> c >> freq) {

		Node* node = new Node;
		node->c = c;
		node->freq = freq;
		node->left = NULL;
		node->right = NULL;
		beforeFreq+=freq*8;

		v.push_back(node);

	}
	file.close();
    /*
	for (int i = 0; i < v.size(); i++) {
		cout << v[i]->c << " " << v[i]->freq << endl;
	}

	for (int i = 0; i < v.size(); i++) {
		cout << v[i]->c << " " << v[i]->freq << endl;
	}
  */
	while (v.size() != 1) {
		sort(v.begin(), v.end(), comparable);
		int n = v.size();
		Node* node = new Node;
		node->freq = v[n - 1]->freq + v[n - 2]->freq;
		node->c = '$';
		node->left = v[n - 1];
		node->right = v[n - 2];

		v.pop_back();
		v.pop_back();

		v.push_back(node);
	}



	printCode(v[0],"");
	cout<<"Before frequency "<<beforeFreq<<endl;
	cout<<"After frequency "<<afterFreq<<endl;


  for(map <char,string>::iterator it = myMap.begin();
    it != myMap.end(); ++it)
{
    cout << it->first << " " << it->second<< "\n";
}

	return 0;
}

