#include <iostream>
#include <vector>
#define MAX_DEEP 5
#define BOX_SIDE 100

namespace KS
{
    struct Node
    {
        int x, y, z;
        int sideLength;
        std::vector<std::vector<int>> points;   // all actors inside current space. 
        struct Node* childs[8];
        Node(int x_, int y_, int z_, int sideLength_):x(x_),y(y_),z(z_),sideLength(sideLength_) {}
    };

    class Octree
    {
    private:
        struct Node* head = nullptr;

        Node* init(int x, int y, int z, int side, int deep)
        {
            if (deep > MAX_DEEP)
            {
                return nullptr;
            }
            // std::cout << "init() : " + deep << std::endl;
            Node* root = new Node(x, y, z, side);
            root->childs[0] = init(x - side / 4, y - side / 4, z + side / 4, side / 2, deep + 1);
            root->childs[1] = init(x - side / 4, y + side / 4, z + side / 4, side / 2, deep + 1);
            root->childs[2] = init(x + side / 4, y - side / 4, z + side / 4, side / 2, deep + 1);
            root->childs[3] = init(x + side / 4, y + side / 4, z + side / 4, side / 2, deep + 1);
            root->childs[4] = init(x - side / 4, y + side / 4, z - side / 4, side / 2, deep + 1);
            root->childs[5] = init(x - side / 4, y - side / 4, z - side / 4, side / 2, deep + 1);
            root->childs[6] = init(x + side / 4, y + side / 4, z - side / 4, side / 2, deep + 1);
            root->childs[7] = init(x + side / 4, y - side / 4, z - side / 4, side / 2, deep + 1);
            return root;
        }

        void deepFind(Node* root, int x, int y, int z, int deep, Node*& value)
        {
            if (root == nullptr)
            {
                return;
            }

            int side = root->sideLength;
            int rootX = root->x;
            int rootY = root->y;
            int rootZ = root->z;
            if (((rootX - side / 2 <= x && rootX + side / 2 >= x) && (rootY - side / 2 <= y && rootY + side / 2 >= y) && (rootZ - side / 2 <= z && rootZ + side / 2 >= z)) == false)
            {
                return; // don’t in this space.
            }

            if (deep == MAX_DEEP)
            {
                for (auto &&i : root->points)
                {
                    if (i.at(0) == x && i.at(1) == y && i.at(2) == z)
                    {
                        value = root;
                        return;
                    }
                }
                return;    // in this space.
            }

            for (int i = 0; i < 8; ++i)
            {
                deepFind(root->childs[i], x, y, z, deep + 1, value); 
            }
        }

        bool deepInsert(Node* root, int x, int y, int z, int deep)
        {
            if (root == nullptr)
            {
                return false;
            }
            int side = root->sideLength;
            int rootX = root->x;
            int rootY = root->y;
            int rootZ = root->z;
            if (((rootX - side / 2 <= x - 1 && rootX + side / 2 >= x + 1) && (rootY - side / 2 <= y - 1 && rootY + side / 2 >= y + 1) && (rootZ - side / 2 <= z - 1 && rootZ + side / 2 >= z + 1)) == false)
            {
                return false; // don’t in this space.
            }

            if (deep == MAX_DEEP)
            {
                root->points.push_back({x,y,z});
                return true;    // in this space.
            }

            bool value = false;
            for (int i = 0; i < 8; ++i)
            {
                value = value || deepInsert(root->childs[i], x, y, z, deep + 1);
            }
            return value;
        }

    public:
        Octree()
        {
            this->head = init(0,0,0,BOX_SIDE, 1);
            return;
        }

        bool find(int x, int y, int z)
        {
            Node* value = nullptr;
            deepFind(this->head, x, y, z, 1, value);
            if (value == nullptr)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        
        bool insert(int x, int y, int z)
        {
            return deepInsert(this->head, x, y, z, 1);
        }

        ~Octree()
        {

        }
    };
}