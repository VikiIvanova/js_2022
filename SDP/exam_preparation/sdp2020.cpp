/*Напишете функция, която по подаден като аргумент непразен свързан списък от цели числа
намира най-дългия негов непрекъснат под-списък, който е строго монотонен (нарастващ или намаляващ).
Ако има повече от един монотонен под-списък с максимална дължина, да се намери този с най-голяма
сума от елементите. Като резултат функцията трябва да върне списък, еквивалентен на този монотонен списък.
Подаденият като аргумент списък да не се променя. Демонстрирайте използването на функцията в програма.
Пример:
Входен списък:
2 -> 3 -> 2 -> 1 -> 0 -> 3 -> 2
Резултат:
3 -> 2 -> 1 -> 0*/
#include <iostream>
#include <vector>

struct LinkedListNode
{
    int data;
    LinkedListNode *next;
    LinkedListNode(int data, LinkedListNode *next = nullptr) : data(data), next(next){};
};

int sumElementInList(std::pair<LinkedListNode *, int> element)
{
    int index = 1;
    int sum = 0;
    while (index <= element.second)
    {
        sum += element.first->data;
        element.first = element.first->next;
        index++;
    }
    return sum;
}

LinkedListNode *maxMonotonicSeq(LinkedListNode *list, size_t &size)
{
    std::vector<std::pair<LinkedListNode *, int>> same;
    int maxLength = 1;
    int currentLength = 1;
    LinkedListNode *currentRoot = list;
    LinkedListNode *maxRoot = list;
    while (list->next)
    {
        while (list->next && list->data <= list->next->data)
        {
            currentLength++;
            list = list->next;
        }
        if (maxLength == currentLength)
        {
            same.push_back({maxRoot, maxLength});
            same.push_back({currentRoot, currentLength});
        }
        else if (maxLength < currentLength)
        {
            same.clear();
            maxLength = currentLength;
            maxRoot = currentRoot;
        }
        if (list->next)
        {
            currentRoot = list->next;
        }
        currentLength = 1;
        list = list->next;
    }
    if (same.size() > 1)
    {
        int maxSum = 0;
        for (auto index : same)
        {
            int sum = sumElementInList(index);
            if (sum > maxSum)
            {
                maxSum = sum;
                maxRoot = index.first;
            }
        }
        std::cout << "Има списъци с еднаква дължина, максималната сума на елементите е: " << maxSum << std::endl;
    }

    size = maxLength;
    return maxRoot;
}

int main()
{
    LinkedListNode *list = new LinkedListNode((2), new LinkedListNode((3), new LinkedListNode((2), new LinkedListNode((1), new LinkedListNode((0), new LinkedListNode((3), new LinkedListNode(2)))))));
    size_t size = 0;
    LinkedListNode *result = maxMonotonicSeq(list, size);

    while (size)
    {
        std::cout << result->data << " ";
        result = result->next;
        size--;
    }
    std::cout << std::endl;
}

/* Напишете програма, която да получи като аргумент име на текстов файл,
който съдържа произволен брой цели числа, разделени помежду си спразни символи (нов ред или интервал).
Програмата трябва да добави тези числа в двоично наредено дърво, което не допуска повторения (т.е. при опит
за добавяне на елемент, който вече съществува, дървото не се променя).
След това, при подадено число N, програмата трябва да предостави на потребителя информация
колко поддървета в така полученото дърво съдържат точно N елемента. Също така трябва да имате функция,
която по подадено дърво и число K да изтрива това число от дървото, заедно с всички негови четни наследници */

// #include <iostream>
// #include <string>
// #include <fstream>

// struct Node
// {
//     int data;
//     Node *left = nullptr;
//     Node *right = nullptr;
// };

// bool tryInsertRec(Node *&node, const int &elem)
// {
//     if (node == nullptr)
//     {
//         node = new Node{elem};
//         return true;
//     }

//     if (elem < node->data)
//         return tryInsertRec(node->left, elem);

//     if (elem > node->data)
//         return tryInsertRec(node->right, elem);

//     return false;
// }

// void insertRec(Node *&node, const int &elem)
// {
//     if (!tryInsertRec(node, elem))
//         throw std::logic_error("BST: Cannot store duplicate elements!");
// }

// void readBST(const std::string &filename, Node *&node)
// {
//     std::ifstream file_info(filename);
//     if (file_info.good())
//     {
//         int nextNode;
//         while (file_info.good())
//         {
//             file_info >> nextNode;
//             insertRec(node, nextNode);
//         }
//     }
// }

// // void print(const Node *node)
// // {
// //     if (node == nullptr)
// //         return;

// //     return print(node->left);
// //     std::cout << node->data << " ";
// //     return print(node->right);
// // }

// int countNodes(Node *root)
// {
//     if (root == nullptr)
//     {
//         return 0;
//     }
//     return countNodes(root->left) + countNodes(root->right) + 1;
// }

// int countSubtrees(Node *root, int n)
// {
//     if (root == nullptr)
//         return 0;

