#include "iostream"
#include "fstream"
using namespace std;
const int maxDinh = 20;
bool visited[maxDinh] = { false };

struct node {
	int dinhKe;
	int trongSo;
	node* link;
};

struct danhSachKe {
	node* dsk[maxDinh];
	int soDinh; // số đỉnh của graph
};

void readFile(danhSachKe& list) {
	ifstream inFile("AdjacencyList.txt");
	if (!inFile.is_open()) {
		cout << "\nKhong the mo tep.";
		return;
	}
	// cho danh sách = null hết
	for (int i = 0; i < maxDinh; i++)
		list.dsk[i] = NULL;
	// Nhap số đỉnh tổng
	inFile >> list.soDinh;
	for (int i = 0; i < list.soDinh; i++) {
		int soDinhKe;
		inFile >> soDinhKe;
		for (int j = 0; j < soDinhKe; j++) {
			node* newNode = new node();
			inFile >> newNode->dinhKe;
			inFile >> newNode->trongSo;
			newNode->link = NULL;
			// Thêm vào single list theo đỉnh tương ứng 
			if (list.dsk[i] == NULL)  // chưa có đỉnh kề nào hết 
				list.dsk[i] = newNode;
			else { // đã có đỉnh kề trước đó thêm vào cuối single list 
				node* temp = list.dsk[i];
				while (temp->link != NULL)
					temp = temp->link;
				temp->link = newNode;
			}
		}
	}
}

void xuatDanhSachKe(danhSachKe list) {
	cout << "GRAPH";
	for (int i = 0; i < list.soDinh; i++) {
		cout << "\n(" << i << "): ";
		node* pointer = list.dsk[i];
		while (pointer) {
			cout << "(" << pointer->dinhKe << "," << pointer->trongSo << ") ";
			pointer = pointer->link;
		}
	}
}

void DFS(int u, danhSachKe list) {
	cout << u << " ";
	visited[u] = true; // đánh dấu đỉnh u đã được thăm 

	// Duyệt qua tất cả các đỉnh kề của u
	node* temp = list.dsk[u];
	while (temp != NULL) {
		int v = temp->dinhKe;
		if (!visited[v])
			DFS(v, list);
		temp = temp->link;
	}
}

void connectComponent(danhSachKe list) {
	int count = 0;
	for (int i = 1; i <= list.soDinh; i++) {
		if (visited[i] == false) {
			count++;
			cout << "\nCac dinh thuoc thanh phan lien thong thu " << count << ": ";
			DFS(i, list);
			cout << endl;
		}
	}
	if (count == 1)
		cout << "Do thi lien thong";
	else {
		cout << "Do thi khong lien thong";
		cout << "\nSo thanh phan lien thong cua do thi: " << count;
	}
}

int main() {
	danhSachKe list;
	readFile(list);
	xuatDanhSachKe(list);
	connectComponent(list);
}
