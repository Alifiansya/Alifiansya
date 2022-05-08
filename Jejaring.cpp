#include <iostream>
using namespace std;

template <typename T>
struct Stack
{
    struct Node
    {
        T data;
        Node *next;
        Node(T d, Node *nx)
        {
            data = d;
            next = nx;
        }
    };
    
    Node *top = NULL;
    int size = 0;

    bool empty()
    {
        return top == NULL;
    }

    void push(T data)
    {
        Node *tmp = new Node(data, NULL);
        if(empty()) top = tmp;
        else
        {
            tmp -> next = top;
            top = tmp;
        }
        size++;
    }

    void pop()
    {
        if(!empty())
        {
            Node *tmp = top;
            top = top -> next;
            delete tmp;
            size--;
        }
    }

    T peek(){
        return top -> data;
    }

    void clear()
    {
        while(!empty())
        {
            pop();
        }
    }
};

template <typename T>
struct LinkedList
{
    struct Node
    {
        T data;
        Node *next = NULL;
        Node(T dt){
            data = dt;
        }
    };
    
    Node *head = NULL;
    int size = 0;

    bool empty()
    {
        return head == NULL;
    }

    void push(T data)
    {
        Node *tmp = new Node(data);
        if(empty())
            head = tmp;
        else
        {
            tmp -> next = head;
            head = tmp;
        }
        size++;
    }

    void pop()
    {
        if(empty()) throw "LL empty! cannot pop.";
        Node *tmp = head;
        head = head -> next;
        delete tmp;
        size--;
    }

    void deleteDupe()
    {
        Node* hlp;
        for(Node *p = head; p != NULL; p = p -> next)
        {
            hlp = p;
            for(Node *q = p; q != NULL;)
            {
                if(p != q && (p -> data == q -> data))
                {
                    hlp -> next = q -> next;
                    delete q;
                    q = hlp -> next;
                }
                else
                {
                    hlp = q;
                    q = q -> next;
                }
            }
        }
    }

    Node *nodeAt(int index)
    {
        if(index > size || index < 0) throw "Index not found 404!";
        Node *p = head;
        for(int i = 0; i < size-index-1; i++) 
            p = p -> next;
        return p;
    }
    
    T at(int index)
    {
        if(index > size || index < 0) throw "Index not found 404!";
        Node *p = head;
        for(int i = 0; i < size-index-1; i++) 
            p = p -> next;
        return p -> data;
    }

    int findIndex(T data)
    {
        if(empty()) return -1;
        int i = 0;
        for(Node *p = head; p -> data != data; p = p -> next)
        {
            i++;
            if(p == NULL) return -1;
        }
        return size-1 - i;
    }

    T findMax()
    {
        if(empty()) throw "List empty! cannot find max.";
        Node *p = head;
        for(Node *q = head; q != NULL; q = q -> next)
        {
            if(p -> data < q -> data) p = q;
        }
        return p -> data;
    }

    T findMin()
    {
        if(empty()) throw "List empty! cannot find min.";
        Node *p = head;
        for(Node *q = head; q != NULL; q = q -> next)
        {
            if(p -> data > q -> data) p = q;
        }
        return p -> data;
    }

    void strSortList()
    {
        string tmp;
        for(Node *p = head; p != NULL; p = p -> next)
            for(Node *q = p; q != NULL; q = q -> next)
                if(p -> data.compare(q -> data) > 0)
                {
                    tmp = p -> data;
                    p -> data = q -> data;
                    q -> data = tmp;
                }
    }

    int getMemSize()
    {
        int memSize = 0;
        for(Node *p = head; p != NULL; p = p -> next)
            memSize += sizeof(p -> data);
        return memSize;
    }

    bool isSame(LinkedList<T> &data)
    {
        for(Node *p = head; p != NULL; p = p -> next)
            for(Node *q = data.head; q != NULL; q = q -> next)
                if(p -> data != q -> data)
                    return false;
        return true;
    }

