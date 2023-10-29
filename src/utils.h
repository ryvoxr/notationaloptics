#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

double degnormalize(double deg);
double degtorad(double deg);
double radtodeg(double rad);
double degsin(double deg);
double degcos(double deg);
double degtan(double deg);
double degatan2(double y, double x);
void sort(int v[], int left, int right);
void swap(int *px, int *py);
