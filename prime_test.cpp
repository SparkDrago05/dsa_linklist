#include <iostream>
#include <random>

using namespace std;

struct Node
{
    uint64_t chunk; // 64-bit number
    Node *next;
    Node() : chunk(0), next(nullptr) {};
};

class LinkedList
{
    Node *head;
    Node *tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {};

    /**
     * The function `addNode` creates a new node with a given chunk value and adds it to the end of the
     * linked list.
     *
     * @param chunk The `chunk` parameter in the `addNode` function is of type `uint64_t`, which is an
     * unsigned 64-bit integer. This parameter represents the data that will be stored in the new node
     * being added to a linked list.
     */
    void addNode(uint64_t chunk)
    {
        Node *node = new Node();
        node->chunk = chunk;

        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }

        size++;
    }

    /**
     * This function removes a specified node from the linked list.
     *
     * @param node The node that needs to be removed from the list.
     */
    void removeNode(Node *node)
    {
        if (head == nullptr)
            return;

        Node *temp = head;
        Node *prev = nullptr;

        while (temp != nullptr)
        {
            if (temp == node)
            {
                if (prev != nullptr)
                {
                    prev->next = temp->next;
                }
                if (temp == head)
                {
                    head = temp->next;
                }
                if (temp == tail)
                {
                    tail = prev;
                }
                delete temp;
                size--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    /**
     * The clear function deletes all nodes in a linked list and resets the head, tail, and size
     * variables.
     */
    void clear()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /**
     * The function `display` iterates through a linked list and prints out the values of each node.
     */
    void display(bool includeSpace = true)
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->chunk << (includeSpace ? " " : "");
            temp = temp->next;
        }
        cout << endl;
    }

    /**
     * The function checks if all elements in a linked list are zero and returns true if they are.
     *
     * @return The function isZero() returns a boolean value - true if all the chunk values in the
     * linked list are zero, and false if at least one chunk value is not zero.
     */
    bool isZero()
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->chunk != 0)
            {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    /**
     * The function `isOdd` checks if the value of `chunk` in the `tail` node is odd.
     *
     * @return The function is checking if the last element in the linked list (tail) is an odd number.
     * It returns true if the last element is odd (its value modulo 2 is 1), and false otherwise.
     */
    bool isOdd()
    {
        return (tail->chunk % 2 == 1);
    }

    /**
     * The function `divideByTwo` iterates through a linked list of nodes, dividing each node's chunk
     * value by 2 and carrying over the remainder to the next node.
     */
    void divideByTwo()
    {
        Node *current = head;
        uint64_t carry = 0;
        while (current != nullptr)
        {
            uint64_t temp = current->chunk;
            current->chunk = (current->chunk + carry) / 2;
            carry = (temp % 2) * (1ULL << 63);
            current = current->next;
        }
    }

    // Modular Exponentiation: (base^exponent) % mod using the list.
    uint64_t modularExponentiation(uint64_t base, LinkedList &exponent, uint64_t mod)
    {
        uint64_t result = 1;
        LinkedList currentExponent = exponent;

        // While the exponent is not zero
        while (!currentExponent.isZero())
        {
            // If the exponent is odd, multiply the result with the base
            if (currentExponent.isOdd())
            {
                result = (result * base) % mod;
            }
            // Square the base
            base = (base * base) % mod;
            // Divide the exponent by 2
            currentExponent.divideByTwo();
        }

        return result;
    }

    int subtractOneUtil(Node *head)
    {
        if (head == nullptr)
        {
            return -1;
        }

        // Recursively call for next node
        int borrow = subtractOneUtil(head->next);

        // If there is a borrow
        if (borrow == -1)
        {
            // If the current node is 0, set it to 0xFFFFFFFFFFFFFFFF
            if (head->chunk == 0)
            {
                head->chunk = UINT64_MAX;
                return -1;
            }
            // Otherwise, subtract 1 from the current node
            else
            {
                head->chunk -= 1;
                return 0;
            }
        }
        // If there is no borrow
        else
        {
            return 0;
        }
    }

    // Subtract one from the 1024 bit number in the list (n - 1)
    void subtractOne()
    {
        // Recursively subtract one from the number
        subtractOneUtil(head);

        // If there are leading zeros
        while (head && head->next && head->chunk == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Check if the number is 1
    bool isOne()
    {
        return (size == 1 && head->chunk == 1);
    }

    // Check if the number is equal to another number
    bool equals(LinkedList &other)
    {
        if (size != other.size)
        {
            return false;
        }

        Node *current = head;
        Node *otherCurrent = other.head;

        while (current != nullptr)
        {
            if (current->chunk != otherCurrent->chunk)
            {
                return false;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        return true;
    }

    // Use Miller-Rabin Primality Test to check if the number is prime.
    // Here All nodes of the Link List collectively represent the 1024-bit number.
    bool isPrime(int noOfRounds)
    {
        if (isZero() || !isOdd())
        {
            return false;
        }

        // Write the number in the form of 2^r * d + 1
        // Get the value of d
        LinkedList nMinus1List = *this;
        nMinus1List.subtractOne();

        // Get the value of r
        int r = 0;
        while (!nMinus1List.isOdd())
        {
            nMinus1List.divideByTwo();
            r++;
        }

        LinkedList d = nMinus1List;

        // Miller-Rabin Primality Test
        for (int i = 0; i < noOfRounds; i++)
        {
            uint64_t a = 2 + rand() % (UINT64_MAX - 2); // Random number between 2 and UINT64_MAX - 1
            uint64_t x = modularExponentiation(a, d, UINT64_MAX);
            if (x == 1 || x == (UINT64_MAX - 1))
            {
                continue; // This round is likely prime
            }
            bool isComposite = true;
            for (int j = 0; j < r - 1; j++)
            {
                x = (x * x) % UINT64_MAX;
                if (x == (UINT64_MAX - 1))
                {
                    isComposite = false;
                    break;
                }
            }
            if (isComposite)
            {
                return false; // Composite number found
            }
        }
        return true; // Probably prime
    }

    ~LinkedList()
    {
        Node *temp = head;
        Node *next = nullptr;
        while (temp != nullptr)
        {
            next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main()
{
    LinkedList list;
    // Generate 64-bit random number and add it to the list
    // Seed the random number
    srand(time(0));
    for (int i = 0; i < 16; i++)
    {
        uint64_t random_number = (uint64_t)rand() << 32 | rand();
        list.addNode(random_number);
    }

    list.display();

    if (list.isPrime(5))
    {
        cout << "The number is prime." << endl;
    }
    else
    {
        cout << "The number is not prime." << endl;
    }

    return 0;
}