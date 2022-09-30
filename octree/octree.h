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

        void init(Node* root, int x, int y, int z, int side, int deep)
        {
            if (deep == MAX_DEEP)
            {
                return;
            }
            std::cout << "init() : " + deep << std::endl;
            root = new Node(x, y, z, side);
            init(root->childs[0], x - side / 4, y - side / 4, z + side / 4, side / 2, deep + 1);
            init(root->childs[1], x - side / 4, y + side / 4, z + side / 4, side / 2, deep + 1);
            init(root->childs[2], x + side / 4, y - side / 4, z + side / 4, side / 2, deep + 1);
            init(root->childs[3], x + side / 4, y + side / 4, z + side / 4, side / 2, deep + 1);
            init(root->childs[4], x - side / 4, y + side / 4, z - side / 4, side / 2, deep + 1);
            init(root->childs[5], x - side / 4, y - side / 4, z - side / 4, side / 2, deep + 1);
            init(root->childs[6], x + side / 4, y + side / 4, z - side / 4, side / 2, deep + 1);
            init(root->childs[7], x + side / 4, y - side / 4, z - side / 4, side / 2, deep + 1);
        }

    public:
        Octree()
        {
            this->init(head, 0, 0, 0, BOX_SIDE, 1);
            return;
        }

        bool find(int x, int y, int z)
        {
             
        }
        
        void insert(int x, int y, int z)
        {

        }

        Node* deepFind(Node* root, int x, int y, int z, int deep)
        {
            int side = root->sideLength;
            int rootX = root->x;
            int rootY = root->y;
            int rootZ = root->z;
            if (
                (rootX - side / 2 <= x && rootX + side / 2 >= x) &&
                (rootY - side / 2 <= y && rootY + side / 2 >= y) &&
                (rootZ - side / 2 <= z && rootZ + side / 2 >= z)
            )
            {
                
            }

            if (deep > MAX_DEEP)
            {
                return true;
            }
        }

        ~Octree()
        {

        }
    };
}