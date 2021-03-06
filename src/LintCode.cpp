#include "LintCode.h"

class Solution {
public:
	// 2.两数相加
	static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int add = 0;
		ListNode* head = NULL;
		ListNode* temp;
		while (l1 || l2)
		{
			int m = l1 ? l1->val : 0;
			int n = l2 ? l2->val : 0;
			int k = 0;
			if (m + n + add >= 10)
			{
				k = m + n + add - 10;
				add = 1;
			}
			else
			{
				k = m + n + add;
				add = 0;
			}
			ListNode* l = new ListNode(k);
			if (NULL == head)
			{
				head = l;
				temp = l;
			}
			else
			{
				temp->next = l;
				temp = temp->next;
			}

			l1 = l1 ? l1->next : NULL;
			l2 = l2 ? l2->next : NULL;
		}

		if (add)
		{
			ListNode* l = new ListNode(1);
			temp->next = l;
		}

		return head;
	}

	// 4.两个排序数组的中位数
	static double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int i = 0, j = 0;
		vector<int> num;
		for (; i < nums1.size() || j < nums2.size();)
		{
			if (j == nums2.size())
			{
				num.push_back(nums1[i]);
				i++;
				continue;
			}
			if (i == nums1.size())
			{
				num.push_back(nums2[j]);
				j++;
				continue;
			}
			if (nums1[i] <= nums2[j])
			{
				num.push_back(nums1[i]);
				i++;
			}
			else
			{
				num.push_back(nums2[j]);
				j++;
			}
		}
		double ans;
		size_t k = num.size();
		if (k % 2 == 0)
		{
			ans = (num[k / 2] + num[k / 2 - 1]) / 2.0;
		}
		else
		{
			ans = num[(k - 1) / 2];
		}

		return ans;
	}

	// 5.最大回文子串
	static string longestPalindrome(string s) {
		if (s.size() < 2) return s;
		size_t n = s.size(), maxLen = 0, start = 0;
		for (int i = 0; i < n;) {
			if (n - i <= maxLen / 2) break;
			int left = i, right = i;
			while (right < n - 1 && s[right + 1] == s[right]) ++right;
			i = right + 1;
			while (right < n - 1 && left > 0 && s[right + 1] == s[left - 1]) {
				++right; --left;
			}
			if (maxLen < right - left + 1) {
				maxLen = right - left + 1;
				start = left;
			}
		}
		return s.substr(start, maxLen);
	}

	// 7.反转整数
	static int reverse(int x) {
		int y = 0;
		int k = -1, b = -1;
		do
		{
			k = x / 10;
			b = x % 10;
			if (y > INT_MAX / 10 || (y == INT_MAX / 10 && b > 7)) return 0;
			if (y < INT_MIN / 10 || (y == INT_MIN / 10 && b < -8)) return 0;
			y = y * 10 + b;
			x = k;
		} while (k != 0);
		return y;
	}

	// 9.回文数
	static bool isPalindrome(int x) {
		if (x < 0) return false;
		int tmp = 0;
		int num = x;
		while (num)
		{
			if (tmp > x / 10)
			{
				return false;
			}
			tmp = tmp * 10 + (num % 10);
			num /= 10;
		}
		if (tmp == x)
			return true;
		else
			return false;
	}

	// 14.最长公共前缀
	static string longestCommonPrefix(vector<string>& strs) {
		string s;
		int n = strs.size();
		if (n == 0) return s;

		bool bCommon = true;
		for (int i = 0; i < strs[0].length(); i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (i >= strs[j].length() || strs[j][i] != strs[0][i])
				{
					bCommon = false;
					break;
				}
			}
			if (!bCommon)
			{
				break;
			}
			s += strs[0][i];
		}
		
		return s;
	}

	// 23.合并K个排序链表
	static ListNode* merge2List(ListNode* l1, ListNode* l2)
	{
		if (l1 == NULL) return l2;
		if (l2 == NULL) return l1;
		ListNode l(0);
		ListNode* ptr = &l;
		while (l1 && l2) {
			if (l1->val <= l2->val) {
				ptr->next = l1;
				l1 = l1->next;
			}
			else {
				ptr->next = l2;
				l2 = l2->next;
			}
			ptr = ptr->next;
		}
		if (l1){
			ptr->next = l1;
		}
		if (l2) {
			ptr->next = l2;
		}

		return l.next;
	}
	static ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty()) {
			return NULL;
		}
		if (lists.size() == 1) {
			return lists[0];
		}
		if (lists.size() == 2) {
			return merge2List(lists[0], lists[1]);
		}
		size_t mid = lists.size() / 2;
		vector<ListNode*> sub_list1;
		vector<ListNode*> sub_list2;
		for (int i = 0; i < mid; i++) {
			sub_list1.push_back(lists[i]);
		}
		for (size_t i = mid; i < lists.size(); i++) {
			sub_list2.push_back(lists[i]);
		}
		ListNode* l1 = mergeKLists(sub_list1);
		ListNode* l2 = mergeKLists(sub_list2);
		return  merge2List(l1, l2);
	}
	
	// 55.跳跃游戏
	static bool canJump(vector<int>& nums) {
		int max = 0;
		for (int i = 0; i < nums.size() - 1; i++)
		{
			max = max > nums[i] ? max : nums[i];
			if (max == 0)
			{
				return false;
			}

			max--;
		}

		return true;
	}

	// 80.删除排序数组中的重复项 II
	static int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0)  return 0;
		int ans = 1;
		bool bFrist = true;
		int pre = nums[0];
		vector<int>::iterator it = nums.begin();
		it++; 
		while (it != nums.end())
		{
			if (*it ==  pre && bFrist)
			{
				bFrist = false;
				ans++;
				it++;
			}
			else if (*it != pre)
			{
				pre = *it;
				bFrist = true;
				ans++;
				it++;
			}
			else
			{
				it = nums.erase(it);
			}
		}

		return ans;
	}

	// 92.翻转链表II
	static ListNode* reverseBetween(ListNode* head, int m, int n) {
		ListNode preHead(0);
		preHead.next = head;
		ListNode* pre = &preHead;
		ListNode* tmp = head;
		for (int i = 1; i <  m && tmp ; i++)
		{
			pre = pre->next;
			tmp = tmp->next;
		}

		ListNode* tmp1 = tmp;
		ListNode* tmp2 = tmp1->next;
		ListNode* tmp3 = NULL;
		for (int i = m; i < n; i++)
		{
			tmp3 = tmp2->next;
			tmp2->next = tmp1;
			tmp1 = tmp2;
			tmp2 = tmp3;
		}

		pre->next = tmp1;
		tmp->next = tmp2;

		return preHead.next;
	}

	// 106.从中序与后序遍历序列构造二叉树
	static TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		if (inorder.size() == 0 || postorder.size() == 0) return NULL;
		vector<int> li, lp, ri, rp;
		int k = postorder[postorder.size() - 1];
		TreeNode* head = new TreeNode(k);
		if (postorder.size() == 1)
			return head;
		int m = 0, n = 0;
		for (int i = 0; i < inorder.size(); i++)
		{
			bool bFindHead = false;
			if (inorder[i] != k)
			{
				if (!bFindHead)
				{
					li.push_back(inorder[i]);
					m++;
				}
				else
				{
					ri.push_back(inorder[i]);
					n++;
				}
			}
			else
			{
				bFindHead = true;
			}
		}

		for (int i = 0; i < postorder.size(); i++)
		{
			if (i < m)
			{
				lp.push_back(postorder[i]);
			}
			else if (i < m + n)
			{
				rp.push_back(postorder[i]);

			}
		}

		head->left = buildTree(li, lp);
		head->right = buildTree(ri, rp);

		return head;
	}

	// 110. 平衡二叉树
	static int balance(TreeNode* node)
	{
		if (node == NULL)
			return 0;
		int left = balance(node->left);
		if (left == -1)
			return -1;
		int right = balance(node->right);
		if (right == -1)
			return -1;
		if (abs(left - right) > 1)
			return -1;
		return max(left, right) + 1;
	}
	static bool isBalanced(TreeNode* root) {
		return balance(root) != -1;
	}

	// 121.买卖股票最佳时机
	static int maxProfit(vector<int>& prices) {
		if (prices.size() <= 1) return 0;
		int min = prices[0];
		int max = 0;
		for (int i = 1; i < prices.size(); i++)
		{
			if (prices[i] > min)
			{
				int a = prices[i] - min;
				max = max < a ? a : max;
			}
			else
			{
				min = prices[i];
			}
		}

		return max;
	}

	// 148.排序链表
	static ListNode* sortList(ListNode* head) {
		if (head == NULL || head->next == NULL) return head;

		ListNode* slow = head;
		ListNode* fast = head;
		ListNode* brkN = head;
		while (fast && fast->next)
		{
			brkN = slow;
			slow = slow->next;
			fast = fast->next->next;
		}

		brkN->next = NULL;
		ListNode* l1 = sortList(head);
		ListNode* l2 = sortList(slow);

		return merge2List(l1, l2);
	}

	// 151.翻转字符串里的单词
	static string reverseWords(string s) {

	}

	// 206.反转链表
	static ListNode* reverseList(ListNode* head) {
		if (NULL == head)  return head;

		ListNode* pFir = head;
		ListNode* pSec = pFir->next;
		pFir->next = NULL;
		while (pSec)
		{
			ListNode* pThi = pSec->next;
			pSec->next = pFir;

			pFir = pSec;
			pSec = pThi;
		}

		return pFir;
	}

	// 221.最大正方形
	static int maximalSquare(vector<vector<char>>& matrix) {
		size_t m = matrix.size();
		if (m == 0) return 0;
		size_t n = matrix[0].size();

		int res = 0;
		vector<vector<int>> a(m, vector<int>(n, 0));

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == 0 || j == 0) a[i][j] = matrix[i][j] - '0';
				else if (matrix[i][j] == '1') {
					a[i][j] = min(a[i - 1][j - 1], min(a[i][j - 1], a[i - 1][j])) + 1;
				}
				res = max(res, a[i][j]);
			}
		}

		return res * res;
	}

	// 237. 删除链表中的节点
	static void deleteNode(ListNode* node) {
		if (node == NULL) return;
		ListNode* pNext = node->next;
		node->val = pNext->val;	
		node->next = pNext->next;
	}

	// 322.零钱兑换 
	static int coinChange(vector<int>& coins, int amount) {
		if (coins.size() == 0) return -1;
		if (amount == 0) return 0;
		sort(coins.begin(), coins.end());
		int a[200][1000];
		for (int j = 1; j <= amount; j++)
		{
			a[0][j] = j % coins[0] == 0 ? j / coins[0] : -1;
		}
		for (int i = 1; i < coins.size() && coins[i] < amount; i++)
		{
			for (int j = 1; j <= amount; j++)
			{
				a[i][j] = -1;
				if (j%coins[i] == 0)
				{
					a[i][j] = j / coins[i];
				}
				else
				{
					for (int k = j / coins[i]; k >= 0; k--)
					{
						if (a[i - 1][j - k * coins[i]] != -1)
						{
							int p = k + a[i - 1][j - k * coins[i]];
							if (a[i][j] > p || a[i][j] == -1)
							{
								a[i][j] = p;
							}
						}
					}
				}
				cout << a[i][j] << endl;
			}

		}
		return a[coins.size() - 1][amount];
	}

	// 354. 俄罗斯套娃信封问题
	static bool cmp(const pair<int, int> a, const pair<int, int> b) {
		return a.first == b.first ? a.second < b.second : a.first < b.first;
	}
	static int maxEnvelopes(vector<std::vector<int>>& envelopes) {
		int n = envelopes.size();
		if (n <= 1) return n;

		vector<pair<int, int>> e;
		for (int i = 0; i < n; i++)
		{
			e.push_back(pair<int, int>(envelopes[i][0], envelopes[i][1]));
		}
		sort(e.begin(), e.end(), cmp);
		vector<int> dp(n);
		int ret = 0;
		for (int j = 0; j < n; j++) {
			dp[j] = 1;
			for (int i = 0; i < j; i++) {
				if (e[i].first < e[j].first) {
					if (e[i].second < e[j].second && dp[i] + 1 > dp[j]) {
						dp[j] = dp[i] + 1;
					}
				}
			}
			ret = max(ret, dp[j]);
		}
		return ret;
	}

	// 395.至少有K个重复字符的最长子串
	static int longestSubstring(string s, int k) {
		if (k <= 1)
		{
			return s.length();
		}
		int a[256] = { 0 };
		for (int i = 0; i < s.length(); i++)
		{
			a[s[i]]++;
		}

		int c = 0;
		bool bFull = true;
		for (; c < 256; c++)
		{
			if (a[c] < k && a[c] > 0)
			{
				bFull = false;
				break;
			}
		}

		if (bFull) return s.length();
		size_t pos = s.find(c);
		string left = s.substr(0, pos);
		string right = s.substr(pos+1);

		return max(longestSubstring(left, k), longestSubstring(right, k));
	}

	// 397.整数替换
	static int integerReplacement(int n) {
		if (n == 1) return 0;
		if (n % 2)
		{
			if (n == INT_MAX) {
				return integerReplacement(n >> 1) + 1;
			}
			return min(integerReplacement(n - 1), integerReplacement(n + 1)) + 1;
		}
		else
		{
			return integerReplacement(n >> 1) + 1;
		}
	}

	// 413. 等差数列划分
	static int numberOfArithmeticSlices(vector<int>& A) {
		vector<int> a;
		int j = 0;
		if (A.size() <= 2)
		{
			return 0;
		}
		for (int i = 0; i < A.size() - 2; i++)
		{
			if (A[i] + A[i + 2] == 2 * A[i + 1])
			{
				j++;
			}
			else
			{
				a.push_back(j);
				j = 0;
			}
		}

		a.push_back(j);

		int ans = 0;
		for (int i = 0; i < a.size(); i++)
		{
			ans += a[i]*(a[i]+1)/2;
		}

		return ans;
	}

	// 518.零钱兑换2
	int change(int amount, vector<int>& coins) {
		if (amount == 0) return 1;
		if (coins.size() == 0) return 0;
		int a[500][5001] = { 0 };
		for (int i = 0; i < coins.size(); i++)
		{
			for (int j = 1; j <= amount; j++)
			{
				if (i == 0)
				{
					if (j % coins[i] == 0) a[i][j] = 1;
					else a[i][j] = 0;
					continue;
				}
				int k = j / coins[i];
				while (k >= 0)
				{
					if (j - k * coins[i] == 0)
					{
						a[i][j]++;
					}
					else
					{
						a[i][j] += a[i - 1][j - k * coins[i]];
					}
					k--;
				}
			}
		}

		return  a[coins.size() - 1][amount];
	}

	// 575.分糖果
	static int distributeCandies(vector<int>& candies) {
		set<int> sa;
		int size = candies.size();

		for (int i = 0; i < size; i++)
		{
			sa.insert(candies[i]);
		}

		if (sa.size() > size / 2)
		{
			return size / 2;
		}
		else
		{
			return sa.size();
		}
	}

	// 530. 二叉搜索树的最小绝对差
	static int getMinimumDifference(TreeNode* root) {
		if (NULL == root) return 0;
		stack<TreeNode*> st;
		TreeNode* tmp = root;
		int val1, val2, valt, dif = INT_MAX;
		bool isFirst = true;
		while (tmp || !st.empty())
		{
			if (tmp)
			{
				st.push(tmp);
				tmp = tmp->left;
			}
			else
			{
				tmp = st.top();
				st.pop();
				if (isFirst)
				{
					val1 = tmp->val;
					isFirst = false;
				}
				else
				{
					val2 = tmp->val;
					valt = val2 - val1;
					if (dif > valt)
					{
						dif = valt;
					}
					val1 = val2;
				}
				tmp = tmp->right;
			}
		}

		return dif;
	}

	// 682.棒球比赛
	static int calPoints(vector<string>& ops) {
		int a[1000] = { 0 };
		int k = -1;
		for (int i = 0; i < ops.size(); i++)
		{
			if (ops[i] == "D")
			{
				if (k != -1)
				{
					a[k + 1] = 2 * a[k];
					k++;
				}
			}
			else if (ops[i] == "C")
			{
				if (k != -1)
				{
					a[k] = 0;
					k--;
				}
			}
			else if (ops[i] == "+")
			{
				if (k == -1)
				{
					a[0] = 0; k = 0;
					continue;
				}
				if (k == 0)
				{
					a[1] = a[0]; k = 1;
					continue;
				}
				a[k + 1] = a[k] + a[k - 1];
				k++;
			}
			else
			{
				int goal = atoi(ops[i].c_str());
				a[k+1] = goal;
				k++;
			}
		}

		int ans = 0;
		for (int i = 0; i <= k; i++)
		{
			ans += a[i];
		}

		return ans;
	}

	// 789.逃脱阻碍者
	static bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
		int step = abs(target[0]) + abs(target[1]);
		for (int i = 0; i < ghosts.size(); i++)
		{
			if (abs(ghosts[i][0] - target[0]) + abs(ghosts[i][1] - target[1]) <= step)
			{
				return false;
			}
		}

		return true;
	}

	// 852.山脉数组的峰顶索引
	static int peakIndexInMountainArray(vector<int>& A) {
		int i = 0;
		for (; i < A.size()-1; i++)
		{
			if (A[i] > A[i + 1]) break;
		}

		return i;
	}

	// 876.链表的中间结点
	static ListNode* middleNode(ListNode* head) {
		if (!head)  return NULL;
		if (!head->next) return head;
		ListNode* n = head;
		ListNode* nn = head;
		while (nn && nn->next)
		{
			n = n->next;
			nn = nn->next->next;
		}
		return n;
	}

	// 976. 三角形的最大周长
	static int largestPerimeter(vector<int>& A) {
		if (A.size() < 3) return 0;
		sort(A.begin(), A.end());
		int cl = 0;
		for (int i = A.size() - 1; i > 1; i--)
		{
			if (A[i] < A[i - 1] + A[i - 2])
			{
				cl = A[i] + A[i - 1] + A[i - 2];
				break;
			}
		}

		return cl;
	}

	// 991. 坏了的计算器
	static int brokenCalc(int X, int Y) {
		if (Y <= X) return X - Y;

		if (Y % 2)
		{
			return min(brokenCalc(X, Y - 1), brokenCalc(X, Y + 1)) + 1;
		}
		else
		{
			return brokenCalc(X, Y / 2) + 1;
		}
	}
};

int main()
{
	vector<vector<int> > gh = { {1, 9},{2, -5},{3, 8},{9, 8},{-1, 3} };
	vector<int> target = { 1, 1, 1, 2, 2, 3 };
	vector<string> ops = { "5","2","C","D","+" };
	string s = "aacdefcaa";
	
	ListNode* ln = new ListNode(-1);
	int a[5] = { 1,2,3,4,5 };
	ListNode* ltmp = ln;
	for (int i = 0; i < 5; i++)
	{
		ListNode *l = new ListNode(a[i]);
		ltmp->next = l;
		ltmp = ltmp->next;
	}
	
	int ans = Solution::removeDuplicates(target);
}