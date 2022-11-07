#include <iostream>
#include <fstream>
using namespace std;

class Node {
    public:
    string data;
    Node* next;

    Node(string data) {
        this -> data = data;
        this -> next = NULL;
    }
};

class Editor {
    
    public:
    void add_line(Node* &root) {    // add a user given line to the end of text
    
        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');       // input text until enter is pressed

        if(root == NULL) {
            root = new Node(line);
            return;
        }

        Node* root_ref = root;
        while(root_ref -> next != NULL) {
            root_ref = root_ref -> next;
        }
        
        Node* temp = new Node(line);
        root_ref -> next = temp;
    }

    void add_line_at(Node* &root) {   // add a line at a particular index

        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        int line_no;
        cout << "Enter index to insert at: ";
        cin >> line_no;

        Node* temp = new Node(line);

        if(line_no == 0) {
            temp -> next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;

        for(int i=1; i<line_no-1; i++) {
            root_ref = root_ref -> next;
        }

        temp -> next = root_ref -> next;
        root_ref -> next = temp;
    }

    void delete_line(Node* &root) {

    }

    void open_file(Node* &root) {   // read a file and return the head of linked list

        ifstream file;      // open file in read mode
        string line;

        file.open("sample.txt");    
        file.seekg(0, ios::beg);       // set the pointer to the start of file

        if(!file) {
            cout << "File couldn't open successfully." << endl;
            return;
        }

        Node* root_ref = NULL;
        Node* temp = NULL;

        while(getline(file, line)) {    // execute until file is read completely

            //getline(file, line);    // read a single line from file
            if(root == NULL) {
                root = new Node(line);      // head node
                continue;   
            }
            root_ref = root;

            while(root_ref -> next != NULL) {   
                root_ref = root_ref -> next;    // traverse till the end of linked list
            }

            temp = new Node(line);    
            root_ref -> next = temp;
        }
        if(sizeof(line) == 0) {
            root_ref -> next = NULL;
            delete temp;
        }

        file.close();   
    }   

    void save_file(Node* &root) {   // save the modified file

        ofstream file;
        file.open("sample.txt");

        Node* root_ref = root;

        while(root_ref != NULL) {

            string line = root_ref -> data;

            file << line << endl;
            root_ref = root_ref -> next;
        }

        file.close();
    }

    void begin() {      
        

    }

    void display(Node* root) {
        cout << "Current text:" << endl;
        int i=0;
        while(root != NULL) {
            cout << ++i << "> ";    // display line number
            cout << root -> data << endl;
            root = root -> next;
        }
        cout << endl;
    }
};

int main() {

    Node* root = NULL;
    Editor a;
    a.open_file(root);
    a.display(root);
    a.add_line(root);
    a.display(root);
    a.save_file(root);
}