//     int leftCount = countSubtrees(root->left, n);
//     int rightCount = countSubtrees(root->right, n);
//     int currCount = (root->left ? countNodes(root->left) : 0) + (root->right ? countNodes(root->right) : 0) + 1;
//     if (currCount == n)
//     {
//         return leftCount + rightCount + 1;
//     }
//     return leftCount + rightCount;
// }

// Node *deleteNode(Node *root, int data)
// {
//     if (root == nullptr)
//         return nullptr;

//     if (data < root->data)
//         root->left = deleteNode(root->left, data);

//     else if (data > root->data)
//         root->right = deleteNode(root->right, data);

//     else
//     {
//         if (root->left == nullptr)
//         {
//             Node *temp = root->right;
//             delete root;
//             return temp;
//         }
//         else if (root->right == nullptr)
//         {
//             Node *temp = root->left;
//             delete root;
//             return temp;
//         }
//         Node *successor = root->right;
//         while (successor->left != nullptr)
//         {
//             successor = successor->left;
//         }
//         root->data = successor->data;
//         root->right = deleteNode(root->right, successor->data);
//     }
//     return root;
// }

// Node *deleteTree(Node *root)
// {
//     if (root == nullptr)
//         return nullptr;

//     root->left = deleteTree(root->left);
//     root->right = deleteTree(root->right);
//     delete root;
//     return nullptr;
// }

// Node *deleteEvenDescendants(Node *root, int data)
// {
//     if (root == nullptr)
//         return nullptr;

//     if (data < root->data)
//         root->left = deleteEvenDescendants(root->left, data);

//     else if (data > root->data)
//         root->right = deleteEvenDescendants(root->right, data);

//     else
//     {
//         if (root->data % 2 == 0)
//         {
//             root = deleteTree(root);
//         }
//         else
//         {
//             root->left = deleteEvenDescendants(root->left, data);
//             root->right = deleteEvenDescendants(root->right, data);
//         }
//     }
//     return root;
// }

// int main()
// {
//             Node *root;
//             readBST("bstTest.txt", root);
//             print(root);
// }

/* Задача: Да се реализира работа с разредени матрици. Това са матрици,
при които голяма част от елементите са нули.
А) Въведете данни за такава матрица с размери NxM (0 < N < 1000000000, 0 < M < 1000000000).
B) Проверете дали има два различни не нулеви реда, които са линейно зависими.
Ако има такава двойка – изведете номерата им. Ако няма – изведете -1.
Припомняме, че два вектора X и Y са линейно зависими, ако съществуват две числа a и b (a*b != 0), такива че aX+bY = 0
C) Въведете данни за вектор с M елемента. Умножете го по матрицата и изведете резултата на екрана.
Опишете входния формат, който използвате.
Той трябва да е еднозначен и да позволява въвеждане на произволни матрица и вектор, отговарящи на горното условие! */

/*Задача: Разглеждаме дървета с данни цели числа и произволна разклоненост и наредба на децата.
За всяко такова дърво са позволени две операции:
- Размяна на стойностите в два възела, намиращи се на едно ниво
- Размяна на два възела, които имат общ баща (това означава размяна на целите поддървета с корени в тези възли)
Напишете функция, която по подадени две такива дървета:
А) Проверява дали може чрез прилагане на тези две операции върху едното или двете от тях да се получат две еднакви дървета
Б) (бонус) Намира най-малкия брой операции, с които това може да се получи.
Демонстрирайте използването на функциите, като прочетете от стандартния вход двете дървета и
изведете на екрана дали може да ги трансформирате до еднакви дървета.
Опишете входния формат, който използвате. Той трябва да е еднозначен и да позволява въвеждане на произволно дърво,
отговарящо на горното условие.*/

/*Задача: Напишете функция, която получава като аргумент едносвързан списък с елементи цели числа.
Функцията трябва да го сортира по следното правило - в началото на списъка трябва да останат четните елементи,
подредени в нарастващ ред, след това нечетните елементи, подредени в намаляващ ред.
Също така премахнете повтарящите се елементи. Демонстрирайте функцията в кратка програма.
В тази задача не можете да използвате класовете от стандартната библиотека.*/
// #include <iostream>

// struct LinkedListNode
// {
//     int data;
//     LinkedListNode *next;
//     LinkedListNode(int data, LinkedListNode *next = nullptr) : data(data), next(next){};
// };

// void insertFrom(LinkedListNode *&list, int elem)
// {
//     if (list == nullptr)
//         list = new LinkedListNode(elem);
//     else
//     {
//         LinkedListNode *newNode = new LinkedListNode(elem, list);
//         list = newNode;
//     }
// }

// void insertAfter(LinkedListNode *&list, int elem)
// {
//     if (list == nullptr)
//         list = new LinkedListNode(elem);
//     else
//     {
//         LinkedListNode *temp = list;
//         while (list->next)
//         {
//             list = list->next;
//         }
//         LinkedListNode *newNode = new LinkedListNode(elem);
//         list->next = newNode;
//         list = temp;
//     }
// }
// void print(LinkedListNode *list)
// {
//     while (list)
//     {
//         std::cout << list->data << " ";
//         list = list->next;
//     }
//     std::cout << std::endl;
// }

