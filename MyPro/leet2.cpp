//#include "iostream"
//using namespace std;
//
//struct ListNode {
//	int val;
//	ListNode* next;
//	ListNode(int x) : val(x), next(NULL) {}
//};
//
//ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//	if (l1 == NULL)
//		return l2;
//	if (l2 == NULL)
//		return l1;
//	bool jin = ((l1->val+l2->val)/10)==1?true:false;
//	ListNode* pnew = new ListNode((l1->val + l2->val) % 10);
//	ListNode* pnode = pnew;
//	while (l1->next != NULL || l2->next != NULL) {
//		ListNode* pnext;
//		if (l1->next == NULL) {
//			l2 = l2->next;
//			pnext = new ListNode((l2->val + (jin ? 1 : 0))%10);
//			if ((l2->val + (jin ? 1 : 0)) / 10 == 1)
//				jin = true;
//			else
//				jin = false;
//		}
//		else if (l2->next == NULL) {
//			l1 = l1->next;
//			pnext = new ListNode((l1->val + (jin ? 1 : 0))%10);
//			if ((l1->val + (jin ? 1 : 0)) / 10 == 1)
//				jin = true;
//			else
//				jin = false;
//		}
//		else {
//			l1 = l1->next;
//			l2 = l2->next;
//			pnext = new ListNode((l1->val+l2->val + (jin ? 1 : 0))%10);
//			if ((l1->val + l2->val + (jin ? 1 : 0)) / 10 == 1)
//				jin = true;
//			else
//				jin = false;
//		}
//		pnode->next = pnext;
//		pnode = pnode->next;
//	}
//	if (jin == true) {
//		pnode->next = new ListNode(1);
//	}
//	return pnew;
//}
//
//int main() {
//	ListNode * node1_0 = new ListNode(9);
//	ListNode * node1_1 = new ListNode(9);
//	ListNode * node1_2 = new ListNode(9);
//	ListNode * node2_0 = new ListNode(1);
//	ListNode * node2_1 = new ListNode(1);
//	ListNode * node2_2 = new ListNode(1);
//	node1_0->next = node1_1;
//	node1_1->next = node1_2;
//	node2_0->next = node2_1;
//	node2_1->next = node2_2;
//	ListNode* pnew=addTwoNumbers(node1_0, node2_0);
//	while (pnew != NULL) {
//		cout << pnew->val<<"  ";
//		pnew = pnew->next;
//	}
//	cout << endl;
//}