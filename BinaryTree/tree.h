//Very tree.  So binary. Wow.
//Matt Sguerri.

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

        inline TreeNode<T>* GetLeft()  { return m_left; }
        inline TreeNode<T>* GetRight() { return m_right; }
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
            : m_root()
        {
            m_root = new TreeNode<T>(root);
        }

        bool Insert(T item)
        {
            return Insert(item, m_root);
        }

        bool Remove(T item)
        {
            TreeNode<T>* t = Find(item);
            if (t)
            {
                delete t;
            }

            return false;
        }

        int Depth()
        {
            return Depth(m_root);
        }

        TreeNode<T>* TraverseBFS(T item)
        {
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

        virtual ~BinarySearchTree()
        {
            delete m_root;
        }

    private:
        TreeNode<T>* m_root;

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
                    return true;
                }
            }
            return false;
        }
    };
}