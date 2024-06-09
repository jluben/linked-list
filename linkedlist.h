/**
 * linkedlist.h
 * 
 * @brief A cursory implementation of a linked list.
 * 
 * Author: Joshua P. Luben
*/
#pragma once

/**
 @brief Node class that is used by the linked list.
*/
template <typename T>
class LinkedListNode
{
public:
    using LinkedListNodePtr = LinkedListNode<T>*;

    LinkedListNode() {
    }
    LinkedListNode(std::shared_ptr<T> data) {
        m_Data = data;
    }

    std::shared_ptr<T> data() const {   
        return m_Data;
    };
    void setData(std::shared_ptr<T> data) {
        m_Data = data;
    }

    LinkedListNodePtr previous() {
        return m_Previous;
    }
    void setPrevious(LinkedListNodePtr previous) {
        m_Previous = previous;
    }
    LinkedListNodePtr next() {
        return m_Next;
    }
    void setNext(LinkedListNodePtr next) {
        m_Next = next;
    }

private:
    // In a better implementation, T might be a std::shared_ptr
    std::shared_ptr<T> m_Data;
    LinkedListNodePtr m_Previous=nullptr;
    LinkedListNodePtr m_Next=nullptr;
};

template <typename T>
class LinkedList
{
public:
    /**
     * @brief Templates can be pretty, verbose, so hide the wordy-type behind "Node"
    */
    using Node = LinkedListNode<T>;

    /**
     * @brief This is a bidirectional iterator
    */
    template <typename T>
    class iterator {
        public:
            iterator(Node* current) {
                m_Current = current;
            }
            iterator& operator=(const iterator& iter) {
                m_Current = iter.m_Current;
                return *this;
            }
            bool operator==(const iterator& iter) const {
                return (m_Current == iter.m_Current);
            }

            iterator& operator++() {
                next();
                return *this;
            }

            bool next() {
                if (m_Current) {
                    Node* next = m_Current->next();
                    if (next) {
                        m_Current = next;
                        return true;
                    }
                }

                return false;
            }


            iterator& operator--() {
                previous();
                return *this;
            }

            bool previous() {
                if (m_Current) {
                    Node* prev = m_Current->previous();
                    if (prev) {
                        m_Current = prev;
                        return true;
                    }
                }

                return false;
            }

            std::shared_ptr<T> operator*() {
                if (m_Current) {
                    return m_Current->data();
                }

                return nullptr;
            }
        private:
            Node* m_Current=nullptr;
    };

    ~LinkedList() {
        clear();
    }

    iterator<T> begin() const {
        return iterator<T>(m_Front);
    }
    iterator<T> end() const {
        return iterator<T>(m_Back);
    }

    void clear() {
        //
        // Cleanup the list.
        //
        Node* node = m_Front;
        Node* next = nullptr;
        
        if (node)
        {
            while (node)
            {
                next = node->next();
                delete node;
                node = next;
            }
        }

        m_Front = nullptr;
        m_Back = nullptr;
    }

    Node* front() const { 
        return m_Front;
    }
    Node* back() const { 
        return m_Back;
    }

    /**
     * @brief Insert a node into the front of the list.
     * Insertion time O(1)
    */
    bool addFront(Node* node) {
        if (node) {
            Node* front = m_Front;
            m_Front = node;
            node->setNext(front);
            if (front) {
                front->setPrevious(node);
            }  else {
                m_Back = node;
            }
            return true;
        }

        return false;
    }

    /**
     * @brief Insert a node at the back of the list
     * Insertion time O(1)
    */
    bool addBack(Node* node) {
        if (node) {
            Node* back = m_Back;
            m_Back = node;
            node->setPrevious(back);
            if (back) {
                back->setNext(node);
            } else {
                m_Front = node;
            }
            return true;
        }

        return false;
    }

    /**
     * @brief Remove a node from the list
     * Execution time O(1)
     * 
     * This function does not release the node, that is up to the caller.
     * Gap: This does not actually check to see if the node is in the list.
    */
    bool remove(Node* node) {
        if (node) {
            Node* previous = node->previous();
            Node* next = node->next();

            if (previous) {
                previous->setNext(next);
            }
            if (next) {
                next->setPrevious(previous);
            }
            if (m_Front == node) {
                m_Front = next;
            }
            if (m_Back == node) {
                m_Back = previous;
            }

            return true;
        }

        return false;
    }
    
    Node* operator[](size_t index) const {
        size_t current_index = 0;
        Node* node = m_Front;
        
        if (node)
        {
            while (node && current_index <= index)
            {
                if (current_index == index) {
                    return node;
                }
                node = node->next();
                ++current_index;
            }
        }

        return nullptr;
    }

    /**
     * @brief Determine the size of the list.
     * This takes O(n)
    */
    size_t size() const {
        size_t list_size = 0;
        Node* node = m_Front;
        Node* next = nullptr;
        
        if (node)
        {
            while (node)
            {
                next = node->next();
                ++list_size;
                node = next;
            }
        }

        return list_size;
    }

private:
    Node* m_Front=nullptr;
    Node* m_Back=nullptr;
};