    void concat(LinkedList<T> &data)
    {
        for(Node *p = data.head; p != NULL; p = p -> next)
            push(p -> data);
    }

    void clear()
    {
        while(!empty())
        {
            pop();
        }
    }

    void print()
    {
        for(Node *p = head; p != NULL; p = p -> next)
            cout << p -> data << "->";
        cout << endl;
    }
};


class Graph
{
    struct Vertex
    {
        string username;
        string minat[3];
        Vertex(string un, string m1, string m2, string m3)
        {
            username = un;
            minat[0] = m1;
            minat[1] = m2;
            minat[2] = m3;
        }
    };
    LinkedList<Vertex*> users;
    LinkedList<LinkedList<int>*> adjMatrix;
    LinkedList<int>* edges = new LinkedList<int>;
    int count = 0;

    public:
    void addVertex(string w, string x, string y, string z)
    {
        Vertex *p = new Vertex(w, x, y, z);
        users.push(p);
        edges->push(0);
        adjMatrix.push(edges);
        edges = new LinkedList<int>;
        count++;

        for(int i = 0; i < adjMatrix.size; i++)
        {
            for(int j = adjMatrix.at(i)->size; j < count; j++)
                adjMatrix.at(i)->push(0);
            edges->push(0);
        }       
    }

    int findIndex(string username)
    {  
        int index;
        for(index = 0; users.at(index) -> username != username; index++);
        return index;
    }

    void connect(string from, string to)
    {
        adjMatrix.at(findIndex(from)) -> nodeAt(findIndex(to)) -> data = 1;
    }

    int inEdgesCount(int index)
    {
        int edgeCount = 0;
        for(int i = 0; i < count; i++)
        {
            if(adjMatrix.at(i)->at(index) == 1)
                edgeCount++;
        }
        return edgeCount;
    }

    int outEdgesCount(int index)
    {
        int edgeCount = 0;
        for(int i = 0; i < count; i++)
        {
            if(adjMatrix.at(index)->at(i) == 1)
                edgeCount++;
        }
        return edgeCount;
    }

    string mostFollowed()
    {
        LinkedList<int> ll;
        for(int i = 0; i < count; i++)
            ll.push(inEdgesCount(i));
        return users.at(ll.findIndex(ll.findMax()))->username;
    }

// ==================================== TST ====================================
    int minRetweetCount(int from, int to)
    {
        LinkedList<int> data = findRetweet(from, to);
        if(from == to && adjMatrix.at(from)->at(to) == 1)
            return 0;
        if(data.empty()) 
            return -1;
        return data.findMin();
    }

    LinkedList<int> findNeighbours(int index)
    {
        LinkedList<int> neighbours;
        for(int i = 0; i < count; i++)
        {
            if(adjMatrix.at(index)->at(i) == 1)
                neighbours.push(i);
        }
        return neighbours;
    }

    LinkedList<int> findRetweet(int src, int dst)
    {
        int rCount = -1;
        LinkedList<bool> checked;
        LinkedList<int> steps;
        for(int i = 0; i < count; i++)
            checked.push(false);
        retweet_util(rCount, src, dst, checked, findNeighbours(src), steps);
        return steps;
    }

    void retweet_util(int &rCount, int from, int to, LinkedList<bool>& checked, LinkedList<int> neighbours, LinkedList<int> &steps)
    {
        checked.nodeAt(from) -> data = true;
        if (from == to) {
            steps.push(rCount);
        }
        else 
            for(int i = 0; i < neighbours.size; i++)
            {
                int nb = neighbours.at(i);
                if(!checked.at(nb))
                    retweet_util(++rCount, nb, to, checked, findNeighbours(nb), steps);
            }
                
        --rCount;
        checked.nodeAt(from) -> data = false;
    }

//=================================================================================
//===================================== FIND GROUP ================================
    int getNumGroup()
    {
        LinkedList<LinkedList<int>> groups;
        LinkedList<int> grouped;
        LinkedList<int> users;

        for(int i = 0; i < count; i++)
        {
            if(grouped.findIndex(i) == -1)
            {
                cout << i;
                

                dfs(i, 0, users);
                dfs(i, 1, users);
                users.print();
                users.deleteDupe();
                grouped.concat(users);
                groups.push(users);
                users.clear();
            }     
        }

        return groups.size;
    }

