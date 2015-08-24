//Very tree.  So binary. Wow.
//Esquire At Large

namespace Tree
{
    template <class T>
    class TreeNode
    {
    public:
        TreeNode(T data)
            : m_left(nullptr), m_right(nullptr), m_data(data)
        {
        }

        //Get this node's left child.
        inline TreeNode<T>* GetLeft()  { return m_left; }

        //Get this node's right child.
        inline TreeNode<T>* GetRight() { return m_right; }

        //Get the data this node holds.
        inline T         GetData()  { return m_data; }

        inline void      SetLeft(TreeNode<T>* t) { m_left = t; }
        inline void      SetRight(TreeNode<T>* t) { m_right = t; }

        virtual ~TreeNode()
        {
            if (m_left)
                delete m_left;
            if (m_right)
                delete m_right;
        }

    private:
        TreeNode<T>* m_left;
        TreeNode<T>* m_right;

        T         m_data;
    };

    template <class T>
    class BinarySearchTree
    {
    public:
        explicit BinarySearchTree(T root)
            : m_root(), m_numItems(0)
        {
            m_root = new TreeNode<T>(root);
        }

        explicit BinarySearchTree(const char* preOrder)
        {

        }

        //Insert a node into the tree.
        //Worst case: O(n)
        //Why O(n)?  Let's assume so far we have only added numbers each one greater than the previous.
        //So our tree now is basically a linked list, and if we add another node greater than all the rest, 
        //we must iterate all the way down to the bottom through every node.


        //Average: O(log(n))
        //Why O(log(n))?  Assuming a balanced tree, we can shave off half the tree on an insertion!  
        //Instead of checking every node as in the worst case, we can ignore one half of the tree depending on the node we
        //are inserting.  

        bool Insert(T item)
        {
            return Insert(item, m_root);
        }

        bool Remove(T item)
        {
            TreeNode<T>* t = Find(item);
            if (!t)
                return false;

            if (!t->GetLeft() && !t->GetRight())
            {
                //A leaf node can just be deleted.
                delete t;
                m_numItems--;

                return true;
            }

            LeftRotate(t->GetLeft());

            return false;
        }

        //Remove all nodes from the tree.
        //Replace the root value with the argument.
        void Clear(int newRoot)
        {
            delete m_root;
            m_root = new TreeNode<T>(newRoot);
        }

        int Depth()
        {
            return Depth(m_root);
        }

        TreeNode<T>* TraverseBFS(T item)
        {
            return DoBFS(item);
        }

        //DFS
        TreeNode<T>* Find(T item)
        {
            return Find(item, m_root);
        }

        bool IsBalanced()
        {
            int dl = Depth(m_root->GetLeft());
            int dr = Depth(m_root->GetRight());
            return (abs(dr - dl) <= 1);
        }

        //Balance using Day-Stout-Warren
        void Balance()
        {
            //Let's make a dummy root.
            TreeNode<T>* dmyRoot = new TreeNode<T>();
            dmyRoot->SetRight(m_root);

            int size = 0;
            ToLinkedList(dmyRoot, size);


        }

        //This function will provide the distance (number of edges) between the
        //two argument nodes.
        //If the two nodes refer to the same node, the distance is zero.
        int GetDistance(TreeNode<T>* home, TreeNode<T>* destination)
        {
            //The nodes have to be valid, otherwise let's return a negative distance.
            if (!home || !destination)
                return -1;

            if (home == destination)
                return 0;

            //Let's find the closest common ancestor of the two nodes.
            TreeNode<T>* ancestor = FindAncestor(m_root, home, destination);
            if (!ancestor)
                return -1;

            int d1 = DistanceTo(ancestor, home);
            int d2 = DistanceTo(ancestor, destination);

            return d1 + d2;
        }

        virtual ~BinarySearchTree()
        {
            delete m_root;
        }

    private:
        TreeNode<T>* m_root;

        //The amount of nodes present in the tree
        int m_numItems; 

        void ToLinkedList(TreeNode<T>* root, int& size)
        {
            struct Node
            {
                TreeNode<T>* data;
                Node* next;
            };
            Node head;
            Node* tail = &head;
            TreeNode<T>* r = root->GetRight();

            head.data = root;

            while (r != null)
            {
                if (r->GetLeft() == nullptr)
                {
                    tail->next 
                }
                else
                {
                }
            }


            while ()
        }

        int Depth(TreeNode<T>* tn)
        {
            if (!tn)
                return 0;

            int dl = Depth(tn->GetLeft());
            int dr = Depth(tn->GetRight());

            return ((dl > dr) ? (dl + 1) : (dr + 1));
        }

