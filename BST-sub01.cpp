#include <iostream>

using namespace std;

int maximum;

class TreeNode{
public:
    // Pointer to the left child
    //  Initialised to nullptr (this syntax is a new C++11 feature)
    TreeNode* left = nullptr;
    // Pointer to the right child
    //  Initialised to nullptr (this syntax is a new C++11 feature)
    TreeNode* right = nullptr;

    // Value in the node
    int value;

    // Constructor, sets the value
    TreeNode(int v) : value(v) {}
    // Destructor, nifty trick to recursively delete all the nodes
    //  be careful though, when you delete just a single node, make
    //  sure that you set left and right = nullptr first
    ~TreeNode() {
        delete left;
        delete right;
    }
};

class Tree{
private:
    TreeNode* root = nullptr; //like head pointer

public:
    // These functions do the actual work
    void insert(int v, TreeNode* &subtree){ //value and tree it needs to be added in to
        if(subtree == nullptr){ //if node is null we can place new node there                                            
           subtree = new TreeNode(v); 
        }else if(v < subtree->value){ //if it lies on left call function recursively
            insert(v, subtree->left);
        }else{
            insert(v, subtree->right); //if it lies on right call function recursively
        }
    }

    void preOrderTraversal(TreeNode* subtree) const{ //pre-> value then left then right
        if(subtree!=nullptr){
        cout << subtree->value << ' '; //returns value then space

        if(subtree->left!=nullptr){
            preOrderTraversal(subtree->left); //calls function recursively
        }
        if(subtree->right!=nullptr){
            preOrderTraversal(subtree->right); //calls function recursively
        }
        }
    }

    void inOrderTraversal(TreeNode* subtree) const{ //left -> value -> right
        if(subtree!=nullptr){
            if(subtree->left!=nullptr){
                inOrderTraversal(subtree->left);
            }
            cout << subtree->value << ' ';
            if(subtree->right!=nullptr){
                inOrderTraversal(subtree->right);
            }
        }
    }

    void postOrderTraversal(TreeNode* subtree) const{
    
        if(subtree!=nullptr){
            if(subtree->left!=nullptr){
                postOrderTraversal(subtree->left);
            }
            if(subtree->right!=nullptr){
                postOrderTraversal(subtree->right);
            }
            cout << subtree->value << ' ';
        }
    }

    int min(TreeNode* subtree) const{
        TreeNode * tmp = root;
        while(tmp->left!= nullptr){ //keep going left till null is encountered
            tmp=tmp->left;
        }
        return tmp->value;
    }
    int max(TreeNode* subtree) const{
        TreeNode * tmp = root;
        while(tmp->right!= nullptr){ //keep going right till null is encountered
            tmp=tmp->right;
        }
        return tmp->value;
    }
    bool contains(int value, TreeNode* subtree) const{
        if(value == subtree->value){ //if value is subtree value return true
            return true;
        }
        else if(value<subtree->value){ //lies on left
            if(subtree->left==nullptr){ //left is nullptr that means the value isnt even here
                return false;
            }
            else{
                contains(value, subtree->left); //calls function recursively essentially says return contains()
            }
        }
        else if(value>subtree->value){
            if(subtree->right==nullptr){ //right is nullptr that means value isnt here 
                return false;
            }
            else{
                contains(value, subtree->right); //returns bool
            }
        }
    }
    void remove(int value, TreeNode* &subtree){ //pointer to memory address holding that pointer
       // remove a node from the tree with the given value
        if (subtree == nullptr)
        {
            return;
        }
        else if (value < subtree->value)
        {
            remove(value, subtree->left);
        }
        else if (value > subtree->value)
        {
            remove(value, subtree->right);
        }
        else
        {
            // We found the node to remove
            //  Case 1: No children
            if (subtree->left == nullptr && subtree->right == nullptr)
            {
                delete subtree;
                subtree = nullptr;
            }
            //  Case 2: One child
            else if (subtree->left == nullptr)
            {
                TreeNode *oldNode = subtree;
                subtree = subtree->right;
                oldNode->right = nullptr;
                delete oldNode;
            }
            else if (subtree->right == nullptr)
            {
                TreeNode *oldNode = subtree;
                subtree = subtree->left;
                oldNode->left = nullptr;
                delete oldNode;
            }
            //  Case 3: Two children
            else
            {
                // Find the smallest value in the right subtree
                subtree->value = min(subtree->right);
                // Remove the node that contained that value
                remove(subtree->value, subtree->right);
            }
        }
    }
    int maximum(int i, int j) const{
        if(i>j){
            return i;
        }
        else{
            return j;
        }
    }

    int height(TreeNode* subtree) const{
        if(subtree==nullptr){
            return 0;
        }
        else{
            int left = height(subtree->left);
            int right = height(subtree->right);
            int h;
            if(left>right){
                h = 1 + left;
            }
            else{
                h = 1+ right;
            }
            return h; 
        }
    }
    
    int diameter(TreeNode* subtree) const{
        int finaldiameter;
        if(subtree==nullptr){
            return 0;
        }
        else{
            int lheight = height(subtree->left);
            int rheight = height(subtree->right);
            int ldiameter = diameter(subtree->left);
            int rdiameter = diameter(subtree->right);
            finaldiameter = maximum(lheight+rheight+1, maximum(ldiameter, rdiameter));
        }
        return finaldiameter;
    }

    void deleteleaves(TreeNode* subtree) const{
        if(subtree == nullptr){
            return;
        }
        else{

        }
    }

    void insert(int value){
        insert(value, root);
    }
    int maximum(int i, int j){
        return maximum(i,j);
    }
    void preOrderTraversal(){
        preOrderTraversal(root);
        cout << endl;
    }
    void inOrderTraversal(){
        inOrderTraversal(root);
        cout << endl;
    }
    void postOrderTraversal(){
        postOrderTraversal(root);
        cout << endl;
    }
    void diameter(){
        cout << diameter(root) << endl;
    }
    int min(){
        return min(root);
    }
    int max(){
        return max(root);
    }
    bool contains(int value){
        return contains(value, root);
    }
    void remove(int value){
        remove(value, root);
    }
    void deleteleaves(){
        deleteleaves(root);
    }
    ~Tree(){
        // This ends up deleting all the nodes recursively.
        delete root;
    }
};

int main(){
    Tree t;
    int value;
    // Sample code to read and construct the tree.
    while(cin >> value && value != -1){
        t.insert(value);
    }
    while(cin >> value && value != -1){
        t.remove(value);
        t.preOrderTraversal();
        t.inOrderTraversal();
        t.postOrderTraversal();
    }
    

    // Do some stuff...

}