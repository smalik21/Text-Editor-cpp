#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

class Node {
    public:
    string data;
    Node* next;

    Node(string data) {     // constructor
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

        if(root == NULL) {      // insert line in an empty list
            root = new Node(line);
            return;
        }

        Node* root_ref = root;
        while(root_ref -> next != NULL) {   // traverse the whole list
            root_ref = root_ref -> next;
        }
        
        Node* temp = new Node(line);
        root_ref -> next = temp;    // insert the line at end
    }

    void add_line_at(Node* &root) {   // add a line at a particular index

        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        int line_no;
        cout << "Enter index to insert at: ";
        cin >> line_no;

        Node* temp = new Node(line);

        if(line_no == 1) {      // add node to the head of list
            temp -> next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;

        for(int i=1; i<line_no-1; i++) {       // traverse till the specified index is reached
            root_ref = root_ref -> next;    
        }

        temp -> next = root_ref -> next;    // insert the node
        root_ref -> next = temp;    
    }

    void add_line_at(Node* &root, int line_no) {   // add a line at given index

        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        Node* temp = new Node(line);

        if(line_no == 1) {      // add node to the head of list
            temp -> next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;

        for(int i=1; i<line_no-1; i++) {       // traverse till the specified index is reached
            root_ref = root_ref -> next;    
        }

        temp -> next = root_ref -> next;    // insert the node
        root_ref -> next = temp;    
    }

    void add_line_at(Node* &root, int line_no, string line) {   

        Node* temp = new Node(line);

        if(line_no == 1) {      // add node to the head of list
            temp -> next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;

        for(int i=1; i<line_no-1; i++) {       // traverse till the specified index is reached
            root_ref = root_ref -> next;    
        }

        temp -> next = root_ref -> next;    // insert the node
        root_ref -> next = temp;   
    }

    void replace_line(Node* &root) {    // replace a line 

        int line_no;
        cout << "Enter the line number to replace: ";
        cin >> line_no;
        cin.ignore();

        delete_line(root, line_no);     // delete the line at index
        add_line_at(root, line_no);     // replace it with a new line
    }

    void interchange_lines(Node* &root) {   // interchange two lines using their index

        int index1, index2;     // index of the lines to interchange
        cout << "Enter the index for line 1: ";
        cin >> index1;
        cout << "Enter the index for line 2: ";
        cin >> index2;

        Node* root_ref = root;
        for(int i=1; i<index1; i++) {
            root_ref = root_ref -> next;
        }
        string line1 = root_ref -> data;    // get text of line 1
        
        root_ref = root;
        for(int i=1; i<index2; i++) {
            root_ref = root_ref -> next;
        }
        string line2 = root_ref -> data;    // get text of line 2

        // insert the line at the other index
        add_line_at(root, index1, line2);
        delete_line(root, index1+1);
        add_line_at(root, index2, line1);
        delete_line(root, index2+1);
    }

    void delete_line(Node* &root) {     // delete a line whose index is given by the user

        int line_no;
        cout << "Enter line number to delete: ";
        cin >> line_no;
        
        if(line_no == 1) {      // delete node at the head of list
            Node* temp = root;
            root = root -> next;
            delete temp;        // free up space 
            return;
        }

        Node* root_ref = root;

        for(int i=1; i<line_no-1; i++) {       // traverse till the specified index is reached
            root_ref = root_ref -> next;    
        }

        Node* temp = root_ref -> next;
        root_ref -> next = temp -> next;
        delete temp;        // free up space
    }

    void delete_line(Node* &root, int line_no) {     // delete the line at given index
        
        if(line_no == 1) {      // delete node at the head of list
            Node* temp = root;
            root = root -> next;
            delete temp;        // free up space 
            return;
        }

        Node* root_ref = root;

        for(int i=1; i<line_no-1; i++) {       // traverse till the specified index is reached
            root_ref = root_ref -> next;    
        }

        Node* temp = root_ref -> next;
        root_ref -> next = temp -> next;
        delete temp;        // free up space
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
        else {
            cout << "File opened successfully." << endl;
        }

        while(getline(file, line)) {    // execute until file is read completely

            //getline(file, line);    // read a single line from file
            if(root == NULL) {
                root = new Node(line);      // head node
                continue;   
            }
            Node* root_ref = root;

            while(root_ref -> next != NULL) {   
                root_ref = root_ref -> next;    // traverse till the end of linked list
            }

            Node* temp = new Node(line);    
            root_ref -> next = temp;
        }
        

        file.close();   
    }   

    void save_file(Node* &root) {   // save the modified file

        ofstream file;
        file.open("sample.txt");    // open in output mode

        Node* root_ref = root;

        while(root_ref != NULL) {

            string line = root_ref -> data;

            file << line << endl;       // write data in the file
            root_ref = root_ref -> next;
        }
        cout << "File saved successfully." << endl;
        file.close();
    }

    void undo() {
        
    }

    void display(Node* root) {      // display the content of file
        cout << "Current text:" << endl;
        int i=0;
        while(root != NULL) {
            cout << ++i << "> ";    // display line number
            cout << root -> data << endl;
            root = root -> next;
        }
        cout << endl;
    }

    void begin(Node* &root) {     // contoller function

        open_file(root);

        int select;

        while(1) {

            cout << "Enter your Selection:" << endl;
            cout << "1. Insert line" << endl;
            cout << "2. Insert line at index" << endl; 
            cout << "3. Replace a line" << endl;
            cout << "4. Interchange two lines" << endl;
            cout << "5. Delete line" << endl;
            cout << "6. UNDO" << endl;
            cout << "7. Display text file" << endl;
            cout << "8. Save File" << endl;
            cout << "-1. Exit" << endl;
            cout << ">> ";

            cin >> select;
            cin.ignore();
            switch(select) 
            {
                case 1:
                    add_line(root);              
                    break;
                case 2:
                    add_line_at(root);                    
                    break;
                case 3:
                    replace_line(root);                   
                    break;
                case 4:
                    interchange_lines(root);             
                    break;
                case 5:
                    delete_line(root);                  
                    break;
                case 6:
                    undo();
                    break;
                case 7:
                    display(root);
                    break;
                case 8:
                    save_file(root);
                    break;
                case -1:
                    cout << "Editor exited...";
                    return;   
            }
        }
    }
};

int main() {

    Node* root = NULL;
    Editor a;

    a.begin(root);

    return 0;
}