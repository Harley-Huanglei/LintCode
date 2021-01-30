#pragma once

#pragma warning(disable:4018)

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <math.h>
#include <map>
#include <algorithm>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};