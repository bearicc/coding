#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <tuple>

using namespace std;

struct TreeNode {
    string tag;
    string content;
    string tail;
    vector<TreeNode*> next;
    TreeNode(string tag):tag(tag) {}
};

pair<string, string> read(const string& html, int& i) {
    const int N = html.size();
    string text, tag;
    while (i < N && html[i] != '<') {
        text += html[i++];
    }
    ++i;
    while (i < N && html[i] != '>') {
        tag += html[i++];
    }
    ++i; // skip '>'
    return {text, tag};
}

TreeNode* parse(string html) {
    const int N = html.size();
    int i = 0;
    string text, tag;
    stack<TreeNode*> mystack;

    tie(text, tag) = read(html, i);
    if (tag.empty()) {
        return NULL;
    }
    TreeNode* root = new TreeNode(tag);
    mystack.push(root);
    while (i < N) {
        tie(text, tag) = read(html, i);
        if (!tag.empty()) {
            if (tag[0] != '/') {
                mystack.top()->content = text;
                TreeNode* p = new TreeNode(tag);
                mystack.top()->next.push_back(p);
                mystack.push(p);
            } else {
                if (mystack.top()->next.empty()) {
                    mystack.top()->content = text;
                } else {
                    mystack.top()->tail = text;
                }
                mystack.pop();
            }
        }
    }
    return root;
}

void test(TreeNode* root) {
    if (!root) {
        return;
    }
    cout << "(" << root->tag << ") (" << root->content << ") (" << root->tail << ")" << endl;
    for (TreeNode* p: root->next) {
        test(p);
    }
}

int main() {
    string html = "<html><head><title>Test</title></head><body>It works!</body></html>  ";
    cout << html << endl;
    TreeNode* root = parse(html);
    test(root);
    return 0;
}
