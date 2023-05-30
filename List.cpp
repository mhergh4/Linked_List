#include <iostream>

// define a class ListNode to store the data and the next pointer
class ListNode
{
public:
    // constructor to initialize the data and next pointer
    ListNode(const double _d) : _data(_d),
                                _nextPtr(nullptr)
    {
    }
    double _data;       // the data stored in the node
    ListNode *_nextPtr; // pointer to the next node in the list
};

// define a class List to manage the linked list
class List
{
public:
    // constructor to initialize the first and last pointers
    List()
    {
        _firstPtr = nullptr;
        _lastPtr = nullptr;
    }

    // destructor to deallocate the memory used by the nodes
    ~List()
    {
        ListNode *temp = _firstPtr;
        while (temp != nullptr)
        {
            _firstPtr = _firstPtr->_nextPtr;
            delete temp;
            temp = _firstPtr;
        }
    }
    size_t getElementCount() const
    {
        return _count;
    }
    bool insertAtIndex(const size_t idx, const double value)
    {
        ListNode *indexDataNode = getNewNode(value);
        if (isEmpty())
        {
            _count++;
            _firstPtr = _lastPtr = indexDataNode;
        }
        else
        {
            if (idx == 0)
            {
                insertAtFront(value);
            }
            else if (idx >= getElementCount() || idx < 0)
            {
                return false;
            }
            else
            {
                _count++;
                ListNode *temp = _firstPtr;
                for (int i = 0; i < idx - 1; i++)
                {
                    temp = temp->_nextPtr;
                }
                ListNode *nextTemp = temp->_nextPtr;
                temp->_nextPtr = indexDataNode;
                indexDataNode->_nextPtr = nextTemp;
            }
        }
        return true;
    }
    bool removeAtIndex(const size_t idx, double &dataSaver)
    {
        if (isEmpty())
        {
            dataSaver = 0;
            return false;
        }
        else
        {
            if (idx == 0)
                removeFromFront(dataSaver);
            else if (idx == getElementCount() - 1)
                removeFromBack(dataSaver);
            else if (idx < 0 || idx >= getElementCount())
            {
                return false;
            }
            else
            {
                _count--;
                ListNode *temp = _firstPtr;
                for (int i = 0; i < idx - 1; i++)
                {
                    temp = temp->_nextPtr;
                }
                ListNode *nextTemp = temp->_nextPtr->_nextPtr;
                dataSaver = temp->_nextPtr->_data;
                delete temp->_nextPtr;
                temp->_nextPtr = nextTemp;
            }
            return true;
        }
    }
    // function to insert a new node at the front of the list
    void insertAtFront(const double frontData)
    {
        _count++;
        ListNode *frontDataNode = getNewNode(frontData);
        if (isEmpty())
        {
            _firstPtr = _lastPtr = frontDataNode;
        }
        else
        {
            ListNode *temporaryNode = _firstPtr;
            _firstPtr = frontDataNode;
            frontDataNode->_nextPtr = temporaryNode;
        }
    }

    // function to insert a new node at the back of the list
    void insertAtBack(const double backData)
    {
        _count++;
        ListNode *backDataNode = getNewNode(backData);
        if (isEmpty())
        {
            _firstPtr = _lastPtr = backDataNode;
        }
        else
        {
            _lastPtr->_nextPtr = backDataNode;
            _lastPtr = backDataNode;
        }
    }

    // function to remove the node at the front of the list and return its data
    bool removeFromFront(double &dataSaver)
    {
        if (isEmpty())
        {
            return false;
        }
        else
        {
            _count--;
            dataSaver = _firstPtr->_data;
            ListNode *temp = _firstPtr;
            _firstPtr = _firstPtr->_nextPtr;
            delete temp;
            return true;
        }
    }