        int DistanceTo(TreeNode<T>* from, TreeNode<T>* to)
        {
            if (!from || !to)
                return 0;
            if (to->GetData() > from->GetData())
                return 1 + DistanceTo(from->GetRight(), to);
            else if (to->GetData() < from->GetData())
                return 1 + DistanceTo(from->GetLeft(), to);
            return 0;
        }

        TreeNode<T>* Find(T item, TreeNode<T>* start)
        {
            if (!start)
                return nullptr;
            if (item == start->GetData())
                return start;
            if (item > start->GetData())
                return Find(item, start->GetRight());
            else
                return Find(item, start->GetLeft());
        }

        bool Insert(T item, TreeNode<T>* parent)
        {
            if (!parent)
                return false;
            if (item > parent->GetData())
            {
                TreeNode<T>* r = parent->GetRight();
                if (r)
                    return Insert(item, r);
                else
                {
                    TreeNode<T>* n = new TreeNode<T>(item);
                    parent->SetRight(n);
                    m_numItems++;
                    return true;
                }
            }
            else if(item < parent->GetData())
            {
                TreeNode<T>* l = parent->GetLeft();
                if (l)
                    return Insert(item, l);
                else
                {
                    TreeNode<T>* n = new TreeNode<T>(item);
                    parent->SetLeft(n);
                    m_numItems++;
                    return true;
                }
            }
            return false;
        }

        TreeNode<T>* DoBFS(T item)
        {
            TreeNode<T>** nodes = new TreeNode<T>*[m_numItems + 1];
            TreeNode<T>* target = nullptr;

            int current = 0, next = 1;
            nodes[0] = m_root;

            bool found = false;
            int i = 0;
            while ((current < next) && !target)
            {
                TreeNode<T>* now = nodes[current];
                current++;

                if (now->GetData() == item)
                    target = now;
                else  
                {
                    if ((now->GetLeft()))
                    {
                        nodes[next] = now->GetLeft();
                        next++;
                    }
                    if (now->GetRight())
                    {
                        nodes[next] = now->GetRight();
                        next++;
                    }
                }
            }

            delete nodes;
            return target;
        }

        //Let's take the right child of the argument node.
        //Make it the parent node, and move the argument node down to a left child of the new parent.
        //Assign the right node's left child to be a right child of the argument node.
        //Function returns the new subtree root.
        //The parent can be adjusted using this return type; alternatively the parent could be passed down.
        TreeNode<T>* LeftRotate(TreeNode<T>* item)
        {
            if (item == nullptr)
                return nullptr;

            if (item->GetRight() == nullptr)
                return item;

            TreeNode<T>* right = item->GetRight();
            item->SetRight(right->GetLeft());
            right->SetLeft(item);

            return right;
        }

        //Take the left child of the argument node.
        //Make this child the parent node, moving the argument node down to a right child.
        //Assign the left child's right node to be a left child of the argument node.
        //Function returns the new subtree root.
        TreeNode<T>* RightRotate(TreeNode<T>* item)
        {
            if (item == nullptr)
                return nullptr;

            if (item->GetLeft() == nullptr)
                return item;

            TreeNode<T>* left = item->GetLeft();
            item->SetLeft(left->GetRight());
            left->SetRight(item);

            return left;
        }

        //This function will search for the nearest ancestor of the two argument nodes, one and two.
        //parent - The node to begin the search for.
        //kith - One of the familial nodes.
        //kin - The second of the familial nodes.
        //This function will use two markers and continue traversing down the tree until the markers no longer
        //equal one another.  The last place the markers equaled one another is the last common node.
        TreeNode<T>* FindAncestor(TreeNode<T>* parent, TreeNode<T>* kith, TreeNode<T>* kin)
        {
            //Border condition.
            if (!parent || !kith || !kin)
                return nullptr;

            //If the nodes are the same, we are our own ancestor.
            if (kith == kin)
                return kith;

            TreeNode<T>* ancestor = parent;
            TreeNode<T>* child1 = nullptr, *child2 = nullptr; //The two markers.
            
            //Let's run down the tree with both markers.  The reason for an if - elif
            //is because we don't want to continue traversing if the kith or kin nodes 
            //would be one of the ancestors (picture two nodes on the same branch). <mrs>
            if (kith->GetData() < parent->GetData())
            {
                child1 = ancestor->GetLeft();
            }
            else if (kith->GetData() > parent->GetData())
            {
                child1 = ancestor->GetRight();
            }

            if (kin->GetData() < parent->GetData())
            {
                child2 = ancestor->GetLeft();
            }
            else if (kin->GetData() > parent->GetData())
            {
                child2 = ancestor->GetRight();
            }

            //The instant the markers differ, return the ancestor.
            if (child1 != child2)
                return ancestor;

            ancestor = child1;

            return FindAncestor(ancestor, kith, kin);
        }
    };
}