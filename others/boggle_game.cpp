/*
 *Given a board which is a 2D matrix includes a-z and dictionary dict, find the largest collection of words on the board, the words can not overlap in the same position. return the size of largest collection.
 *
 * Notice
 *
 *The words in the dictionary are not repeated.
 *You can reuse the words in the dictionary.
 *Have you met this question in a real interview? Yes
 *Example
 *Give a board below
 *
 *[['a', 'b', 'c'],
 * ['d', 'e', 'f'],
 * ['g', 'h', 'i']]
 *dict = ["abc", "cfi", "beh", "defi", "gh"]
 *Return 3 // we can get the largest collection["abc", "defi", "gh"]
 */

class Solution {
public:
    int boggleGame(vector<vector<char> > &board, vector<string> &words) {
        for (const string& word: words) {
            add_word(word);
        }
        if (board.empty() || board[0].empty()) {
            return 0;
        }
        const int row = board.size(), col = board[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        find_words(board, 0, 0, &root, 0, 0, NULL, 0, visited);
        return max_count;
    }
private:
    struct TrieNode {
        vector<TrieNode*> next;
        bool end;
        string word;
        TrieNode():next(26, NULL), end(false) {}
    };

    void add_word(const string& word) {
        TrieNode* p = &root;
        for (const char& c: word) {
            if (p->next[c - 'a'] == NULL) {
                p->next[c - 'a'] = new TrieNode();
            }
            p = p->next[c - 'a'];
        }
        p->end = true;
    }

    int max_count = 0;
    TrieNode root;

    void find_words(vector<vector<char> > &board,
                   int x, int y, TrieNode* root,
                   int x1, int y1, TrieNode* p,
                   int count, vector<vector<bool>>& visited) {
        const int row = board.size(), col = board[0].size();
        if (p == NULL) {
            for (int i = x; i < row; ++i) {
                for (int j = y; j < col; ++j) {
                    if (!visited[i][j] && root->next[board[i][j] - 'a']) {
                        find_words(board, i, j, root, i, j, root, count, visited);
                    }
                }
                y = 0;
            }
            return;
        }

        p = p->next[board[x1][y1] - 'a'];
        visited[x1][y1] = true;

        if (p->end) {
            max_count = max(max_count, count+1);
            find_words(board, x, y, root, -1, -1, NULL, count+1, visited);
            visited[x1][y1] = false;
            return;
        }

        vector<int> dx{0, 0, 1, -1}, dy{1, -1, 0, 0};
        for (int k = 0; k < dx.size(); ++k) {
            int x2 = x1 + dx[k], y2 = y1 + dy[k];
            if (x2 >= 0 && x2 < row && y2 >= 0 && y2 < col &&
                !visited[x2][y2] && p->next[board[x2][y2] - 'a']) {
                find_words(board, x, y, root, x2, y2, p, count, visited);
            }
        }

        visited[x1][y1] = false;
    }
};
