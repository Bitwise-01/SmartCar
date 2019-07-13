#pragma once
namespace list
{
template <typename T>
struct node
{
    node(T value) : value(value), next(nullptr) {}

    const T value;
    node *next;
};

template <typename T>
class List
{
public:
    List() : m_root(nullptr), m_size(0U) {}
    ~List();

    void clear();
    unsigned int size() const;
    T peek(unsigned int index);

    void append(T value);
    void insert(unsigned int index, T value);

    T pop();
    T pop(unsigned int index);

private:
    node<T> *m_root;
    unsigned int m_size;
    void m_deleteNode(node<T> *currentNode);
    void m_deleteNode(node<T> *lastNode, node<T> *currentNode);
    void m_append(node<T> *currentNode, T value);
};

template <typename T>
List<T>::~List()
{
    if (m_root != nullptr)
    {
        m_deleteNode(m_root);
    }
}

template <typename T>
void List<T>::m_deleteNode(node<T> *currentNode)
{
    if (m_size > 0)
    {
        if (currentNode->next != nullptr)
        {
            m_deleteNode(currentNode->next);
        }

        delete currentNode;
        m_size--;

        if (m_size == 0)
        {
            m_root = nullptr;
        }
    }
}

template <typename T>
void List<T>::m_deleteNode(node<T> *lastNode, node<T> *currentNode)
{
    if (currentNode->next != nullptr)
    {
        lastNode->next = currentNode->next;
    }

    lastNode->next = nullptr;
    delete currentNode;
    m_size--;
}

template <typename T>
void List<T>::clear()
{
    // Remove all of the items from the list
    m_deleteNode(m_root);
}

template <typename T>
unsigned int List<T>::size() const
{
    return m_size;
}

template <typename T>
void List<T>::append(T value)
{
    if (m_root == nullptr)
    {
        node<T> *rootNode = new node<T>(value);
        m_root = rootNode;
    }
    else
    {
        node<T> *currentNode = m_root;

        while (true)
        {

            if (currentNode->next == nullptr)
            {
                m_append(currentNode, value);
                break;
            }
            else
            {
                currentNode = currentNode->next;
            }
        }
    }

    m_size++;
}

template <typename T>
void List<T>::m_append(node<T> *currentNode, T value)
{
    node<T> *newNode = new node<T>(value);
    currentNode->next = newNode;
}

template <typename T>
void List<T>::insert(unsigned int index, T value)
{
    if (m_root == nullptr)
    {
        append(value);
    }
    else
    {
        unsigned int n = 0U;
        node<T> *lastNode = nullptr;
        node<T> *currentNode = m_root;

        while (n < index)
        {

            if (currentNode->next != nullptr)
            {
                lastNode = currentNode;
                currentNode = currentNode->next;
            }
            else
            {
                break;
            }

            n++;
        }

        if (lastNode != nullptr)
        {
            node<T> *newNode = new node<T>(value);

            lastNode->next = newNode;
            newNode->next = currentNode;
        }
        else if (index == 0)
        {
            node<T> *newroot = new node<T>(value);
            node<T> *oldroot = m_root;

            newroot->next = oldroot;
            m_root = newroot;
        }

        m_size++;
    }
}

template <typename T>
T List<T>::pop()
{
    // Get the item at the end of the list

    T value;
    node<T> *lastNode = nullptr;
    node<T> *currentNode = m_root;

    while (true)
    {
        if (currentNode->next != nullptr)
        {
            lastNode = currentNode;
            currentNode = currentNode->next;
        }
        else
        {
            break;
        }
    }

    if (lastNode != nullptr)
    {
        lastNode->next = nullptr;
    }

    value = currentNode->value;
    m_deleteNode(currentNode);

    return value;
}

template <typename T>
T List<T>::pop(unsigned int index)
{

    T value;
    unsigned int i = 0;
    node<T> *lastNode = m_root;
    node<T> *currentNode = m_root;

    while (i < index)
    {
        if (currentNode->next != nullptr)
        {
            lastNode = currentNode;
            currentNode = currentNode->next;
        }
        else
        {
            break;
        }

        i++;
    }

    value = currentNode->value;

    if (lastNode != currentNode)
    {
        m_deleteNode(lastNode, currentNode);
    }
    else
    { // root node
        if (currentNode->next != nullptr)
        {
            node<T> *newroot = currentNode->next;

            delete m_root;
            m_root = newroot;
        }
        else
        {
            delete m_root;
            m_root = nullptr;
        }
    }

    return value;
}

template <typename T>
T List<T>::peek(unsigned int index)
{
    node<T> *currentNode = m_root;

    for (unsigned int i = 0; i < index; ++i)
    {
        if (currentNode->next != nullptr)
        {
            currentNode = currentNode->next;
        }
    }

    return currentNode->value;
}
} // namespace list