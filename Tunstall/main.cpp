#include <iostream>
#include<map>
#include<sstream>
#include<fstream>
#include<vector>
#include<math.h>

using namespace std;

map <char,string> myMap;

struct Node {
	float prob;
	string c;
	Node* left;
	Node* middle;
	Node* right;
};

string c1,c2,c3;
float prob1,prob2,prob3;


Node *get_max(Node **myNode){
Node *maxx;
if( (*myNode)->left->prob > (*myNode)->middle->prob ){

    if( (*myNode)->left->prob > (*myNode)->right->prob )
        maxx=(*myNode)->left;
    else
        maxx=(*myNode)->middle;
}
else{
    if( (*myNode)->right->prob > (*myNode)->right->prob )
        maxx=(*myNode)->right;
    else
        maxx=(*myNode)->middle;
}
}

void add_node(Node**myNode){

Node *n1,*n2,*n3;

n1=new Node;
n2=new Node;
n3=new Node;

n1->c=(*myNode)->c+c1;
n2->c=(*myNode)->c+c2;
n3->c=(*myNode)->c+c3;

n1->prob=(*myNode)->prob*prob1;
n2->prob=(*myNode)->prob*prob2;
n3->prob=(*myNode)->prob*prob3;

n1->left=NULL;
n1->middle=NULL;
n1->right=NULL;

n2->left=NULL;
n2->middle=NULL;
n2->right=NULL;

n3->left=NULL;
n3->middle=NULL;
n3->right=NULL;

(*myNode)->left=n1;
(*myNode)->middle=n2;
(*myNode)->right=n3;

}


void print_code(Node*root){
if (root == NULL)
		return;
print_code(root->left);
print_code(root->middle);
print_code(root->right);

 if (root->c != "$"){
    if(root->left==NULL && root->right==NULL)
    cout << root->c << " " <<root->prob<<endl;

	}
}




int main()
{

    fstream file;
	file.open("data.txt");

	string c;
	float prob;

	vector<Node*> v;
	 Node *newNode;
     Node*p;

	while (file >> c >> prob) {

		Node* node = new Node;
		node->c = c;
		node->prob = prob;
		node->left = NULL;
		node->middle = NULL;
		node->right = NULL;
		v.push_back(node);
	}
	file.close();

	int num_of_leaves=0;
	int m=v.size(),
	    n=3;//target output length


    while (v.size() != 1) {
		int n = v.size();
		Node* node = new Node;
		node->prob=0;
		node->c = "$";
		node->left = v[n - 3];
		node->middle = v[n - 2];
		node->right = v[n - 1];
        num_of_leaves=num_of_leaves+3;

		v.pop_back();
		v.pop_back();
		v.pop_back();

		v.push_back(node);
	}

   Node *root = v[0];

   c1=root->left->c;
   c2=root->middle->c;
   c3=root->right->c;
   prob1=root->left->prob;
   prob2=root->middle->prob;
   prob3=root->right->prob;


   newNode=get_max(&root);
   add_node(&newNode);

   num_of_leaves=num_of_leaves+2;

  while(num_of_leaves<=(pow(2,n)-m)){
     p=get_max(&newNode);
     add_node(&p);
     num_of_leaves=num_of_leaves+2;
     newNode=p;
    }


   print_code(root);

    return 0;
}
