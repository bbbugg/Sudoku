#include <bits/stdc++.h>
using namespace std;
clock_t start, stop;
double duration;

int sd[11][11];//����������
bool p[11][11], l[11][11], fz[11][11];//�У��У�����
void _out() {
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++)
			cout << sd[i][j] << ""; 
		cout << endl;
	}
	//exit(0);
}

void dfs(int x, int y) {
	if (sd[x][y] != 0) {//���ԭ�����λ�������֣�������
		if (x == 9 && y == 9)_out(); // l�����ж�Ϊ9�������ɣ������
		else if (y == 9) dfs(x + 1, 1);//������Ϊ9��������һ�š�
		else dfs(x ,y+1);//����һ��
	}
	else {//ԭ���ĵط�û�����֣�׼�����!
		for (int i = 1; i <= 9; i++)
			if ((!p[x][i]) && (!l[y][i]) && (!fz[(x - 1) / 3 * 3 + (y - 1) / 3 + 1][i]))//�ж��ǲ����ظ��ˡ�
			{
				sd[x][y] = i;//���!
				p[x][i] = l[y][i] = fz[(x - 1) / 3 * 3 + (y - 1) / 3 + 1][i] = true;
				//���ϱ�ǡ�
				if (x == 9 && y == 9)_out();//ȫ������!
				else if (y == 9)dfs(x + 1, 1);//ͬ��!����һ�С�
				else dfs (x,y+1);//����һ��!
				sd[x][y] = 0; //�ָ���ǡ�
				p[x][i] = l[y][i] = fz[(x - 1) / 3 * 3 + (y - 1) / 3 + 1][i] = false;//�ָ����
			}
	}
}

int main() {
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++) {
			int t;
			cin >> t;
			if (t != 0)
				p[i][t] = l[j][t] = fz[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][t] = true; // ���Ĳ���0�Ļ�����ʾԭ���������ˡ����ϱ�ǡ�
			sd[i][j] = t;//����������
		}
	start = clock();
	dfs(1, 1);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << endl << "��ʱ��" << duration;
	return 0;
}