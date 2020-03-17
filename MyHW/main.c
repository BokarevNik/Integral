#include <stdio.h>
#include <math.h>
#include <getopt.h>

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double df1(double x);
extern double df2(double x);
extern double df3(double x);
extern double ddf1(double x);
extern double ddf2(double x);
extern double ddf3(double x);
static int iter = 0;

double root(double (*f) (double x),double (*df) (double x),double (*ddf) (double x), double (*g) (double x), double (*dg) (double x),double (*ddg) (double x), double a, double b, double e){  // Хорды и касательные
    do {
        iter++;
        if ((f(a) - g(a)) * (ddf(a) - ddg(a)) < 0) {
            a = a + (b - a) / ((f(a) - g(a)) - (f(b) - g(b)))*f(a); 
        } else if ((f(a) - g(a)) * (ddf(a) - ddg(a)) > 0){
            a = a - (f(a) - g(a))/ (df(a) - dg(a));
        }
        if ((f(b) - g(b)) * (ddf(b) - ddg(b)) < 0) {
            b = b - (b - a) / ((f(b)- g(b)) - (f(a) - g(a)))*(f(b) - g(b)); 
        } else if ((f(b) - g(b)) * (ddf(b) - ddg(b)) > 0) {
            b = b - (f(b) - g(b))/ (df(b) - dg(b));
        }
    } while (fabs(b - a) > 2.0 * e);
    return (a + b) / 2.0;
}

double integral(double (*f) (double x), double a, double b, double e){     // Метод Симпсона
    double Iprev = (b - a)/6.0 * (f(a) + 4 * f((a + b)/2.0) + f(b));
    double Icur = Iprev;
    int n = 1;
    do {
        Iprev = Icur;
        n *= 2;
        double sum4 = 0;
        double sum2 = 0;
        double h = (b - a)/ n;
        for (int i = 1; i < n; i+=2){
            sum4 += f(a + i * h);
            sum2 += f(a + (i + 1) * h);
        }
        Icur = h/3.0 * (f(a) + 4 * sum4 + 2 * sum2);
    } while (fabs(Iprev - Icur) > e);
    return Icur;
}

int main(int argc, char *argv[]){
    typedef double (*AsmFunc)(double x);
    AsmFunc Func_list[8];
    Func_list[0] = f1;
    Func_list[1] = df1;
    Func_list[2] = ddf1;
    Func_list[3] = f2;
    Func_list[4] = df2;
    Func_list[5] = ddf2;
    Func_list[6] = f3;
    Func_list[7] = df3;
    Func_list[8] = ddf3;
    double a, b, e;

    static struct option options[] = {
        {"help",   0, 0, 'h'},
        {"abscissa", 0, 0, 'a'},
        {"iterations", 0, 0, 'i'},
        {"root", 0, 0, 'r'},
        {"simpson", 0, 0, 's'},
    };
    char flag1 = 0, flag2 = 0;
    int option_index;
    int c = getopt_long_only(argc, argv, "h", options, &option_index);
    int first_func = 1;
    int second_func = 1;
    double hint[3];
    if (c != -1) {
        switch (c) {
            case 'h':
                printf("type nasm -h for help\ntype nasm -a for abscisses\ntype nasm -i for iterations number\ntype nasm -r for roots\ntype nasm -s for integral\n");
                return 0;
            case 'a':
                flag1 = 1;
                break;
            case 'i':
                flag2 = 1;
                break;
            case 'r':
                sscanf(argv[optind], "%d", &first_func);
                optind++;
                sscanf(argv[optind], "%d", &second_func);
                optind++;
                sscanf(argv[optind], "%lf", &a);
                optind++;
                sscanf(argv[optind], "%lf", &b);
                optind++;
                sscanf(argv[optind], "%lf", &e);
                printf("%lf\n", root(Func_list[(first_func - 1) * 3], Func_list[(first_func - 1) * 3 + 1], Func_list[(first_func - 1) * 3 + 2], Func_list[(second_func - 1) * 3], Func_list[(second_func - 1) * 3 + 1], Func_list[(second_func - 1) * 3 + 2], a, b, e));
                return 0;
            case 's':
                sscanf(argv[optind], "%d", &first_func);
                optind++;
                sscanf(argv[optind], "%lf", &a);
                optind++;
                sscanf(argv[optind], "%lf", &b);
                optind++;
                sscanf(argv[optind], "%lf", &e);
                printf("%lf\n", integral(Func_list[(first_func - 1) * 3], a, b, e));
                return 0;
            default:
                break;
        }
    }
    double x1, x2, x3;
    double I1, I2, I3;

    x1 = root (f1, df1, ddf1, f3, df3, ddf3, 0.1, 2.0, 0.001);
    int iter1= iter;
    iter = 0;
    x2 = root (f1, df1, ddf1, f2, df2, ddf2, 0.0, 4.0, 0.001);
    int iter2 = iter;
    iter = 0;
    x3 = root (f3, df3, ddf3, f2, df2, ddf2, 0.1, 2.0, 0.001);
    int iter3 = iter;
    iter = 0;
    
    if (flag1 == 1){
        printf("%lf %lf %lf\n", x1, x2, x3);
        return 0;
    }
    if (flag2 == 1){
        printf("%d %d %d\n", iter1, iter2, iter3);
        return 0;
    }

    I1 = integral(f1, x1, x2, 0.001);
    I2 = integral(f2, x3, x2, 0.001);
    I3 = integral(f3, x1, x3, 0.001);
    printf("%lf\n", I1 - I2 - I3);
    return 0;
}