// LinkedListNode *sortEvenElements(LinkedListNode *list)
// {
//     LinkedListNode *tempEvenElements = list;
//     LinkedListNode *resultEvenElement = nullptr;
//     while (tempEvenElements->data % 2 != 0)
//     {
//         tempEvenElements = tempEvenElements->next;
//     }
//     resultEvenElement = new LinkedListNode(tempEvenElements->data);
//     tempEvenElements = tempEvenElements->next;
//     while (tempEvenElements)
//     {
//         if (tempEvenElements->data % 2 == 0)
//         {
//             if (resultEvenElement->data < tempEvenElements->data)
//             {
//                 insertAfter(resultEvenElement, tempEvenElements->data);
//             }
//             else if (resultEvenElement->data > tempEvenElements->data)
//             {
//                 insertFrom(resultEvenElement, tempEvenElements->data);
//             }
//         }
//         tempEvenElements = tempEvenElements->next;
//     }
//     return resultEvenElement;
// }

// LinkedListNode *sortOddElements(LinkedListNode *list)
// {
//     LinkedListNode *tempOddElements = list;
//     LinkedListNode *resultOddElement = nullptr;
//     while (tempOddElements->data % 2 == 0)
//     {
//         tempOddElements = tempOddElements->next;
//     }
//     resultOddElement = new LinkedListNode(tempOddElements->data);
//     tempOddElements = tempOddElements->next;

//     while (tempOddElements)
//     {
//         if (tempOddElements->data % 2 != 0)
//         {
//             if (resultOddElement->data < tempOddElements->data)
//             {
//                 insertFrom(resultOddElement, tempOddElements->data);
//             }
//             else if (resultOddElement->data > tempOddElements->data)
//             {
//                 insertAfter(resultOddElement, tempOddElements->data);
//             }
//         }
//         tempOddElements = tempOddElements->next;
//     }
//     return resultOddElement;
// }
// LinkedListNode *sortForSpecificWayList(LinkedListNode *list)
// {
//     LinkedListNode *result = nullptr;
//     LinkedListNode *oddList = nullptr;
//     LinkedListNode *evenList = nullptr;
//     if (list->data % 2 != 0)
//     {
//         oddList = sortOddElements(list);
//         evenList = sortEvenElements(list);
//     }
//     else
//     {
//         evenList = sortEvenElements(list);
//         oddList = sortOddElements(list);
//     }
//     result = evenList;

//     while (evenList->next)
//     {
//         evenList = evenList->next;
//     }
//     evenList->next = oddList;
//     return result;
// }

// int main()
// {
//     LinkedListNode *list = new LinkedListNode(5, new LinkedListNode(4, new LinkedListNode(7, new LinkedListNode(3, new LinkedListNode(8, new LinkedListNode(2, new LinkedListNode(9)))))));
//     LinkedListNode *result = sortForSpecificWayList(list);
//     print(result);
// }

/*Задача: Разглеждаме колекция от символни низове.
Те са съставени от малки латински букви, цифри и символите '*' и '?'.
При сравняване на два низа всеки символ '?' можем да заменим с точно една произволна буква или цифра,
а всеки символ '*' с произволен брой (включително нула) букви или цифри.
Напишете функция, която получава като аргумент колекция от такива символни низове и
връща като резултат класовете на еквивалентност сред подадените низове.
Всеки клас на еквивалентност съдържа всички низове в началната последователност,
които са равни помежду си според горното правило.*/
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

std::vector<std::vector<std::string>> findEquivalenceClasses(const std::vector<std::string> &strs)
{
    std::unordered_map<std::string, std::unordered_set<std::string>> graph;
    std::unordered_map<std::string, int> visited;

    for (const auto &str1 : strs)
    {
        for (const auto &str2 : strs)
        {
            if (str1 == str2)
                continue;
            int i = 0, j = 0;
            while (i < str1.length() && j < str2.length())
            {
                if (str1[i] == '?' || str2[j] == '?' || str1[i] == str2[j])
                {
                    i++;
                    j++;
                }
                else if (str1[i] == '*')
                {
                    i++;
                    if (j == str2.length() - 1)
                    {
                        graph[str1].insert(str2);
                        break;
                    }
                }
                else if (str2[j] == '*')
                {
                    j++;
                    if (i == str1.length() - 1)
                    {
                        graph[str2].insert(str1);
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            if (i == str1.length() && j == str2.length())
            {
                graph[str1].insert(str2);
                graph[str2].insert(str1);
            }
        }
    }

    std::vector<std::vector<std::string>> result;
    for (const auto &str : strs)
    {
        if (visited.count(str) > 0)
            continue;
        std::vector<std::string> equivalentStrings;
        std::queue<std::string> queue;
        queue.push(str);
        visited[str] = result.size();
        while (!queue.empty())
        {
            auto curr = queue.front();
            queue.pop();
            equivalentStrings.push_back(curr);
            for (const auto &next : graph[curr])
            {
                if (visited.count(next) == 0)
                {
                    visited[next] = result.size();
                    queue.push(next);
                }
            }
        }
        result.push_back(equivalentStrings);
    }
    return result;
}
