#include <bits/stdc++.h>
using namespace std;
int pos = 0;
// username and password hash map
struct Username
{
    map<string, string> dict;
    void sam_insert()
    {
        dict.insert(pair<string, string>("john", "aloha"));
        dict.insert(pair<string, string>("kendrick", "lamar"));
        dict.insert(pair<string, string>("pedro", "hello"));
    }
    void insert()
    {
        string username;
        string password;
        cout << "Enter username: " << endl;
        cin >> username;
        cout << "Enter password: " << endl;
        cin >> password;
        dict.insert(pair<string, string>(username, password));
    }
    void password()
    {
        dict.insert(pair<string, string>("john", "aloha"));
        dict.insert(pair<string, string>("kendrick", "lamar"));
        dict.insert(pair<string, string>("pedro", "hello"));
        string username, password;
        cout << "Enter username: " << endl;
        cin >> username;
        cout << "Enter password: " << endl;
        cin >> password;
        // dict.insert(pair<string,string>(username,password));
        if (dict.find(username) != dict.end() && dict[username] == password)
        {
            cout << "Login Successfull!";
        }
        else
        {
            cout << "Invalid Credentials!!!";
            exit(0);
        }
    }
    void display_passmenu()
    {
        map<string, string>::iterator itr;
        cout << '\t' << "Name"
             << "\t"
             << "password" << '\n';
        for (itr = dict.begin(); itr != dict.end(); ++itr)
        {
            cout << '\t' << itr->first << '\t' << itr->second << '\n';
        }
    }
} ob1;

class Customer
{
private:
    string customer_name;
    string customer_id;
    float price;
    string mobileno;

public:
    Customer()
    {
    }

    Customer(string _customer_name, string _customer_id, float _price, string _mobileno);
    void set_customer_name(string cname);
    void set_customer_id(string ssno);
    void set_price(float total);
    void set_customer_mno(string mno);
    string get_customer_name();
    string get_customer_id();
    float get_price();
} ob4[30];

Customer ::Customer(string _customer_name, string _customer_id, float _price, string _mobileno)
{
    customer_name = _customer_name;
    customer_id = _customer_id;
    price = _price;
    mobileno = _mobileno;
}
void Customer ::set_customer_name(string cname)
{
    customer_name = cname;
}
void Customer ::set_customer_id(string ssno)
{
    customer_id = ssno;
}
void Customer ::set_price(float total)
{
    price = total;
}
void Customer ::set_customer_mno(string mno)
{
    mobileno = mno;
}
string Customer ::get_customer_name()
{
    return customer_name;
}
string Customer ::get_customer_id()
{
    return customer_id;
}
float Customer ::get_price()
{
    return price;
}

class Node
{
public:
    string key;
    Node *left;
    Node *right;
    int height;

