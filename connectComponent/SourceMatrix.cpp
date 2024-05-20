#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

const int MAX = 20;

struct maTrix {
    int maTranKe[MAX][MAX];
    int soDinh;
};

void readFile(maTrix& mtk) {
    ifstream inFile("AdjacencyMatrix.txt");
    if (!inFile.is_open()) {
        cout << "\nKhong the mo tep";
        return;
    }

    inFile >> mtk.soDinh;
    for (int i = 0; i < mtk.soDinh; i++) {
        for (int j = 0; j < mtk.soDinh; j++) {
            inFile >> mtk.maTranKe[i][j];
        }
    }
    inFile.close();
}

void outputMaTrix(maTrix mtk) {
    cout << "\nMA TRAN KE: " << endl;
    for (int i = 0; i < mtk.soDinh; i++) {
        for (int j = 0; j < mtk.soDinh; j++) {
            cout << mtk.maTranKe[i][j] << "\t";
        }
        cout << endl;
    }
}

bool visited[MAX] = { false };

void DFS(int u, maTrix graph) {
    cout << u << " ";
    visited[u] = true;

    for (int i = 0; i < graph.soDinh; ++i) {
        if (graph.maTranKe[u][i] != 0 && !visited[i]) {
            DFS(i, graph);
        }
    }
}


void connectComponent(maTrix graph) {
    int count = 0;
    for (int i = 0; i < graph.soDinh; i++) {
        if (!visited[i]) {
            count++;
            cout << "\nCac dinh thuoc thanh phan lien thong thu " << count << ": ";
            DFS(i, graph);
            cout << endl;
        }
    }
    if (count == 1)
        cout << "\nDo thi lien thong";
    else {
        cout << "\nDo thi khong lien thong";
        cout << "\nSo thanh phan lien thong cua do thi: " << count;
    }
}

int main() {
    maTrix graph;
    readFile(graph);
    outputMaTrix(graph);
    connectComponent(graph);
}
