#ifndef TRANSACTION_BST_HPP
#define TRANSACTION_BST_HPP

#include "Transaction.hpp"
#include "Utils.hpp"
#include <memory>
#include <iostream>

struct TreeNode {
    Transaction* data; 
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(Transaction* t) : data(t), left(nullptr), right(nullptr) {}
};

class TransactionBST {
private:
    std::unique_ptr<TreeNode> root;

    void insertNode(std::unique_ptr<TreeNode>& node, Transaction* t) {
        if (!node) {
            node = std::make_unique<TreeNode>(t);
            return;
        }
        if (t->getAmount() < node->data->getAmount()) {
            insertNode(node->left, t);
        } else {
            insertNode(node->right, t);
        }
    }

    void inorderTraversal(const std::unique_ptr<TreeNode>& node) const {
        if (node) {
            inorderTraversal(node->left);
            node->data->display();
            inorderTraversal(node->right);
        }
    }

    void searchAboveAmountRecursive(const std::unique_ptr<TreeNode>& node, double minAmount, bool& found) const {
        if (node) {
            // Duyệt cây: Nếu node nhỏ hơn minAmount, chỉ tìm ở nhánh phải
            if (node->data->getAmount() >= minAmount) {
                searchAboveAmountRecursive(node->left, minAmount, found);
                node->data->display();
                found = true;
                searchAboveAmountRecursive(node->right, minAmount, found);
            } else {
                searchAboveAmountRecursive(node->right, minAmount, found);
            }
        }
    }

public:
    TransactionBST() : root(nullptr) {}

    void insert(Transaction* t) { insertNode(root, t); }

    void displaySortedByAmount() const {
        if (!root) {
            std::cout << "  [INFO] No transactions available to sort.\n";
            return;
        }
        inorderTraversal(root);
    }

    void displayAboveAmount(double minAmount) const {
        if (!root) {
            std::cout << "  [INFO] Tree is empty.\n";
            return;
        }
        bool found = false;
        searchAboveAmountRecursive(root, minAmount, found);
        if (!found) {
            std::cout << "  [INFO] No transactions found above " << formatWithDollar(minAmount) << ".\n";
        }
    }
};

#endif