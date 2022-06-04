#include "Material.hpp"

// using namespace std;

int main() {
    char s[] = "NAME";
    char c[] = "COURSE";
    char p[] = "PATH";
    ByteArray md(8, 'x');
    ByteArray mm;
    String sname; sname = s;
    String cname; cname = c;
    String pname; pname = p;
    Time btime; btime = 1000;
    // printf("%s\n%s\n%s\n", sname.data(), cname.data(), pname.data());
    Material a(1, cname, md, sname, pname, btime);
    printf("%d %d\n", a.isHomework(), a.isData());
    printf("%s\n", a.getCourseName().data());
    printf("%s\n", a.getName().data());
    printf("%d: ", md.getSize());
    // mm = a.getMd5();
    // printf("%d: ", mm.getSize());
    // printf("???\n");
    // printf("%d: ", a.getMd5().getSize());
    // for(int i = 0; i < a.getMd5().getSize(); i ++) {
    //     printf("%d ", a.getMd5()[i]);
    // }
    // printf("\n");
    // printf("%d\n", a.getTime().calHours());
    return 0;
}