    int unchekedUsers(int v, bool checked[])
    {
        for(int j=0; j<count; j++)
            if(adjMatrix.at(v)->at(j) !=0 && checked[j]==false)
                return j;
        return -1;
    }

    int rUnchekedUsers(int v, bool checked[])
    {
        for(int j=0; j<count; j++)
            if(adjMatrix.at(j)->at(v) !=0 && checked[j]==false)
                return j;
        return -1;
    }

    void dfs(int start, bool reverse, LinkedList<int> &users) // depth-first search
    {  
        bool check[count] = {false};
        Stack<int> st;
        // cout << users.at(v)->username; // display it
        users.push(start);

        st.push(start); // push it
        while( !st.empty() ) // until stack empty,
        {
            int v;
            if(!reverse)
                v = unchekedUsers(st.peek(), check);
            else
                v = rUnchekedUsers(st.peek(), check);
            if(v == -1) // if no such vertex,
                st.pop();
            else // if it exists,
            {
                check[v] = true;
                // cout << users.at(v)->username; // display it
                users.push(v);
                st.push(v); // push it
            }
        } // end while
    }

//==================================================================================
    void printAdjMatrix()
    {   
        string uname;
        std::cout << "[] |  ";
        for(int i = 0; i < count; i++){
            uname = users.at(i) -> username;
            std:: cout << uname[0];
            std::cout << "   ";
        }
        std::cout << std::endl; 
        
        for(int i = 0; i < count; i++)
            std::cout << "----";
        std::cout << "----";
        // std::cout << "";
        std::cout << std::endl;
        for(int i = 0; i < count; i++)
        {
            std::cout << users.at(i) -> username[0] << "  |  ";
            for(int j = 0; j < count; j++)
            {
                std::cout << adjMatrix.at(i)->at(j) << "   ";
            }
            std::cout << std::endl << std::endl;
        }
    }

};

int main()
{
    Graph g;
    g.addVertex("graphy", "meme", "buku", "sas");//v1
    g.addVertex("mario", "meme", "buku", "sas");//v2
    g.addVertex("zaka", "meme", "buku", "sas");//v3
    g.addVertex("rozi", "meme", "buku", "sas");//v4
    g.addVertex("hadiyan", "meme", "buku", "sas");//v5
    g.addVertex("yaya", "meme", "buku", "sas");//v6
    g.addVertex("heru", "meme", "buku", "sas");//v1

    g.addVertex("wini", "meme", "buku", "sas");//v2
    g.addVertex("biti", "meme", "buku", "sas");//v3
    g.addVertex("tini", "meme", "buku", "sas");//v4

    g.addVertex("dolly", "meme", "buku", "sas");//v5
    g.addVertex("bolly", "meme", "buku", "sas");//v6
    try{
        g.connect("graphy", "mario");
        g.connect("mario", "zaka");
        g.connect("mario", "rozi");
        g.connect("heru", "yaya");
        g.connect("yaya", "heru");
        g.connect("heru", "rozi");
        g.connect("yaya", "rozi");
        g.connect("zaka", "rozi");
        g.connect("zaka", "hadiyan");
        g.connect("hadiyan", "zaka");

        g.connect("biti", "wini");
        g.connect("wini", "biti");
        g.connect("biti", "tini");
        g.connect("tini", "wini");

        g.connect("dolly", "bolly");
        g.connect("bolly", "dolly");
        
        g.printAdjMatrix();
        cout << g.mostFollowed() << endl;
        // g.count_paths(g.findIndex("graphy"), g.findIndex("hadiyan"), 6).print();
        cout << g.minRetweetCount(g.findIndex("graphy"), g.findIndex("hadiyan"));
        cout << g.getNumGroup();
    }
    catch(const char *msg){
        cerr << msg;
    }
}
