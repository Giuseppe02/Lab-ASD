#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stack>

using namespace std;
// Lavoro di gruppo di: Tardi Giuseppe(337492) - Orsi Alina(335150)

int details = 0;

/// struct per il nodo dell'albero
typedef struct node {
    int val;
    struct node *L;
    struct node *R;
} node_t;


node_t *node_new(int elem) { /// crea nuovo nodo
    node_t *t = new node_t;
    t->val = elem;
    t->L = NULL;
    t->R = NULL;
    return t;
}

void tree_print(node_t *n){
    if(n == NULL) return; 
    cout << n->val<<" ";
    tree_print(n->L);
    tree_print(n->R);
    
}

void print_dot(node_t* node, ofstream& file) {
    if (node == NULL) {
        return;
    }
    file << node->val << " [label=\"" << node->val << "\"]" << endl;
    if (node->L != NULL) {
        file << node->val << " -> " << node->L->val << endl;
        print_dot(node->L, file);
    }
    if (node->R != NULL) {
        file << node->val << " -> " << node->R->val << endl;
        print_dot(node->R, file);
    }
}

void print_tree(node_t* root1, string filename) {
    ofstream file(filename);
    file << "digraph Tree {" << endl;
    print_dot(root1, file);
    file << "}" << endl;
    file.close();
}
//funzione ricorsiva che verifica se i due alberi sono uguali o no
bool sameTree(node_t* root1, node_t* root2){
    if(root1 == nullptr && root2==nullptr) return true;
    else if(root1==nullptr || root2==nullptr) return false;
    else if(root1->val != root2->val) return false;
    else return sameTree(root1->L,root2->L) && sameTree(root1->R,root2->R);
}
//funzione per controllare se sono isomorfi
bool isIsomorphic(node_t* root1, node_t* root2) {
    if(root1 == nullptr && root2==nullptr) return true;
    else if(root1==nullptr || root2==nullptr) return false;
    
    stack<node_t*> stack1, stack2;
    stack1.push(root1);
    stack2.push(root2);
    
    while (!stack1.empty() && !stack2.empty()) {
        node_t* node1 = stack1.top();
        node_t* node2 = stack2.top();
        stack1.pop();
        stack2.pop();
        
        if (node1->val != node2->val) {
            return false;
        }
        if (node1->L && node2->L) {
            stack1.push(node1->L);
            stack2.push(node2->L);
        } else if (node1->L || node2->L) {
            return false;
        }
        
        if (node1->R && node2->R) {
            stack1.push(node1->R);
            stack2.push(node2->R);
        } else if (node1->R || node2->R) {
            return false;
        }
    }
    return stack1.empty() && stack2.empty();
}


void tree_insert_child_L(node_t *n, int elem) {
    /// inserisco il nuovo nodo con contenuto elem come figlio Left del nodo n
    /// creo nodo
    n->L = node_new(elem);
}

void tree_insert_child_R(node_t *n, int elem) {
    /// inserisco il nuovo nodo con contenuto elem come figlio Right del nodo n
    n->R = node_new(elem);
}

int main() {
    node_t *root = node_new(1);
    tree_insert_child_L(root, 2);
    tree_insert_child_R(root, 3);
    tree_insert_child_L(root->L, 4);
    tree_insert_child_R(root->L, 5);
    tree_insert_child_L(root->R, 6);
    tree_insert_child_L(root->L->R, 7);
    tree_insert_child_R(root->L->R, 8);
    node_t *root2 = node_new(1);
    tree_insert_child_L(root2, 3);
    tree_insert_child_R(root2, 2);
    tree_insert_child_L(root2->R, 4);
    tree_insert_child_R(root2->R, 5);
    tree_insert_child_R(root2->L, 6);
    tree_insert_child_L(root2->R->R, 8);
    tree_insert_child_R(root2->R->R, 7);

    //controlla se gli alberi sono guali
    if(sameTree(root,root2)){
        cout<<"Gli alberi sono uguali"<<endl;
    }
    else cout<<"Gli alberi sono diversi"<<endl;

    cout<<isIsomorphic(root,root2);
    //controlla se gli alberi sono isomorfi
    if(isIsomorphic(root,root2)!=0) cout<<"I due alberi non sono isomorfi"<<endl;
    else cout<<"I due alberi sono isomorfi"<<endl;

    //tree_print(root);
    //cout<<endl;
    //tree_print(root2);
    print_tree(root, "tree.dot");
    print_tree(root2, "tree2.dot");
    return 0;
}