/*
    Binary Search Tree Implementation
    Author: Giannakouris - Salalidis Victor
    E-mail: victorasgs@gmai.com
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct data node_data;
typedef struct binary_tree binary_tree;

binary_tree* init_bt();
node *findMax(node* root);
node* bt_search(char *query, node *root);
node* create_btree();
void print_node(node* n);
void add(node* leaf, node* root);
void inorder(node* bt);
void overwrite(node* A, node* B);
void add_node(char *id, char *name,
    float data1, int data2,
    float data3, binary_tree* bt);

//Binary Tree Node
struct node{
    node_data *data;
    node *parent;
    node *left;
    node *right;
};

//Sample Data of a Binary Tree Node
struct data{
    char id[20];
    char name[100];
    float data1;
    int data2;
    float data3;
};

//Binary Tree
struct binary_tree{
    node *root;
};

//Binary Tree Initialization
binary_tree* init_bt(){
    binary_tree* bt = (binary_tree*)malloc(sizeof(binary_tree));
    bt->root = NULL;
    return bt;
}

//Binary Tree Print Method
void inorder(node* bt){
    if (bt != NULL){
        inorder(bt->left);
        print_node(bt);
        inorder(bt->right);
    }
}

//Add Node to Binary Tree (Client Side)
void add_node(char *id, char *name,
    float data1, int data2,
    float data3, binary_tree* bt){

    //Node Initialization
    node* leaf = (node*)malloc(sizeof(node));
    leaf->left = NULL;
    leaf->right= NULL;

    //Set Node Data
    leaf->data = (node_data*)malloc(sizeof(node_data));
    strcpy(leaf->data->id, id);
    strcpy(leaf->data->name, name);
    leaf->data->data1 = data1;
    leaf->data->data3 = data3;
    leaf->data->data2 = data2;

    if (bt->root == NULL){
        bt->root = leaf;
    }
    else add(leaf, bt->root);
}

//Add Node to Binary Tree (Code Side)
void add(node* leaf, node* root){

    if ( strcmp(leaf->data->id, root->data->id) == -1 ){
        if (root->left == NULL){
            root->left = leaf;
            leaf->parent = root;
        }
        else{
            add(leaf, root->left);
        }
    }
    else{
        if (root->right == NULL){
            root->right = leaf;
            leaf->parent = root;
        }
        else{
            add(leaf, root->right);
        }
    }

}

//Search in the binary tree
node* bt_search(char *query, node *root){
    if (root == NULL){
        printf("\nRecord not found\n\n");
        return NULL;
    }
    if (strcmp(root->data->id, query) == 0){
        return root;
    }
    else{
        if ( strcmp(query, root->data->id) == -1 ){
            bt_search(query, root->left);
        }
        else{
            bt_search(query, root->right);
        }
    }
}

//Element deletion
void delete_element(char *query, node *root){
    if (root == NULL){
        printf("Empty Tree\n");
        return;
    }

    node* del = bt_search(query, root);
    node* tmp;

    if (del == NULL) return;

    //The node has two children
    if (del->left!=NULL && del->right!=NULL){
        tmp = findMax(del->left);
        overwrite(del, tmp);

        //Checking if the current node is the left or right parent's child
        if (tmp->parent->left == tmp) tmp->parent->left=NULL;
        else tmp->parent->right = NULL;
        free(tmp->data);
        free(tmp);
    }
    //The node has not any child
    else if (del->left==NULL && del->right==NULL){

        //Checking if the current node is the left or right parent's child
        if (del->parent->left == del) del->parent->left=NULL;
        else del->parent->right = NULL;
        free(del->data);
        free(del);
    }
    //The node has one child
    else{
        if (del->left == NULL){
            tmp = del->right;
            del->right = NULL;
        }
        else if (del->right == NULL){
            tmp = del->left;
            del->left = NULL;
        }
        overwrite(del, tmp);
        del->left = tmp->left;
        del->right = tmp->right;
        free(tmp->data);
        free(tmp);
    }
}

//Find Max Value(ID) in Binary Tree
node *findMax(node* root){
    if (root == NULL){
        return NULL;
    }
    if (root->right == NULL){
        return root;
    }
}

//Ovewrite the node A with the node B
void overwrite(node* A, node* B){
    strcpy(A->data->id,B->data->id);
    strcpy(A->data->name, B->data->name);
    A->data->data1 = B->data->data1;
    A->data->data3 = B->data->data3;
    A->data->data2 = B->data->data2;
}

//Full print of the node
void print_node(node* n){
    printf("%s -- %s -- %f -- %d -- %f\n",
        n->data->id, n->data->name,
        n->data->data1, n->data->data2,
        n->data->data3);
}

