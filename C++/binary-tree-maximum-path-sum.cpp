// Time:  O(n)
// Space: O(h)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        return iter_dfs(root);
    }

private:
    int iter_dfs(TreeNode *node) {
        int result = numeric_limits<int>::min(), max_sum = 0;
        vector<tuple<int, TreeNode *, shared_ptr<int>, shared_ptr<int>, int*>> stk = {{1, node, nullptr,  nullptr, &max_sum}};
        while (!stk.empty()) {
            const auto [step, node, ret1, ret2, ret] = stk.back(); stk.pop_back();
            if (step == 1) {
                if (!node) {
                    continue;
                }
                auto ret1 = make_shared<int>(), ret2 = make_shared<int>();
                stk.emplace_back(2, node, ret1, ret2, ret);
                stk.emplace_back(1, node->right, nullptr, nullptr, ret2.get());
                stk.emplace_back(1, node->left, nullptr, nullptr, ret1.get());
            } else if (step == 2) {
                result = max({result, node->val + max(*ret1, 0) + max(*ret2, 0)});
                *ret = node->val + max({*ret1, *ret2, 0});
            }
        }
        return result;
    }
};


// Time:  O(n)
// Space: O(h)
class Solution2 {
public:
    int maxPathSum(TreeNode* root) {
        return dfs(root).first;
    }

private:
    pair<int, int> dfs(TreeNode *node) {
        if (!node) {
            return {numeric_limits<int>::min(), 0};
        }
        const auto& [max_left, curr_left] = dfs(node->left);
        const auto& [max_right, curr_right] = dfs(node->right);
        return {max({max_left, max_right, node->val + max(curr_left, 0) + max(curr_right, 0)}),
                node->val + max({curr_left, curr_right, 0})};
    }
};