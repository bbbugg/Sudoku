#include <bits/stdc++.h>
using namespace std;
clock_t start, stop;
double duration;

int sd[11][11];//数独方阵定义
bool p[11][11], l[11][11], fz[11][11];//行，列，方阵。
void _out() {
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++)
			cout << sd[i][j] << ""; 
		cout << endl;
	}
	//exit(0);
}

void dfs(int x, int y) {
	if (sd[x][y] != 0) {//如果原来这个位置有数字，跳过。
		if (x == 9 && y == 9)_out(); // l当行列都为9，填充完成，输出～
		else if (y == 9) dfs(x + 1, 1);//当列数为9，搜索下一排。
		else dfs(x ,y+1);//搜下一列
	}
	else {//原来的地方没有数字，准备填充!
		for (int i = 1; i <= 9; i++)
			if ((!p[x][i]) && (!l[y][i]) && (!fz[(x - 1) / 3 * 3 + (y - 1) / 3 + 1][i]))//判断是不是重复了。
			{
				sd[x][y] = i;//填充!
				p[x][i] = l[y][i] = fz[(x - 1) / 3 * 3 + (y - 1) / 3 + 1][i] = true;
				//打上标记。
				if (x == 9 && y == 9)_out();//全部填完!
				else if (y == 9)dfs(x + 1, 1);//同上!搜下一行。
				else dfs (x,y+1);//搜下一列!
				sd[x][y] = 0; //恢复标记。
				p[x][i] = l[y][i] = fz[(x - 1) / 3 * 3 + (y - 1) / 3 + 1][i] = false;//恢复标记
			}
	}
}

int main() {
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++) {
			int t;
			cin >> t;
			if (t != 0)
				p[i][t] = l[j][t] = fz[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][t] = true; // 填充的不是0的话，表示原来有数字了。打上标记。
			sd[i][j] = t;//填充进数独。
		}
	start = clock();
	dfs(1, 1);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << endl << "耗时：" << duration;
	return 0;
}