    // function to remove the node at the back of the list and return its data
    bool removeFromBack(double &dataSaver)
    {
        if (isEmpty())
        {
            return false;
        }
        else
        {
            _count--;
            dataSaver = _lastPtr->_data;
            if (_firstPtr == _lastPtr)
            {
                _firstPtr = _lastPtr = nullptr;
            }
            else
            {
                ListNode *temp = _firstPtr;
                while (temp->_nextPtr != _lastPtr)
                {
                    temp = temp->_nextPtr;
                }
                _lastPtr = temp;
                temp = temp->_nextPtr;
                _lastPtr->_nextPtr = nullptr;
                delete temp;
            }
            return true;
        }
    }

    // function to check if the list is empty
    bool isEmpty() const
    {
        return _firstPtr == nullptr;
    }

    // function to print the list
    void print() const
    {
        if (isEmpty())
        {
            std::cout << "List is empty :(" << std::endl;
        }
        else
        {
            ListNode *temp = _firstPtr;
            std::cout << "Our Linked list is" << std::endl;
            while (temp != nullptr)
            {
                std::cout << temp->_data << "  ";
                temp = temp->_nextPtr;
            }
            std::cout << std::endl;
        }
    }

private:
    // helper function to create a new ListNode with given value
    ListNode *getNewNode(const double value) const
    {
        return new ListNode(value);
    }

private:
    ListNode *_firstPtr; // pointer to the first node in the list
    ListNode *_lastPtr;  // pointer to the last node in the list
    size_t _count = 0;
};

// function to display instructions to the user
void instructions()
{
    std::cout << "Enter one of the following:\n"
              << " 1 to insert at beginning of list\n"
              << " 2 to insert at end of list\n"
              << " 3 to delete from beginning of list\n"
              << " 4 to delete from end of list\n"
              << " 5 to insert at index index\n"
              << " 6 to delete from index\n"
              << " 7 to report the number of elements\n"
              << " 8 to end list processing\n";
}

int main()
{
    int processNumber = 0;
    double dataAccepter;
    int indexAccepter;
    List myList;
    instructions(); // display instructions to the user

    while (processNumber != 8)
    { // continue until user enters 5
        std::cout << "\nWhich instruction?  ";
        std::cin >> processNumber;

        if (processNumber == 1 || processNumber == 2 || processNumber == 5)
        {
            std::cout << "Enter your data value: ";
            std::cin >> dataAccepter;
        }
        if (processNumber == 5 || processNumber == 6)
        {
            std::cout << "Enter index ";
            std::cin >> indexAccepter;
        }

        std::cout << std::endl;

        if (processNumber == 1)
        {
            myList.insertAtFront(dataAccepter);
            myList.print();
        }
        else if (processNumber == 2)
        {
            myList.insertAtBack(dataAccepter);
            myList.print();
        }
        else if (processNumber == 3)
        {
            double deletedData;
            if (myList.removeFromFront(deletedData))
            {
                std::cout << deletedData << " was deleted" << std::endl;
                myList.print();
            }
            else
                std::cout << "List is empty";
        }
        else if (processNumber == 4)
        {
            double deletedData;
            if (myList.removeFromBack(deletedData))
            {
                std::cout << deletedData << " was deleted" << std::endl;
                myList.print();
            }
            else
                std::cout << "List is empty";
        }
        else if (processNumber == 5)
        {
            if (myList.insertAtIndex(indexAccepter, dataAccepter))
                myList.print();
            else
                std::cout << " In List don't have a index " << indexAccepter << std::endl;
        }
        else if (processNumber == 6)
        {
            double deletedData;
            if (myList.removeAtIndex(indexAccepter, deletedData))
            {
                std::cout << deletedData << " was deleted" << std::endl;
                myList.print();
            }
            else
                std::cout << " In List don't have a index " << indexAccepter << std::endl;
        }
        else if (processNumber == 7)
        {
            std::cout << "The count of elements is " << myList.getElementCount() << std::endl;
        }
        else if (processNumber == 8)
        {
            std::cout << "End of processes, thank you dear <3";
            break; // exit the loop and end the program
        }
    }

    return 0; // indicate successful program execution
}
