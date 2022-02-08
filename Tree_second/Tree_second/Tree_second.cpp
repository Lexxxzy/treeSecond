

#include <iostream>

class NodeBST
{
private:
    int data;
    NodeBST* left;
    NodeBST* right;

public:

    int getValue(); //у каждого узла есть значение - data, возвращаем его

    NodeBST getLeftSon(); //кто находится слева от него
    NodeBST getRight(); //кто находится справа от него
    void setValue(NodeBST* node, int data); //метод, который вставляет значение в дерево. так как это дерево двоичного поиска,
    //если ключ меньше, то вставляется левее родителя, если ключ больше или равен то правее.
    //Алгоритм такой : если слева никого нет, то вставляем элемент, а если кто - то есть идем дальше рекурсивно и тд.
    //Тоесть это построение двоичного дерева

    NodeBST* findNode(NodeBST* node, NodeBST* p, int data); //поиск элемента, можно узнать родителя чтобы его сохранить
    NodeBST* findNode(NodeBST* node, int data);

    void printPreorder(NodeBST* root); //прямой обход дерева - корень - левое поддерево - правое поддерево 
    void printInorder(NodeBST* root); //симметричный обход - левое - корень - правое

   // void removeNode(NodeBST* node, int data); //удаление элемента, если никого нет просто удаляем;
    //если есть левый ребенок- то он и встает наверх; если есть правый то это число встает наверх, т.е. образуем новую связь

    void exception(NodeBST* A, NodeBST* B, NodeBST* C); //главный метод, строит новое дерево и добавляет туда элементы пересечения A и B,
    //он бегает по дереву B, а затем смотрит есть ли такой в A, если есть то добавляет в C, если нет то идет дальше

    NodeBST() { data = NULL; left = right = NULL; } //пустой конструктор
    NodeBST(int d) { data = d; left = right = NULL; } //конструктор для задания значения

};

int NodeBST::getValue()
{
    return data;
}

NodeBST NodeBST::getLeftSon()
{
    if (left == nullptr) return 0;
    return *left;
}

NodeBST NodeBST::getRight()
{
    if (right == nullptr) return 0;
    return *right;
}

void NodeBST::setValue(NodeBST* node, int data)
{
    if (node == NULL) node = new NodeBST(data);
    else
    {
        if (node->data > data) //если меньше чем родитель
        {
            if (node->left == NULL) node->left = new NodeBST(data); //если нет левого ребенка
            else
            {
                setValue(node->left, data); //рекурсивно вызываем функцию пока не найдем свободное место
            }
        }
        else //если больше чем родитель
        {
            if (node->right == NULL) node->right = new NodeBST(data); //если нет правого ребенка
            else
            {
                setValue(node->right, data);
            }
        }
    }
}


void NodeBST::printPreorder(NodeBST* rootNode)
{
    if (rootNode == NULL)
    {
        //std::cout << "Дерево пусто" << std::endl;
        return;
    }
    if (rootNode->getValue() != 0)
    {
        std::cout << rootNode->getValue() << " ";
        
        //std::cout << "Левое ";
        printPreorder(rootNode->left);
        //std::cout << "Правое ";
        printPreorder(rootNode->right);
    }
}

void NodeBST::printInorder(NodeBST* rootNode)
{
    if (rootNode == NULL)
    {
       // std::cout << "Дерево пусто" << std::endl;
        return;
    }
    printInorder(rootNode->left);
    if (rootNode->getValue() != 0)
    {
        std::cout << rootNode->getValue() << " " << std::endl;
    }
    printInorder(rootNode->right);
}

NodeBST* NodeBST::findNode(NodeBST* node, NodeBST* parent, int data)
{
    if (node->left != NULL && node->right != NULL)
    {
        if (node->left->data == data || node->right->data == data) *parent = *node;
    }
    else if (node->left == NULL && node->right != NULL)
    {
        if (node->right->data == data) *parent = *node;
    }
    else if (node->left != NULL && node->right == NULL)
    {
        if (node->left->data == data) *parent = *node;
    }

    if (node == NULL) return 0;
    if (node->data == data)
    {
        return node;
    }
    else if (node->data > data)
    {
        return findNode(node->left, parent, data);
    }
    else
    {
        return findNode(node->right, parent, data);
    }
}

NodeBST* NodeBST::findNode(NodeBST* node, int data)
{

    if (node == NULL) return 0;
    if (node->data == data)
    {
        return node;
    }
    else if (node->data > data)
    {
        return findNode(node->left, data);
    }
    else
    {
        return findNode(node->right, data);
    }
}

/*
void NodeBST::removeNode(NodeBST* node, int data)
{
    NodeBST parent;
    NodeBST* currentNode = findNode(node, &parent, data);

    if (currentNode->right == NULL && currentNode->left == NULL)
    {
        *parent.right = NULL;
        currentNode = NULL;
    }
    else
    {
        if (currentNode->right == NULL && currentNode->left != NULL)
        {
            currentNode->data = currentNode->left->data;
            currentNode->left = currentNode->left->left;
            currentNode->right = currentNode->left->right;
        }
        else if (currentNode->right == NULL && currentNode->right->left == NULL
            && currentNode->right->right != NULL)
        {
            currentNode->data = currentNode->right->data;
            currentNode->right = currentNode->right->right;
        }

        else if (currentNode->right != NULL && currentNode->right->left == NULL
            && currentNode->right->right != NULL)
        {
            currentNode->data = currentNode->right->data;
            currentNode->right = NULL;
        }
        else if (currentNode->right != NULL && currentNode->right->left == NULL
            && currentNode->right->right == NULL)
        {
            currentNode->data = currentNode->right->left->data;
            currentNode->right->left = NULL;
        }
        else if (currentNode->right != NULL && currentNode->right->left != NULL
            && currentNode->right->right != NULL)
        {
            currentNode->data = currentNode->right->data;
            currentNode->right = currentNode->right->left;
            currentNode->left = currentNode->right->right;
        }
    }
}
*/


void NodeBST::exception(NodeBST* A, NodeBST* B, NodeBST* C)
{
    if (B == NULL)
    {
        return;
    }
    if (A->findNode(A, B->data) != 0)
    {
        C->setValue(C, B->data);
    }
    
    exception(A, B->left, C);
    exception(A, B->right, C);
}



int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    NodeBST* A = new NodeBST(1 + rand() % 1000);
    A->setValue(A,2);
    NodeBST* B= new NodeBST(1 + rand() % 1000);
    NodeBST* C = new NodeBST();

    for (int i = 0; i < 9; i++)
    {
        A->setValue(A, 1 + rand() % 30);
    }

    for (int i = 0; i < 9; i++)
    {
        B->setValue(B, 1 + rand() % 30);
    }

    A->printPreorder(A);
    std::cout << "\n";
    B->printInorder(B);
    std::cout << "\n";
    A->exception(A, B, C);
   // A->printPreorder(A);
    std::cout << "\n";


    C->printInorder(C);
    


}