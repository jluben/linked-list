/**
 * tests.cpp
 * 
 * @brief unit tests to validate LinkedList functionality.
 * 
 * Author: Joshua P. Luben
*/
#include <gtest/gtest.h>
#include "linkedlist.h"

TEST(LinkedListTest, Instantiation) 
{
    LinkedList<std::string>* ll = new LinkedList<std::string>();
    EXPECT_EQ(ll->front(), nullptr);
    EXPECT_EQ(ll->back(), nullptr);
    delete ll;
}

TEST(LinkedListTest, AddFrontParamCheck) 
{
    std::shared_ptr<LinkedList<int>> list(new LinkedList<int>());
    EXPECT_FALSE(list->addFront(nullptr));
}

TEST(LinkedListTest, AddBackParamCheck) 
{
    std::shared_ptr<LinkedList<int>> list(new LinkedList<int>());
    EXPECT_FALSE(list->addBack(nullptr));
}


TEST(LinkedListTest, StringListNode) 
{
    std::shared_ptr<LinkedList<std::string>> list(new LinkedList<std::string>());
    
    LinkedList<std::string>::Node node;
    EXPECT_EQ(node.data(), nullptr);
    std::shared_ptr<std::string> string_ptr(new std::string("red blue green"));
    node.setData(string_ptr);
    EXPECT_EQ(*(node.data()), "red blue green");
}

TEST(LinkedListTest, AddFront) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);

    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("hello"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node1));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    EXPECT_EQ(node1->next(), nullptr);
    EXPECT_EQ(node1->previous(), nullptr);
    
    // Add Node 2
    string_ptr = std::shared_ptr<std::string>(new std::string("world"));
    StringLinkedList::Node* node2 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node2));
    
    EXPECT_EQ(list->front(), node2);
    EXPECT_EQ(node2->next(), node1);
    EXPECT_EQ(list->back(), node1);
    EXPECT_EQ(node1->previous(), node2);
    EXPECT_EQ(node1->next(), nullptr);
    
    // Add Node 3
    string_ptr = std::shared_ptr<std::string>(new std::string("red"));
    StringLinkedList::Node* node3 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node3));
    
    EXPECT_EQ(list->front(), node3);
    EXPECT_EQ(list->back(), node1);
    EXPECT_EQ(node3->next(), node2);
    EXPECT_EQ(node3->previous(), nullptr);
}

TEST(LinkedListTest, AddBack) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);

    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("hello"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node1));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    
    // Add Node 2
    string_ptr = std::shared_ptr<std::string>(new std::string("world"));
    StringLinkedList::Node* node2 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node2));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(node2->next(), nullptr);
    EXPECT_EQ(node2->previous(), node1);
    EXPECT_EQ(list->back(), node2);
    EXPECT_EQ(node1->next(), node2);
    
    // Add Node 3
    string_ptr = std::shared_ptr<std::string>(new std::string("blue"));
    StringLinkedList::Node* node3 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node3));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node3);
    EXPECT_EQ(node3->next(), nullptr);
    EXPECT_EQ(node3->previous(), node2);


    EXPECT_EQ(*(list->front()->data()), "hello");
    EXPECT_EQ(*(list->back()->data()), "blue");
}


TEST(LinkedListTest, AddFrontAndBack) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);

    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("first"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node1));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    EXPECT_EQ(*(node1->data()), "first");
    
    // Add Node 2
    string_ptr = std::shared_ptr<std::string>(new std::string("last"));
    StringLinkedList::Node* node2 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node2));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(node2->next(), nullptr);
    EXPECT_EQ(node2->previous(), node1);
    EXPECT_EQ(list->back(), node2);
    EXPECT_EQ(node1->next(), node2);
    EXPECT_EQ(*(node2->data()), "last");
    
}


TEST(LinkedListTest, Clear) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);
    
    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("beta"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node1));
    // Add Node 2
    string_ptr = std::shared_ptr<std::string>(new std::string("gamma"));
    StringLinkedList::Node* node2 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node2));
    
    list->clear();

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);
}


TEST(LinkedListTest, SimpleRemove) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);

    EXPECT_FALSE(list->remove(nullptr));

    /*
    // Ideally this would work; but it has performance implications.
    StringLinkedList::Node* dummyNode = new StringLinkedList::Node("dummy");
    EXPECT_FALSE(list->remove(dummyNode));
    delete dummyNode;
    */

    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("first"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node1));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    EXPECT_EQ(*(node1->data()), "first");
    
    list->remove(node1);
    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);
    
}