    Customer customer_details;
};

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *newNode(string key, Customer &p)
{
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    node->customer_details = p;
    return (node);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, string key, Customer &p)
{
    if (node == NULL)
        return (newNode(key, p));

    if (key < node->key)
        node->left = insert(node->left, key, p);
    else if (key > node->key)
        node->right = insert(node->right, key, p);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void print_details(Node *root)
{
    cout << "DETAILS:\n";
    cout << "NAME: " << root->customer_details.get_customer_name() << endl;
    cout << "PRICE: Rs." << root->customer_details.get_price();
}

Node *search(Node *root, string key)
{
    if (root == NULL)
    {
        cout << "Not Available\n";
        return root;
    }
    if (root->key == key)
    {
        print_details(root);
        return root;
    }

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

Node *minValueNode(Node *node)
{
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, string key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Node *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *root = NULL;

void search_page()
{
    int ch = 1;
    char b;
    string name;
    while (ch)
    {
        cout << "\n1. Search\n";
        cout << "0. Exit\n";
        cout << "Enter Choice: ";
        cin >> ch;
        if (ch)
        {
            cout << "Enter name of Customer: ";
            cin >> name;
            search(root, name);
            cout << "\nDo u want to continue ";
            cin >> b;
            if (b == 'y')
            {
                return;
            }
        }
        else
            exit(0);
    }
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

class restaurantmenu
{
public:
    map<string, int> menu;
    void insertt()
    {
        menu.insert(pair<string, int>("pizza", 200));
        menu.insert(pair<string, int>("steak", 350));
        menu.insert(pair<string, int>("Burger", 250));
    }
    void insertmenu()
    {
        string item_name;
        int price;
        int flag = 1;
        do
        {
            cout << "Enter item name" << endl;
            cin >> item_name;
            cout << "Enter price of the item" << endl;
            cin >> price;
            menu.insert(pair<string, int>(item_name, price));
            cout << "TO EXIT Enter 0";
            cin >> flag;
        } while (flag);
    }

    void displmenu()
    {
        map<string, int>::iterator itr;
        for (itr = menu.begin(); itr != menu.end(); ++itr)
        {
            cout << '\t' << itr->first << '\t' << itr->second << '\n';
        }
    }
    void modifymenu()
    {
        char m_flag = 'y';
        map<string, int>::iterator itr;
        string ch_key;
        int change_prise;
        while (m_flag != 'n')
        {
            cout << "Enter the key or menu item's price to be changed" << endl;
            cin >> ch_key;
            for (itr = menu.begin(); itr != menu.end(); ++itr)
            {
                if (itr->first == ch_key)
                {
                    cout << "Enter the new prise of the item you want to change";
                    cin >> change_prise;
                    itr->second = change_prise;
                }
                else
                {
                    continue;
                }
            }
            cout << "want to continue to modify the menu items? y/n";
            cin >> m_flag;
        }
    }
    void totalamount()
    {
        int total = 0;
        char f2 = 'a';
        string food;
        int qty;
        while (f2 != 'n')
        {
            displmenu();
            cout << "Enter your order:";
            cin >> food;
            cout << "Enter Qty:";
            cin >> qty;
            auto it = menu.find(food);
            total += qty * (it->second);
            cout << "add next item:(y/n)";
            cin >> f2;
        }
        cout << "Bill amt is:" << total << endl;
        int f3;
        cout << "--------Do you want place order,1.Place order, 2.EXIT---------------";
        cin >> f3;
        if (f3 == 1)
        {
            placeorder(total);
        }
        else
        {
            return;
        }
    }
    void placeorder(int total)
    {
        string mno, cname;
        string ssno;

        cout << "Enter customer name:";
        cin >> cname;
        cout << "Enter id:";
        cin >> ssno;
        cout << "Enter mno:";
        cin >> mno;
        pos = pos + 1;
        // ob4[pos](cname,ssno,total,mno);
        ob4[pos].set_customer_name(cname);
        ob4[pos].set_customer_id(ssno);
        ob4[pos].set_price(total);
        ob4[pos].set_customer_mno(mno);
        root = insert(root, cname, ob4[pos]);
        // check=ob4[pos].get_customer_name();
        // cout<<check;
    }
} ob2, ob3;

int main()
{
    cout << "--------------------------------RESTAURANT MANAGEMENT SYSTEM-----------------------------------" << endl;
    int choice;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "_____________________________________1.RESTAURANT ADMIN___________________________________________" << endl;
    cout << "___________________________________2.RESTAURANT CUSTOMER________________________________________" << endl;
    char f1 = 'a';
    while (f1 != 'n')
    {
        cout << "ENTER YOUR CHOICE (1.Admin  2.Customer):";
        cin >> choice;
        switch (choice)
        {
        case 1:
            int a_flag;
            ob1.sam_insert();
            cout << "RESTAURANT ADMIN CODE HERE";
            cout << "\n 1.TO Insert new items in Menu";
            cout << "\n 2.TO Display menu";
            cout << "\n 3.To modify the given menu";
            cout << "\n 4.Search";
            cout << "\n 5.To Display the contents of AVL TREE";
            cout << "\n 6.To Display the contents of Password Hash map";
            cout << "\n 7.Press 7 to exit or any other number";
            cout << "\nEnter Choice:";
            cin >> a_flag;
            ob2.insertt();
            if (a_flag == 1)
            {
                ob2.insertmenu();
            }
            else if (a_flag == 2)
            {
                ob2.displmenu();
            }
            else if (a_flag == 3)
            {
                ob2.modifymenu();
            }
            else if (a_flag == 4)
            {
                search_page();
            }
            else if (a_flag == 5)
            {
                preorder(root);
            }
            else if (a_flag == 6)
            {
                ob1.display_passmenu();
            }
            else
            {
                cout << "Wrong choice!!\n";
            }
            cout << "want to continue? y/n:";
            cin >> f1;
            break;
        case 2:
            int choiceu;
            cout << "1.REGISTER" << endl;
            cout << "2.EXISTING USER" << endl;
            cout << "ENTER CHOICE:";
            cin >> choiceu;
            if (choiceu == 1)
            {
                char ch = 'y';
                ob1.insert();
                cout << "Now enter username and password" << endl;
                ob1.password();
                ob2.insertt();
                cout << "\nDo you want to order food?(y/n):";
                cin >> ch;
                if (ch == 'y')
                {
                    ob2.totalamount();
                }
            }
            else if (choiceu == 2)
            {
                char ch = 'y';
                ob1.password();
                ob2.insertt();
                cout << "\nDo you want to order food?(y/n):";
                cin >> ch;
                if (ch == 'y')
                {
                    ob2.totalamount();
                }
            }
            else
            {
                cout << "wrong choice";
            }
            cout << "want to continue? y/n:";
            cin >> f1;
            break;

        default:
            cout << "PLEASE ENTER A VALID CHOICE";
            cout << "want to continue? y/n:";
            cin >> f1;
            break;
        }
    }

    return 0;
}
