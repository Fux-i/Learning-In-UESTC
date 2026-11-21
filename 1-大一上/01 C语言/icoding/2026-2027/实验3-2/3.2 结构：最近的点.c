#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y, z;
} point3D;

double distance2(const point3D *a, const point3D *b);
int find_closest_point(const point3D *points, int n, const point3D *query);

#define MAXN 20
point3D points[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf%lf", &points[i].x, &points[i].y, &points[i].z);

    point3D query;
    scanf("%lf%lf%lf", &query.x, &query.y, &query.z);
    int index = find_closest_point(points, n, &query);
    printf("(%.1lf,%.1lf,%.1lf)\n", points[index].x, points[index].y, points[index].z);
    return 0;
}

// 请勿删除或修改此行以上的所有内容！！！
// 你的代码写在TODO和END OF TODO之间

// 计算点a和点b之间的距离的平方
double distance2(const point3D *a, const point3D *b) {
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    double dz = a->z - b->z;
    return dx * dx + dy * dy + dz * dz;
    // END OF TODO
}

// 查询距离点query最近的点的下标。points数组中保存了n个点，query是查询的点。
int find_closest_point(const point3D *points, int n, const point3D *query) {
    int i, best = 0;
    double bestd = distance2(&points[0], query);

    for (i = 1; i < n; i++) {
        double d = distance2(&points[i], query);
        if (d < bestd) {
            bestd = d;
            best = i;
        }
    }

    return best;
    // END OF TODO
}
