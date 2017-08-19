/*
 * Convert a binary search tree to doubly linked list with in-order traversal.
 * 
 * Have you met this question in a real interview? Yes
 * Example
 * Given a binary search tree:
 * 
 *     4
 *    / \
 *   2   5
 *  / \
 * 1   3
 * return 1<->2<->3<->4<->5
 */

/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 * Definition of Doubly-ListNode
 * class DoublyListNode {
 * public:
 *     int val;
 *     DoublyListNode *next, *prev;
 *     DoublyListNode(int val) {
 *         this->val = val;
           this->prev = this->next = NULL;
 *     }
 * }
 */
class Solution {
public:
    DoublyListNode* bstToDoublyList(TreeNode* root) {
        return helper(root).first;
    }
private:
    typedef pair<DoublyListNode*, DoublyListNode*> Ret;
    Ret helper(TreeNode* root) {
        if (!root) {
            return {NULL, NULL};
        }
        DoublyListNode* head = new DoublyListNode(root->val);
        DoublyListNode* tail = head;
        if (root->left) {
            Ret left = helper(root->left);
            left.second->next = head;
            head->prev = left.second;
            head = left.first;
        }
        if (root->right) {
            Ret right = helper(root->right);
            right.first->prev = tail;
            tail->next = right.first;
            tail = right.second;
        }
        return {head, tail};
    }
};
