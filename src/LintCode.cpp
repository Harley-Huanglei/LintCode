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

	// 翻转链表II
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

	// 518.零钱兑换2
	static int change(int amount, vector<int>& coins) {
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
};

int main()
{
	vector<vector<int> > gh = { {1, 9},{2, -5},{3, 8},{9, 8},{-1, 3} };
	vector<int> target = { 8, -10 };
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

	ListNode * ans = Solution::reverseBetween(ln->next, 2, 4);
}