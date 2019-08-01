//bollu

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class AVLTree
{
private:
    struct Node
    {
        int partnum;
        string description;
        int qty;
        double price;
        Node* left;
        Node* right;
    } *root;
    void clear(Node*&);
    int height(Node*);
    void rotateRight(Node*&);
    void rotateLeft(Node*&);
    void rotateRightLeft(Node*&);
    void rotateLeftRight(Node*&);
    int difference(Node*);
    void balance(Node*&);
    void append(Node*&, int, int,double, string);
    void remove(Node*&, int);
    string getOutOfStock(Node*);
    string getPart(Node*,int);
public:
    AVLTree();
    ~AVLTree();
    void clear();
    void append(int,int,double,string);
    void remove(int);
    string getOutOfStock();
    string getPart(int);
    
    
};

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{
    clear(root);
}

void AVLTree::clear()
{
    clear(root);
    root = nullptr;
}

void AVLTree::clear(Node*& r)
{
    if(r != nullptr)
    {
        clear(r->left);
        clear(r->right);
        delete r;
    }
}

int AVLTree::height(Node* r)
{
    if(r == nullptr)
    {
        return 0;
    }
    else
    {
        int L;
        int R;
        L = height(r->left);
        R = height(r->right);
        if(L > R)
        {
            return L + 1;
        }
        else
            return R + 1;
    }
    
}

void AVLTree::rotateRight(Node*& r)
{
    Node* p;
    p = r->left;
    r->left = p->right;
    p->right = r;
    r = p;
}

void AVLTree::rotateLeft(Node*& r)
{
    Node* p;
    p = r->right;
    r->right = p->left;
    p->left = r;
    r = p;
}

void AVLTree::rotateRightLeft(Node*& r)
{
    rotateRight(r->right);
    rotateLeft(r);
}

void AVLTree::rotateLeftRight(Node*& r)
{
    rotateLeft(r->left);
    rotateRight(r);
}

int AVLTree::difference(Node* r)
{
    int bf;
    bf = height(r->right) - height(r->left);
    return(bf);
}

void AVLTree::balance(Node*& r)
{
    if(difference(r) == -2)
    {
        if(difference(r) >= -1)
        {
            rotateRight(r);
        }
        else
        {
            rotateLeftRight(r);
        }
    }
    else if(difference(r) == 2)
    {
        if(difference(r->right) >= 1)
        {
            rotateLeft(r);
        }
        rotateRightLeft(r);
    }
}

void AVLTree::append(int num, int quantity, double price, string desc)
{
    append(root, num, quantity, price, desc);
}

void AVLTree::append(Node*& r, int num, int quantity, double price, string desc)
{
    
    if(r == nullptr)
    {
        r = new Node;
        r->partnum = num;
        r->qty = quantity;
        r->price = price;
        r->description = desc;
        r->left = nullptr;
        r->right = nullptr;
    }
    else if(num < r->partnum)
    {
        append(r->left, num, quantity, price, desc);
        balance(r);
    }
    else
    {
        append(r->right, num, quantity, price, desc);
        balance(r);
    }
    
    
}

void AVLTree::remove(int num)
{
    remove(root,num);
};

void AVLTree::remove(Node*& r, int num)
{
    if(r == nullptr)
    {
        return;
    }
    else if(num < r->partnum)
    {
        remove(r->left,num);
    }
    else if(num > r->partnum)
    {
        remove(r->right,num);
    }
    else
    {
        Node* p;
        
        if(r->left == nullptr && r->right == nullptr)
        {
            delete r;
            r = nullptr;
        }
        else if(r->left != nullptr && r->right == nullptr)
        {
            p = r;
            r = r->left;
            delete p;
        }
        else if(r->left == nullptr && r->right != nullptr)
        {
            p = r;
            r = r->right;
            delete p;
        }
        else
        {
            p = r->right;
            while(p->left != nullptr)
            {
                p = p->left;
            }
            p->left = r->left;
            p = r;
            r = r->right;
            delete p;
        }
        
    }
    
}

string AVLTree::getOutOfStock()
{
    return (getOutOfStock(root));
}

string AVLTree::getOutOfStock(Node* r)
{
    if(r == nullptr)
    {
        return " ";
    }
    string ss = " ";
    if(r->qty == 0)
    {
        ss = ss + to_string(r->partnum) + ", " + r->description + ", " + to_string(r->price) + ", " + to_string(r->qty) + "\n" ;
    }
    return ss + getOutOfStock(r->left) + getOutOfStock(r->right);
    
    
}

string AVLTree::getPart(int num)
{
    return getPart(root, num);
}

string AVLTree::getPart(Node* r, int num)
{
    if(r != nullptr)
    {
        
        if(r->partnum == num)
        {
            
            return to_string(r->partnum) + "\n" + r->description + "\n" + to_string(r->price) + "\n" + to_string(r->qty) + "\n" ;
        }
        else if(num < r->partnum)
        {
            return getPart(r->left, num);
        }
        else if(num > r->partnum)
        {
            return getPart(r->right, num);
        }
        
    }
    return "OUT OF STOCK";
}

int main()
{
    AVLTree attempt;
    char choice;
    bool menu = true;
    while(menu)
    {
        cout << "MENU" << endl;
        cout << "(A)dd a part" << endl;
        cout << "(R)emove a part" << endl;
        cout << "(S)earch for a part" << endl;
        cout << "(O)ut of Stock" << endl;
        cout << "(Q)uit" << endl;
        cout << "[Enter Your Choice] >> " << endl;
        cin >> choice;
        cout << endl;
        switch(choice)
        {
            case 'A':
            case 'a':
            {
                int num;
                int quantity;
                double price;
                string description;
                cin.ignore();
                cout << "\nEnter part description: ";
                getline(cin, description);
                cout << "\nEnter the price: ";
                cin >> price;
                cout << "\nEnter the part number: ";
                cin >> num;
                cout << "\nEnter the qauntity on hand: ";
                cin >> quantity;
                attempt.append(num, quantity, price, description);
                break;
            }
            case 'R':
            case 'r':
            {
                int num;
                cout << "Enter part number to remove: ";
                cin >> num;
                cout << endl;
                attempt.remove(num);
                break;
            }
            case 'S':
            case 's':
            {
                int num;
                cout << "Enter part number to search for: ";
                cin >> num;
                cout << endl;
                cout<<attempt.getPart(num);
                break;
            }
            case 'O':
            case 'o':
            {
                cout << "The following items are out of stock" << endl;
                cout<<attempt.getOutOfStock();
                break;
            }
                
            case 'Q':
            case 'q':
            {
                menu = false;
                cout << "ciao" << endl;
                break;
            }
        }
    }
    
    
}