TEST(LinkedListTest, AddFrontAndBackThenRemove) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);

    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("first"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addFront(node1));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    EXPECT_EQ(*(node1->data()), "first");
    
    // Add Node 2
    string_ptr = std::shared_ptr<std::string>(new std::string("last"));
    StringLinkedList::Node* node2 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node2));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(node2->next(), nullptr);
    EXPECT_EQ(node2->previous(), node1);
    EXPECT_EQ(list->back(), node2);
    EXPECT_EQ(node1->next(), node2);
    EXPECT_EQ(*(node2->data()), "last");
    
    // Now remove 1
    list->remove(node1);
    EXPECT_EQ(list->front(), node2);
    EXPECT_EQ(list->back(), node2);
    
    EXPECT_EQ(node2->next(), nullptr);
    EXPECT_EQ(node2->previous(), nullptr);
    EXPECT_EQ(*(list->front()->data()), "last");
    
    // Now remove 2
    EXPECT_TRUE(list->remove(node2));
    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);
}


TEST(LinkedListTest, RemoveMiddle) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);

    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("hello"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node1));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    
    // Add Node 2
    string_ptr = std::shared_ptr<std::string>(new std::string("world"));
    StringLinkedList::Node* node2 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node2));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(node2->next(), nullptr);
    EXPECT_EQ(node2->previous(), node1);
    EXPECT_EQ(list->back(), node2);
    EXPECT_EQ(node1->next(), node2);
    
    // Add Node 3
    string_ptr = std::shared_ptr<std::string>(new std::string("blue"));
    StringLinkedList::Node* node3 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node3));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node3);
    EXPECT_EQ(node3->next(), nullptr);
    EXPECT_EQ(node3->previous(), node2);


    // Remove middle node
    EXPECT_TRUE(list->remove(node2));
    delete node2;
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node3);
    EXPECT_EQ(*(list->front()->data()), "hello");
    EXPECT_EQ(*(list->back()->data()), "blue");
    
    // Remove node 3
    EXPECT_TRUE(list->remove(node3));
    delete node3;
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    EXPECT_EQ(*(list->front()->data()), "hello");
}


TEST(LinkedListTest, RemoveFrontAndBack) 
{
    using StringLinkedList = LinkedList<std::string>;
    std::shared_ptr<StringLinkedList> list(new StringLinkedList());

    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);

    // Add Node 1
    std::shared_ptr<std::string> string_ptr(new std::string("hello"));
    StringLinkedList::Node* node1 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node1));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node1);
    
    // Add Node 2
    string_ptr = std::shared_ptr<std::string>(new std::string("middle"));
    StringLinkedList::Node* node2 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node2));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(node2->next(), nullptr);
    EXPECT_EQ(node2->previous(), node1);
    EXPECT_EQ(list->back(), node2);
    EXPECT_EQ(node1->next(), node2);
    
    // Add Node 3
    string_ptr = std::shared_ptr<std::string>(new std::string("blue"));
    StringLinkedList::Node* node3 = new StringLinkedList::Node(string_ptr);
    EXPECT_TRUE(list->addBack(node3));
    
    EXPECT_EQ(list->front(), node1);
    EXPECT_EQ(list->back(), node3);
    EXPECT_EQ(node3->next(), nullptr);
    EXPECT_EQ(node3->previous(), node2);


    // Remove middle node
    EXPECT_TRUE(list->remove(node1));
    delete node1;
    EXPECT_TRUE(list->remove(node3));
    delete node3;
    
    // Verify node 2
    EXPECT_EQ(list->front(), node2);
    EXPECT_EQ(list->back(), node2);
    EXPECT_EQ(*(list->front()->data()), "middle");
    EXPECT_EQ(node2->previous(), nullptr);
    EXPECT_EQ(node2->next(), nullptr);
}


TEST(LinkedListTest, LinearEight) 
{
    using IntList = LinkedList<int>;
    std::shared_ptr<IntList> list(new IntList());

    // Insert eight
    for (auto i=0 ; i < 8 ; ++i) {
        
        std::shared_ptr int_ptr = std::shared_ptr<int>(new int);
        *int_ptr = i;
        IntList::Node* node = new IntList::Node(int_ptr);
        EXPECT_TRUE(list->addBack(node));
    }
    
    // Verify
    int idx=0;
    IntList::Node* node = list->front();

    while (node) {
        EXPECT_NE(node->data(), nullptr);
        EXPECT_EQ(*(node->data()), idx);
        node = node->next();
        ++idx;
    }

    // Remove
    node = list->back();

    idx = 7;
    while (node) {
        list->remove(node);
        delete node;
        node = list->back();
        --idx;
        
        if (node) {
            EXPECT_NE(node->data(), nullptr);
            EXPECT_EQ(*(node->data()), idx);
        }
    }
    
    EXPECT_EQ(list->front(), nullptr);
    EXPECT_EQ(list->back(), nullptr);
}
